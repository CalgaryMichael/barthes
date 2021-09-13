#include <stdio.h>
#include <stdlib.h>

namespace barthes {
    void die(const char *s) {
      perror(s);
      exit(EXIT_FAILURE);
    }
}
