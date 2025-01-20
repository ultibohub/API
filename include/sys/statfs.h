#ifndef _STATFS_H_
#define _STATFS_H_

#include <sys/_types.h>

typedef struct {
	int	val[2];
} _fsid_t;

struct statfs {
	__uint32_t f_type;
	__uint32_t f_bsize;
#ifndef _FILE_OFFSET64
	__uint32_t f_blocks;
	__uint32_t f_bfree;
	__uint32_t f_bavail;
	__uint32_t f_files;
	__uint32_t f_ffree;
#else
	__uint64_t f_blocks;
	__uint64_t f_bfree;
	__uint64_t f_bavail;
	__uint64_t f_files;
	__uint64_t f_ffree;
#endif
	_fsid_t f_fsid;
	__uint32_t f_namelen;
	__uint32_t f_frsize;
	__uint32_t f_flags;
	__uint32_t f_spare[4];
};

#ifdef __LARGE64_FILES
struct statfs64 {
	__uint32_t f_type;
	__uint32_t f_bsize;
	__uint64_t f_blocks;
	__uint64_t f_bfree;
	__uint64_t f_bavail;
	__uint64_t f_files;
	__uint64_t f_ffree;
	_fsid_t f_fsid;
	__uint32_t f_namelen;
	__uint32_t f_frsize;
	__uint32_t f_flags;
	__uint32_t f_spare[4];
};
#endif

/* Definitions for f_type */
#define EXT_SUPER_MAGIC 0x137D
#define EXT2_SUPER_MAGIC 0xEF53
#define EXT3_SUPER_MAGIC 0xEF53
#define EXT4_SUPER_MAGIC 0xEF53
#define MSDOS_SUPER_MAGIC 0x4d44
#define NTFS_SB_MAGIC 0x5346544e
#define SMB_SUPER_MAGIC 0x517B

int statfs(const char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);

#ifdef __LARGE64_FILES
int statfs64(const char *path, struct statfs64 *buf);
int fstatfs64(int fd, struct statfs64 *buf);
#endif

#endif /* !_STATFS_H_ */