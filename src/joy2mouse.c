#include <stdio.h>

#include "joystick.h"
#include "xdo.h"

void cursor_listener( struct js_event e );
void click_listener( struct js_event e );

int main( int argc, char **argv ) {
  printf( "%s\n", xdo_version() );
  
  //Initialize Joystick
  init_listener(JOY_0);

  //Register Listeners
  int list_h[2];
  list_h[0] = register_listener( cursor_listener, AXIS_ONLY );
  list_h[1] = register_listener( click_listener, BUTTONS_ONLY );

  while (1) sleep(60);

  //Cleanup
  deregister_listener( list_h[0] );
  deregister_listener( list_h[1] );

  return 0;
}

void cursor_listener( struct js_event e ) {

}

void click_listener( struct js_event e ) {

}
