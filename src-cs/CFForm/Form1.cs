using OpenMRU.Core.Common.Implementations;
using OpenMRU.Core.View.Localization;
using OpenMRU.WinForm.Menu;
using CppWrapper;
using System.Diagnostics;
using System.Media;
using WeifenLuo.WinFormsUI.Docking;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

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
        public Form1()
        {
            dockPanel = new DockPanel();
            dockPanel.Dock = DockStyle.Fill;
            dockPanel.Theme = new VS2015LightTheme();
            dockPanel.DocumentStyle = DocumentStyle.DockingMdi;
            Controls.Add(dockPanel);

            InitializeComponent();

            String path = System.Windows.Forms.Application.UserAppDataPath;
            MRUItemFileStorage storage = new MRUItemFileStorage(path + "\\context_free_mru_storage.xml");
            manager = new MRUManager();
            manager.Initialize(storage);
            manager.MRUItemSelected += openDoc;
            MRUItemsMenu itemsMenu = new MRUItemsMenu();
            itemsMenu.Initialize(manager, new MRUGuiLocalization());
            itemsMenu.AttachToMenu(recentToolStripMenuItem);
        }

        private void openDoc(String name)
        {
            Document document = new Document();

            document.TabText = Path.GetFileName(name);
            document.Name = name;
            document.isNamed = Path.IsPathRooted(name);
            document.reloadWhenReady = document.isNamed ? File.Exists(name)
                                                        : RenderHelper.IsExample(name);
            if (File.Exists(name))
                manager.AddFile(name);

            document.Text = document.TabText;
            document.Dock = DockStyle.Fill;
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
            openDoc("Document.cfdg");
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
            switch ((StartAction)Properties.Settings.Default.StartAction) {
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
    }
}