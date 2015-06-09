#include "xdo.h"

int main() {
  xdo_t *env = xdo_new(NULL);
  xdo_mousedown( env, 0, 3 );
  xdo_mouseup( env, 0, 3 );
  return 0;
}
