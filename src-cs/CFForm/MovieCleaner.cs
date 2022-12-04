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
