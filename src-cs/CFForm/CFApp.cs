// CFApp.cs
// this file is part of Context Free
// ---------------------
// Copyright (C) 2022 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


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
