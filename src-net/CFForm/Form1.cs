namespace CFForm
{
    public partial class Form1 : Form
    {
        public WeifenLuo.WinFormsUI.Docking.DockPanel dockpanel;
        public Form1()
        {
            InitializeComponent();

            this.dockpanel = new WeifenLuo.WinFormsUI.Docking.DockPanel();
            this.dockpanel.Theme = new WeifenLuo.WinFormsUI.Docking.VS2015LightTheme();
            this.SuspendLayout();
        }

        private void urlClick(object sender, EventArgs e)
        {
            ToolStripMenuItem menuitem = (ToolStripMenuItem)sender;
            System.Diagnostics.Process.Start((String)menuitem.Tag);
        }

        private void aboutClick(object sender, EventArgs e)
        {

        }

        private void exitClick(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}