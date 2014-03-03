#include <gtkmm.h>
#include <iostream>

#include "gtkdrive.h"

using namespace Gtk;
using namespace googleapis;

int
main (int    argc,
      char** argv)
{
  Glib::RefPtr<Application> app = Application::create(argc, argv, "org.gtkmm.gtkdrive");

  GtkDrive drive;
  drive.Startup(app);

  return 0;
}
