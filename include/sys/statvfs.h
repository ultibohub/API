#ifndef _STATVFS_H_
#define _STATVFS_H_

#include <sys/_types.h>

typedef struct {
	int	val[2];
} __fsid_t;

struct statvfs
  {
    unsigned long int f_bsize;
    unsigned long int f_frsize;
#ifndef _FILE_OFFSET64
    __fsblkcnt_t f_blocks;
    __fsblkcnt_t f_bfree;
    __fsblkcnt_t f_bavail;
    __fsfilcnt_t f_files;
    __fsfilcnt_t f_ffree;
    __fsfilcnt_t f_favail;
#else
    __fsblkcnt64_t f_blocks;
    __fsblkcnt64_t f_bfree;
    __fsblkcnt64_t f_bavail;
    __fsfilcnt64_t f_files;
    __fsfilcnt64_t f_ffree;
    __fsfilcnt64_t f_favail;
#endif
    __fsid_t f_fsid;
    unsigned long int f_flag;
    unsigned long int f_namemax;
    unsigned int f_spare[6];
  };

#ifdef __LARGE64_FILES

/* Definitions missing from sys/_types.h */
#ifndef __machine_fsblkcnt64_t_defined
typedef __uint64_t __fsblkcnt64_t;
#endif

#ifndef __machine_fsfilcnt64_t_defined
typedef __uint64_t __fsfilcnt64_t;
#endif

struct statvfs64
  {
    unsigned long int f_bsize;
    unsigned long int f_frsize;
    __fsblkcnt64_t f_blocks;
    __fsblkcnt64_t f_bfree;
    __fsblkcnt64_t f_bavail;
    __fsfilcnt64_t f_files;
    __fsfilcnt64_t f_ffree;
    __fsfilcnt64_t f_favail;
    __fsid_t f_fsid;
    unsigned long int f_flag;
    unsigned long int f_namemax;
    unsigned int f_spare[6];
  };
#endif

/* Definitions for the flag in `f_flag'.  */
enum
{
  ST_RDONLY = 1,
#define ST_RDONLY	ST_RDONLY
  ST_NOSUID = 2
#define ST_NOSUID	ST_NOSUID
};

int statvfs (__const char *__restrict __file, struct statvfs *__restrict __buf);
int fstatvfs (int __fildes, struct statvfs *__buf);

#ifdef __LARGE64_FILES
int statvfs64 (__const char *__restrict __file, struct statvfs64 *__restrict __buf);
int fstatvfs64 (int __fildes, struct statvfs64 *__buf);
#endif

#endif /* !_STATVFS_H_ */
