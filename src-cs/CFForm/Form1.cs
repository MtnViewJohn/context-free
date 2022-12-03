using OpenMRU.Core.Common.Implementations;
using OpenMRU.Core.View.Localization;
using OpenMRU.WinForm.Menu;
using CppWrapper;
using System.Diagnostics;
using System.Media;
using WeifenLuo.WinFormsUI.Docking;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Security.Policy;
using Microsoft.Win32;
using System.Windows.Forms;
using System.Xml.Linq;

namespace CFForm
{
    public partial class Form1 : Form
    {
        public enum StartAction
        {
            Welcome = 0, New = 1, Nothing = 2
        }
        private DockPanel dockPanel;
        public bool isResizing = false;
        public bool isResized = false;
        private FindReplaceForm findForm = new FindReplaceForm();
        public ColorCalculator colorCalc = new CppWrapper.ColorCalculator();
        public readonly MRUManager manager;
        private StartAction startAction = StartAction.Nothing;
        public Form1()
        {
            dockPanel = new DockPanel();
            dockPanel.Dock = DockStyle.Fill;
            dockPanel.Theme = new VS2015LightTheme();
            dockPanel.DocumentStyle = DocumentStyle.DockingMdi;
            Controls.Add(dockPanel);

            InitializeComponent();

            String path = System.Windows.Forms.Application.LocalUserAppDataPath;
            MRUItemFileStorage storage = new MRUItemFileStorage(path + "\\..\\context_free_mru_storage.xml");
            manager = new MRUManager();
            manager.Initialize(storage);
            manager.MRUItemSelected += openDoc;
            MRUItemsMenu itemsMenu = new MRUItemsMenu();
            itemsMenu.Initialize(manager, new MRUGuiLocalization());
            itemsMenu.AttachToMenu(recentToolStripMenuItem);

            AllowDrop = true;

            Version osver = Environment.OSVersion.Version;
            if (osver.Major < 10) {
                String appPath = Application.ExecutablePath;
                // Check if the required registry keys exist and are correct
                try {
                    using (RegistryKey? classKey = Registry.CurrentUser.OpenSubKey("Software\\Classes\\.cfdg"),
                                            key2 = classKey.OpenSubKey("ShellNew"))
                    {
                        String? newCmd = key2.GetValue("Command") as String;
                        if (newCmd.IndexOf(appPath) == -1)
                            throw new Exception();
                    }
                    using (RegistryKey? key = Registry.CurrentUser.OpenSubKey("Software\\Classes\\ContextFree.Document")) 
                    {
                        String? name = key.GetValue(String.Empty) as String;
                    }
                } catch {
                    // If not then make/fix them
                    try {
                        using (RegistryKey classKey = Registry.CurrentUser.CreateSubKey("Software\\Classes\\.cfdg"),
                                               key2 = classKey.CreateSubKey("ShellNew")) {
                            classKey.SetValue(String.Empty, "ContextFree.Document");
                            key2.SetValue("Command", String.Format("\"{0}\" /new \"%1\"", appPath));
                        }
                        using (RegistryKey classKey = Registry.CurrentUser.CreateSubKey("Software\\Classes\\ContextFree.Document"),
                                            iconkey = classKey.CreateSubKey("DefaultIcon"),
                                               key1 = classKey.CreateSubKey("shell"),
                                               key2 = key1.CreateSubKey("open"),
                                               key3 = key2.CreateSubKey("command"))
                        {
                            classKey.SetValue(String.Empty, "Context Free file");
                            iconkey.SetValue(String.Empty, String.Format("\"{0}\",1", appPath));
                            key3.SetValue(String.Empty, String.Format("\"{0}\" \"%1\"", appPath));
                        }
                    } catch { }
                }
            }

            String[] args = Environment.GetCommandLineArgs();
            if (args.Length > 1)
                processArgs(args);
            else
                startAction = (StartAction)Properties.Settings.Default.StartAction;

            using (var help = new CppWrapper.RenderHelper()) {
                String[] temps = help.findTempFiles();
                if (temps != null && temps.Length > 0) {
                    if (MessageBox.Show(this, "Should they be deleted?",
                                        "Old temporary files found",
                                        MessageBoxButtons.YesNo, 
                                        MessageBoxIcon.Question,
                                        MessageBoxDefaultButton.Button1) == DialogResult.Yes)
                    {
                        foreach (var file in temps) {
                            try {
                                File.Delete(file);
                            } catch { }
                        }
                    }
                }
            }
        }

        public void processArgs(String[] args)
        {
            if (InvokeRequired) return;
            if (args == null || args.Length <= 1) return;

            if (args.Length == 2) {
                openDoc(args[1]);
            } else if (args[1] == "/new" && args.Length == 3) {
                String? dir = Path.GetDirectoryName(args[2]);
                if (dir == null) dir = String.Empty;
                openNew(dir);
            }
            Activate();
            BringToFront();
        }

        private Document? findOpenDocument(String name)
        {
            foreach (var kid in MdiChildren) {
                Document? doc = kid as Document;
                if (doc != null && doc.Name == name)
                    return doc;
            }
            return null;
        }

        private String uniqueNewFile(String basename, String dir)
        {
            for (int i = 0; ; ++i) {
                String name = i == 0 ? Path.Join(dir, basename + ".cfdg")
                                     : Path.Join(dir, basename + i.ToString() + ".cfdg");
                if (!File.Exists(name) && findOpenDocument(name) == null)
                    return name;
            }
        }

        private void openNew(String dir)
        {
            openDoc(uniqueNewFile("Document", dir));
        }

        private void openDoc(String name)
        {
            Document? document = findOpenDocument(name);
            if (document != null) {
                document.Activate();
                return;
            }

            bool fullPath = Path.IsPathRooted(name);

            document = new Document {
                TabText = Path.GetFileName(name),
                Name = name,
                isNamed = fullPath,
                Text = Path.GetFileName(name),
                Dock = DockStyle.Fill,
                reloadWhenReady = fullPath ? File.Exists(name)
                                           : RenderHelper.IsExample(name)
            };

            if (File.Exists(name))
                manager.AddFile(name);

            document.Show(dockPanel, WeifenLuo.WinFormsUI.Docking.DockState.Document);
        }

        public void openUrl(String url)
        {
            String filename = uniqueNewFile("Download", String.Empty);
            var document = new Document {
                Name = url,
                TabText = filename,
                isNamed = false,
                reloadWhenReady = true,
                Text = filename,
                Dock = DockStyle.Fill
            };

            document.Show(dockPanel, WeifenLuo.WinFormsUI.Docking.DockState.Document);
        }

        public void openText(String cfdg)
        {
            String filename = uniqueNewFile("Document", String.Empty);
            var document = new Document {
                Name = cfdg.Insert(0, "data:text/plain;charset=UTF-8,"),
                TabText = filename,
                isNamed = false,
                reloadWhenReady = true,
                Text = filename,
                Dock = DockStyle.Fill
            };

            document.Show(dockPanel, WeifenLuo.WinFormsUI.Docking.DockState.Document);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void urlToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem menuitem = (ToolStripMenuItem)sender;
            String url = (String)menuitem.Tag;
            Process.Start(new ProcessStartInfo("cmd", $"/c start {url}") { CreateNoWindow = true });
        }

        private void aboutContextFreeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox box = new AboutBox();
            box.Show();
        }

        private void preferencesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PreferenceDialog preference = new PreferenceDialog();
            if (preference.ShowDialog() != DialogResult.Cancel) {
                foreach (var content in dockPanel.Documents) {
                    Document? doc = content as Document;
                    if (doc != null) {
                        if (preference.styleChanged)
                            doc.styleChanged();
                        if (preference.currentFont != null)
                            doc.fontChanged(preference.currentFont);
                    }
                }
            }
        }

        private void openNewClick(object sender, EventArgs e)
        {
            openNew(String.Empty);
        }

        private void resizeBegin(object sender, EventArgs e)
        {
            isResizing = true;
            isResized = false;
        }

        private void resizeEnd(object sender, EventArgs e)
        {
            isResizing = false;
            if (isResized) {
                Properties.Settings.Default.FormSize = ClientSize;
                Document? kid = ActiveMdiChild as Document;
                if (kid != null) {
                    Properties.Settings.Default.EditorSplitter = kid.editorSplitter.SplitterDistance;
                    Properties.Settings.Default.DocumentSplitter = kid.documentSplitter.SplitterDistance;
                }
                isResized = false;
            }
        }

        private void resized(object sender, EventArgs e)
        {
            isResized = true;
        }

        private void menuFOpenClick(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK) {
                openDoc(openFileDialog.FileName);
            }
        }

        private void openExampleClick(object sender, EventArgs e)
        {
            ToolStripMenuItem? example = sender as ToolStripMenuItem;
            if (example != null) {
                openDoc(example.Text + ".cfdg");
            }
        }

        private void formIsClosing(object sender, FormClosingEventArgs e)
        {
            if (e.Cancel) {
                bool userAction = false;
                foreach (var kid in MdiChildren) {
                    Document? doc = kid as Document;
                    if (doc != null)
                        userAction = userAction || doc.canceledByUser;
                }
                if (userAction)
                    return;
                foreach (var kid in MdiChildren) {
                    Document? doc = kid as Document;
                    if (doc != null && doc.renderThread.IsBusy) {
                        doc.postAction = Document.PostRenderAction.Exit;
                        return;     // Have busy child retry the Close()
                    }
                }
                Close();            //  otherwise retry it here.
            }
        }

        private void appIsExiting(object sender, EventArgs e)
        {
            RenderHelper.AbortEverything();
        }

        private void loadInitialization(object sender, EventArgs e)
        {
            switch (startAction) {
                case StartAction.Welcome:
                    welcomeToolStripMenuItem.PerformClick();
                    break;
                case StartAction.New:
                    menuFNew.PerformClick();
                    break;
                default:
                    break;
            }
        }

        private void childActivate(object sender, EventArgs e)
        {
            Document? doc = ActiveMdiChild as Document;
            if (doc != null) {
                findForm.currentScintilla = doc.cfdgText;
            }
        }

        public void menuEFindClick(object? sender, EventArgs e)
        {
            if (findForm.DockState != DockState.DockBottom) {
                dockPanel.DockBottomPortion = 130;
                findForm.Show(dockPanel, DockState.DockBottom);
            } else {
                ToolStripMenuItem? menu = sender as ToolStripMenuItem;
                if (menu != null) {
                    var button = (menu.Tag != null) ? findForm.prevButton : findForm.nextButton;
                    if (button.Enabled)
                        button.PerformClick();
                    else
                        SystemSounds.Beep.Play();
                }
            }
        }

        private void menuWColorCalc(object sender, EventArgs e)
        {
            if (colorCalc.Visible) {
                colorCalc.WindowState = FormWindowState.Normal;
                colorCalc.Activate();
            } else {
                colorCalc.Show();
            }
        }

        private void menuFilePopup(object sender, EventArgs e)
        {
            Document? document = ActiveMdiChild as Document;
            if (document != null)
                document.menuFilePopup(this, e);
        }

        public void formDragDrop(object sender, DragEventArgs e)
        {
            if (e.Data == null) return;
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                foreach (string file in files)
                    openDoc(file);
                return;
            }
            String? url = e.Data.GetData(DataFormats.Text)?.ToString();
            if (url == null) return;

            if (url.StartsWith("file://")) {
                openUrl(url);
                return;
            }

            if (url.StartsWith("https://www.contextfreeart.org/gallery") ||
                url.StartsWith("http://www.contextfreeart.org/gallery") ||
                url.StartsWith("https://contextfreeart.org/gallery") ||
                url.StartsWith("http://contextfreeart.org/gallery") ||
                url.StartsWith("http://localmac/~john/cfa2/gallery")) {
                int idx = url.IndexOf("id=");
                if (idx < 0) {
                    idx = url.IndexOf("#design/");
                    if (idx >= 0) idx += 8;
                } else {
                    idx += 3;
                }
                if (idx >= 0) {
                    if (int.TryParse(url.Substring(idx), out int design))
                        url = String.Format("https://www.contextfreeart.org/gallery/data.php/{0}/info/foo.json", design);
                    else
                        url = null;
                } else if (!url.EndsWith(".cfdg")) {
                    url = null;
                }

                if (url != null)
                    openUrl(url);
                else
                    SystemSounds.Beep.Play();
                return;
            }

            openText(url);
        }

        private void formDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data ==  null) {
                e.Effect = DragDropEffects.None;
            } else {
                if (e.Data.GetDataPresent(DataFormats.FileDrop) || e.Data.GetDataPresent(DataFormats.Text))
                    e.Effect = DragDropEffects.Copy;
                else
                    e.Effect = DragDropEffects.None;
            }
        }
    }
}