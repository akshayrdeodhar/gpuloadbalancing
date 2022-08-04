#include "lib/criu.h"
#include <sys/socket.h>

#define MAX 128
#define SHARED_FS_PATH "/mnt/dump"

typedef int dumpme;

typedef struct {
	char path[MAX]; /* path to process image, rooted at NFS mountpoint */
}loadproc;

int main(void) {
