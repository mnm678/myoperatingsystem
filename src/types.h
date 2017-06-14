#ifndef TYPESH
#define TYPESH

#define size_t uint64_t
#define uid_t uint64_t
#define gid_t uint64_t
#define NULL 0
#define ERR_RET ((void *) -1)

#define mode_t uint16_t
#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

#endif
