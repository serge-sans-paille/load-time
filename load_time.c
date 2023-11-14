#include <dlfcn.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "usage: %s /path/to/a/shared/library.so\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct timeval start, stop;
  gettimeofday(&start, NULL);

  void * handle = dlopen(argv[1], RTLD_NOW);
  if(!handle) {
    fprintf(stderr, "failed to load '%s': %s\n",
        argv[1],
        dlerror());
    exit(EXIT_FAILURE);
  }

  gettimeofday(&stop, NULL);
  fprintf(stderr,
          "%lld us\n",
          (stop.tv_sec - start.tv_sec) * 1000000ll + (stop.tv_usec - start.tv_usec));
  dlclose(handle);
  return 0;
}
