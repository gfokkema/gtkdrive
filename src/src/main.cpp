#include <iostream>

#include "gtkdrive.h"
#include "wizard-mm.h"

using namespace Gtk;
using namespace googleapis;

int
main (int    argc,
      char** argv)
{
  Glib::RefPtr<Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gtkdrive");

  GtkDrive drive;
  drive.Startup();

  app->run(drive);

  return 0;
}
