#include <stdio.h>

#include "joystick.h"
#include "xdo.h"

int main( int argc, char **argv ) {
  printf( "%s\n", xdo_version() );
  return 0;
}
