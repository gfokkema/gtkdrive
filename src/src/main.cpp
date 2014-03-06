#include <iostream>

#include "gtkdrive.h"

using namespace googleapis;

int
main (int    argc,
      char** argv)
{
//  Glib::RefPtr<Application> app = Application::create(argc, argv, "org.gtkmm.gtkdrive");
  GtkDrive drive;
  drive.about();
  drive.dir();

  return 0;
}
