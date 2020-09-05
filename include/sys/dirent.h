#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/lock.h>

struct dirent
  {
#ifndef __USE_FILE_OFFSET64
    __ino_t d_ino;
    __off_t d_off;
#else
    __ino64_t d_ino;
    __off64_t d_off;
#endif
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];		/* We must not include limits.h! */
  };

#ifdef __USE_LARGEFILE64
struct dirent64
  {
    __ino64_t d_ino;
    __off64_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];		/* We must not include limits.h! */
  };
#endif

#define d_fileno	d_ino	/* Backwards compatibility.  */

#undef  _DIRENT_HAVE_D_NAMLEN
#define _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_OFF
#define _DIRENT_HAVE_D_TYPE

#define HAVE_NO_D_NAMLEN	/* no struct dirent->d_namlen */
#define HAVE_DD_LOCK  		/* have locking mechanism */

#define MAXNAMLEN 255		/* sizeof(struct dirent.d_name)-1 */

typedef struct {
    int dd_fd;		/* directory file */
    int dd_loc;		/* position in buffer */
    int dd_seek;
    char *dd_buf;	/* buffer */
    int dd_len;		/* buffer length */
    int dd_size;	/* amount of data in buffer */
    _LOCK_RECURSIVE_T dd_lock;
} DIR;


#define __dirfd(dir) (dir)->dd_fd

/* --- redundant --- */

DIR *opendir(const char *);
struct dirent *readdir(DIR *);
int readdir_r(DIR *__restrict, struct dirent *__restrict,
              struct dirent **__restrict);
void rewinddir(DIR *);
int closedir(DIR *);

#ifdef __USE_LARGEFILE64
struct dirent64 *readdir64 (DIR *);
int readdir64_r (DIR *__restrict, struct dirent64 *__restrict,
			struct dirent64 **__restrict);
#endif

/* internal prototype */
void _seekdir(DIR *dir, long offset);
DIR *_opendir(const char *);

#ifndef _POSIX_SOURCE
long telldir (DIR *);
void seekdir (DIR *, off_t loc);

int scandir (const char *__dir,
             struct dirent ***__namelist,
             int (*select) (const struct dirent *),
             int (*compar) (const struct dirent **, const struct dirent **));

int alphasort (const struct dirent **__a, const struct dirent **__b);
#else
long telldir (DIR *);
void seekdir (DIR *, off_t loc);
    
#endif /* _POSIX_SOURCE */

#ifdef __cplusplus
}
#endif

#endif
