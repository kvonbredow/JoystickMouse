#include <stdio.h>

#include "joystick.h"
#include "xdo.h"

void cursor_listener( struct js_event e );
void click_listener( struct js_event e );

static xdo_t *env;
static int vx, vy;

int main( int argc, char **argv ) {

  //Initialize X Controller
  printf( "%s\n", xdo_version() );
  env = xdo_new(NULL);

  //Initialize Joystick
  if ( argc == 2 )
    init_listener(argv[1]);
  else
    init_listener(JOY_0);

  //Initialize Cursor Velocity
  vx = 0;
  vy = 0;

  //Register Listeners
  int list_h[2];
  list_h[0] = register_listener( cursor_listener, AXIS_ONLY );
  list_h[1] = register_listener( click_listener, BUTTONS_ONLY );

  while (1) {
    xdo_mousemove_relative( env, vx, vy ); 
    usleep(100);
  }

  //Cleanup
  deregister_listener( list_h[0] );
  deregister_listener( list_h[1] );

  return 0;
}

void cursor_listener( struct js_event e ) {
  printf( "AXIS %d : %d\n", e.number, e.value);
  if ( e.value > -5000 && e.value < 5000 ) return;
  switch ( e.number ) {
    case 0:
      vx = e.value / 16000;
      break;
    case 1:
      vy = e.value / 16000;
      break;
  }
}

void click_listener( struct js_event e ) {
  printf( "BUTTON %d : %d\n", e.number, e.value);
  switch ( e.number ) {
    case 0:
      if ( e.value ) xdo_mousedown( env, 0, 1 );
      else xdo_mouseup( env, 0, 1 );
      break;
    case 1:
      if ( e.value ) xdo_mousedown( env, 0, 3 );
      else xdo_mouseup( env, 0, 3 );
      break;
    case 7:
      if ( e.value ) xdo_mousedown( env, 0, 4 );
      else xdo_mouseup( env, 0, 1 );
      break;
    case 6:
      if ( e.value ) xdo_mousedown( env, 0, 5 );
      else xdo_mouseup( env, 0, 5 );
      break;
  }
}
