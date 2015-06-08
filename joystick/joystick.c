#include "joystick.h"

static char initialized = 0;
static struct listener_handle registrar[NUM_L];
static int fp;
static int num_active;
static pthread_t dispatcher;

extern void init_listener(const char *filename ) {
  int k;
  for ( k = 0; k < NUM_L; k++ ) {
    registrar[k].func_ptr = NULL;
    registrar[k].flags = DEFAULT;
    registrar[k].active = 0;
  }
  num_active = 0;
  
  fp = open ( filename, O_RDONLY); 
  if (fp < 0) {
    printf("Unable to open %s\n", filename);
    exit(1);
  }

  initialized = 1;
}

extern int register_listener( void (*func_ptr)(struct js_event e), char flags ) {

  if ( !initialized ) {
    printf("Listener was not initialized");
    exit(1);
  }

  int k;
  for ( k = 0; k < NUM_L && registrar[k].active; k++);

  struct listener_handle *h = &registrar[k];
  h->func_ptr = func_ptr;
  h->flags = flags;
  h->active = 1;

  if ( !num_active )
    pthread_create( &dispatcher, NULL, dispatch, NULL);

  num_active++;

  return k;

}

//IMPLEMENT NON_BLOCKING
void *dispatch( void * ptr ) {

  struct js_event e;
  int bytes;
  int k;

  do {

    bytes = read( fp, &e, sizeof(e) );
    if ( bytes != sizeof(e) ) {
      printf("Unexpected size.\n");
    }

    e.type &= ~JS_EVENT_INIT;
 
    for ( k = 0; k < NUM_L; k++ ) {
      if ( !registrar[k].active ) continue;
      if ( e.type & registrar[k].flags ) continue;
      (*registrar[k].func_ptr)(e);      
    }
    
    usleep(1000);
  
  } while ( 1 );

}

extern void deregister_listener( int k ) {

  struct listener_handle *h = &registrar[k];
  if ( !h->active ) return;
  h->active = 0;
  h->func_ptr = NULL;
  h->flags = DEFAULT;

  num_active--;

  if ( !num_active ) {
    pthread_cancel(dispatcher);
  }

}

void noblock_function( void * ptr ) {
  struct nb_info *info = (struct nb_info*) ptr;
  (*info->func_ptr)(info->e);
  free( info );
}
