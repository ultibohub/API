#ifndef _STATFS_H_
#define _STATFS_H_

#include <sys/_types.h>

typedef struct {
	int	val[2];
} _fsid_t;

struct statfs {
	__uint32_t f_type;
	__uint32_t f_bsize;
	__uint32_t f_blocks;
	__uint32_t f_bfree;
	__uint32_t f_bavail;
	__uint32_t f_files;
	__uint32_t f_ffree;
	_fsid_t f_fsid;
	__uint32_t f_namelen;
	__uint32_t f_frsize;
	__uint32_t f_flags;
	__uint32_t f_spare[4];
};

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

int statfs(const char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);

int statfs64(const char *path, struct statfs64 *buf);
int fstatfs64(int fd, struct statfs64 *buf);

#endif /* !_STATFS_H_ */