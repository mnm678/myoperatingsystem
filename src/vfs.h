#ifndef VFS
#define VFS

#include "block_device.h"
#include "printk.h"
#include "types.h"

typedef struct SuperBlock *(*FS_detect_cb)(BlockDev *dev);
extern void FS_register(FS_detect_cb probe);

typedef struct File {
   struct Inode *inode;
   size_t offset;
   int (*read)(struct File*, char *dst, size_t len);
   int (*write)(struct File*, char *src, size_t len);
   int (*lseek)(struct File*, size_t off);
   int (*close)(struct File**);
} File;

typedef int (*readdir_cb)(const char *name, uint64_t inode_num, void *);

typedef struct Inode {
   size_t size;
   /*struct timeval mod_time, acc_time, create_time these need timing interrupt*/
   mode_t st_mode;
   uid_t uid;
   gid_t gid;
   uint64_t ino_num;
   File* (*open)(struct Inode*);
   readdir_cb cb;
   int (*read_dir)(struct Inode*, readdir_cb, void *);
   int (*unlink)(struct Inode*, const char * name);
   void (*free)(struct Inode **);
} Inode;

typedef struct SuperBlock {
   Inode *root_inode;
   Inode *(*read_inode)(struct SuperBlock*, uint64_t inode);
   char *name;
   char *type;
   int (*sync_fs)(struct SuperBlock*);
   void (*put_super)(struct SuperBlock*);
} SuperBlock;

#endif
