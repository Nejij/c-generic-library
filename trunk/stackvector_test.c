#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#define RUNS 1000000
#define BOUND 10000
#define BASE 0
#define NUMCASES 10

int32_t intcmp(const void *, const void *);
void  print(const void *);
void  ckfree(void *);
void *ckalloc(size_t);

int
main(void) {
  StackVector  object;
  StackVectorIter *ptr;
  unsigned int x, y;
  unsigned int value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(StackVector, &object,sizeof(x),FREEOBJ);
  set_alloc(StackVector,  &object, ckalloc);
  set_dealloc(StackVector,  &object, ckfree);
  set_compare(StackVector,  &object, intcmp);
  set_print(StackVector,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
        case 1:
        case 12:
        case 13:
        case 2:
          value = rand() % BOUND;
          push(StackVector,  &object, &value, DYNAMIC);
          break;
        case 3:
        case 15:
        case 4:
        case 5:
        case 6:
        case 16:
          pop(StackVector,  &object);
          break;
        case 14:
        case 7:
        case 17:
        case 8:
        case 9:
          top(StackVector,  &object);
          break;
        default:
          break;
    };
  }
  destruct(StackVector,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(StackVector,&object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = rand();
    push(StackVector,  &object, &value, STATIC);
  }

  ptr = create(StackVectorIter,  &object);
  head(StackVectorIter, ptr);
  do {
    value = *(unsigned int *) retrieve(StackVectorIter, ptr);
  }
  while (!next(StackVectorIter, ptr));
  assign(StackVectorIter, ptr, &object);
  tail(StackVectorIter, ptr);
  do {
    value = *(unsigned int *) retrieve(StackVectorIter, ptr);
  } while (!prev(StackVectorIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  next(StackVectorIter,ptr);
			  break;
		  case 2:
			  prev(StackVectorIter,ptr);
			  break;
	  }
  }
  destroy(StackVectorIter, ptr);
  destruct(StackVector,  &object);
  return EXIT_SUCCESS;
}

int32_t
intcmp(const void *a, const void *b)
{
  if ((*(const int *) a) < (*(const int *) b)) {
    return -1;
  } else if ((*(const int *) a) > (*(const int *) b)) {
    return 1;
  } else {
    return 0;
  }
}

void
print(const void *a)
{
  printf("%d ", (*(const int *) a));
}

void *
ckalloc(size_t size)
{
  void *ptr;

  do {
    ptr = malloc(size);
  }
  while (!ptr);
  return ptr;
}

void
ckfree(void *ptr)
{
  free(ptr);
}
