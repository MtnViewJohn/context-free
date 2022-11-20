using CppWrapper;
using System.Diagnostics;
using WeifenLuo.WinFormsUI.Docking;

namespace CFForm
{
    public partial class Form1 : Form
    {
        private DockPanel dockPanel;
        public bool isResizing = false;
        public bool isResized = false;
        public Form1()
        {
            dockPanel = new DockPanel();
            dockPanel.Dock = DockStyle.Fill;
            dockPanel.Theme = new VS2015LightTheme();
            dockPanel.DocumentStyle = DocumentStyle.DockingMdi;
            Controls.Add(dockPanel);

            InitializeComponent();
        }

        private void openDoc(String name)
        {
            Document document = new Document();

            document.TabText = Path.GetFileName(name);
            document.Name = name;
            document.isNamed = Path.IsPathRooted(name);
            document.reloadWhenReady = document.isNamed ? File.Exists(name)
                                                        : RenderHelper.IsExample(name);

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

        }
    }
}