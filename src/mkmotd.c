#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <glob.h>
#include <errno.h>
#include <unistd.h>

#include "config.h"
#include "utils.h"

#define BUFSIZE 2048

int usage(int exit) {
  fprintf(stderr,
    "usage: "PROGRAM" (-h |  --help)\n"
    "usage: "PROGRAM" --version\n"
    "\n"
    "generate a message of the day out of multiple input files\n"
    "\n"
    "generate the file "MOTD" out of multiple input files inside "MOTD_DIR".\n"
    "the reasoning behind this task is to provide a documentation about the\n"
    "system to the user exactly when he will probably ask himself how the machine\n"
    "will behave\n");

  return(exit);
}

int cat(int fout, int fin) {
  ssize_t rbytes;
  char buf[BUFSIZE];
  while((rbytes = safe_read(fin, buf, BUFSIZE)) > 0) {
    safe_write(fout, buf, rbytes);
  }
  return rbytes;
}

size_t concat_files(int f, size_t count, char** files) {
  size_t performed_concats = 0;
  struct stat sb;
  int f_src;

  const char* path;
  for(size_t i=0; i < count; i++) {
    path = files[i];
    if (stat(path, &sb) == 0) {
      if ((sb.st_mode & S_IFMT) == S_IFREG) {
        printf("concat file: %s\n", path);
        if((f_src = open(path, O_RDONLY)) > 0) {
          cat(f, f_src);
          performed_concats++;
        }
      }
    }
  }

  return performed_concats;
}



int main(int argc, char** argv) {

  glob_t globres;
  struct stat sb;
  int i = 1;

  /* concat to a temporary file to perform
   * an atomic replace */
  char tmpfile[] = MOTD".tmp.XXXXXX";

  while(i < argc) {
    if(*argv[i] != '-')
      break;

    if(strcmp(argv[i], "--") == 0) {
      i++;
      break;
    }

    if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      return usage(EXIT_SUCCESS);
    }
    else if(strcmp(argv[i], "--version") == 0) {
      printf(PROGRAM" version "VERSION"\n");
      return(EXIT_SUCCESS);
    }
    else {
      fprintf(stderr, PROGRAM": unknown argument: %s\n", argv[i]);
      return(EXIT_FAILURE);
    }
  }

  if(glob(MOTD_DIR "/*", 0, NULL, &globres) == 0) {
    int ftmp = mkstemp(tmpfile);
    if(ftmp < 0) {
      perror("unable to open");
    }
    else {
      if(stat(MOTD, &sb) >= 0) {
        if(fchown(ftmp, sb.st_uid, sb.st_gid) < 0)
          fprintf(stderr, PROGRAM": unable to chown temporary file %s: %s", tmpfile, strerror(errno));
        if(fchmod(ftmp, sb.st_mode & 07777) < 0)
          fprintf(stderr, PROGRAM": unable to chmod temporary file %s: %s", tmpfile, strerror(errno));
      }
      if(concat_files(ftmp, globres.gl_pathc, globres.gl_pathv) == 0) {
        fprintf(stderr, PROGRAM": unable to concat files. Not overwriting motd");
        if(unlink(tmpfile) < 0) {
          fprintf(stderr, PROGRAM": unable to remove temporary file %s: %s", tmpfile, strerror(errno));
        }
      }
      else {
        rename(tmpfile, MOTD);
      }
    }
  }
  globfree(&globres);
}
