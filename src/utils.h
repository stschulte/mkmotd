#ifndef MKMOTD_UTILS_H
#define MKMOTD_UTILS_H

#include <sys/types.h>

ssize_t safe_read(int fildes, void *buf, size_t nbyte);
ssize_t safe_write(int fildes, const void *buf, size_t nbyte);

#endif
