#include "hash.h"

int hash(int elem, int vez, int tam)  {
  long long int ee,vv,tt;
  ee = elem;
  vv = vez;
  tt = tam;
  int ret =  (ee + 17*vv + 19*vv*vv) % tt;
  return ret;
}
