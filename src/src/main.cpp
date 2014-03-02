#include "drive_wrapper.h"
#include "wizard-mm.h"

using namespace Gtk;
using namespace googleapis;

int
main (int    argc,
      char** argv)
{
  Glib::RefPtr<Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gtkdrive");

  DriveWrapper *drive = new DriveWrapper;
  GtkDriveAssistant assistant (drive);

  //DriveWrapper *drive = new DriveWrapper();
  //drive->dir();

  return app->run (assistant);
}
