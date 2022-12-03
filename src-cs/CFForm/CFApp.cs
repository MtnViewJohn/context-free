using Microsoft.VisualBasic.ApplicationServices;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CFForm
{
    internal class CFApp : Microsoft.VisualBasic.ApplicationServices.WindowsFormsApplicationBase
    {
        public CFApp() { 
            EnableVisualStyles = true;
            IsSingleInstance = true;
            ShutdownStyle = Microsoft.VisualBasic.ApplicationServices.ShutdownMode.AfterMainFormCloses;
            StartupNextInstance += new Microsoft.VisualBasic.ApplicationServices.StartupNextInstanceEventHandler(SIApp_StartupNextInstance);
        }

        protected override void OnCreateMainForm()
        {
            MainForm = new Form1();
        }

        protected void SIApp_StartupNextInstance(object sender, StartupNextInstanceEventArgs eventArgs) {
            String[] args = new String[eventArgs.CommandLine.Count];
            eventArgs.CommandLine.CopyTo(args, 0);

            Form1? form1 = MainForm as Form1;
            form1?.Invoke(new Form1.ProcessParametersDelegate(form1.ProcessArgs), new Object[]{args});
        }
    }
}
