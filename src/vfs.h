typedef struct SuperBlock *(*FS_detect_cb)(BlockDev *dev);
extern void FS_register(FS_detect_cb probe);

typedef struct MBR {
   uint16_t bootstrap
