#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#include "utils.h"

ssize_t safe_read(int fildes, void *buf, size_t nbyte) {
  ssize_t read_bytes;
  while(1) {
    read_bytes = read(fildes, buf, nbyte);
    if(read_bytes < 0 && errno == EINTR)
      continue;

    return read_bytes;
  }
}

ssize_t safe_write(int fildes, const void *buf, size_t nbyte) {
  ssize_t write_bytes;
  ssize_t total = 0;

  char* ptr = (char*)buf;
  while(nbyte > 0) {
    write_bytes = write(fildes, ptr, nbyte);
    if(write_bytes < 0) {
      if(errno == EINTR) {
        continue;
      }
      break;
    }

    ptr += write_bytes;
    total += write_bytes;
    nbyte -= write_bytes;
  }

  return total;
}
