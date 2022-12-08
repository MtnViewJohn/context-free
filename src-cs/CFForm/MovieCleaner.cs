// MovieCleaner.cs
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


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CFForm
{
    internal class MovieCleaner
    {
        private static List<MovieCleaner> Cleaners = new List<MovieCleaner>();
        private System.Diagnostics.Process? player;
        private String? file;

        public static void Clean(System.Diagnostics.Process? player, String? file)
        {
            if (file == null) return;
            if (player == null || player.HasExited) {
                try {
                    System.IO.File.Delete(file);
                    System.Diagnostics.Debugger.Log(3, "Delete success: ", file);
                } catch {
                    System.Diagnostics.Debugger.Log(1, "Delete failed: ", file);
                }
            } else {
                Cleaners.Add(new MovieCleaner(player, file));
            }
        }

        private MovieCleaner(System.Diagnostics.Process player, String file)
        {
            this.player = player;
            this.file = file;
            player.Exited += new EventHandler(this.DeleteIt);
            player.CloseMainWindow();
        }

        private void DeleteIt(Object? sender, EventArgs e)
        {
            try {
                System.IO.File.Delete(file);
                System.Diagnostics.Debugger.Log(3, "Delete success: ", file);
            } catch {
                System.Diagnostics.Debugger.Log(1, "Delete failed: ", file);
            }
            player = null;
            file = null;
            Cleaners.Remove(this);
        }
    }
}
