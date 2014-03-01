#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "drive_wrapper.h"

using namespace googleapis;

int main (int argc, char **argv) {
	DriveWrapper *drive = new DriveWrapper();

	drive->dir();
}
