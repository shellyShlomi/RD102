#ifndef ILRD_RD102_EXT2_H
#define ILRD_RD102_EXT2_H

int PrintSuperblock(const char *device_path);
int PrintGroupDescriptor(const char *device_path);
int PrintFileContent(const char *device_path, const char *file_path);

#endif /* ILRD_RD102_EXT2_H */