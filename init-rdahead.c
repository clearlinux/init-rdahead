#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef DEBUG
#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__ );
#else
#define DEBUG_PRINT(...)
#endif

static char *ra_fns[] = {
	"/usr/lib64/ld-2.23.so",
	"/usr/lib/systemd/systemd-bootchart",
	"/usr/lib64/libc-2.23.so",
	"/usr/lib64/libgcc_s.so.1",
	"/usr/lib/systemd/systemd",
	"/usr/lib64/libpthread.so.0",
	"/usr/lib64/libcap.so.2",
	"/usr/lib64/librt.so.1",
	"/usr/lib64/libpam.so.0",
	"/usr/lib64/libkmod.so.2",
	"/usr/lib64/libmount.so.1",
	"/usr/lib64/libdl.so.2",
	"/usr/lib64/libblkid.so.1",
	"/usr/lib64/libuuid.so.1",
	"/usr/lib/systemd/system-generators/systemd-fstab-generator",
	"/usr/lib/systemd/system-generators/systemd-debug-generator",
	"/usr/bin/kmod",
	"/usr/bin/mount",
	"/usr/lib64/libattr.so.1",
	"/usr/lib64/libacl.so.1",
	"/usr/lib/systemd/systemd-random-seed",
	"/usr/lib/systemd/systemd-vconsole-setup",
	"/usr/lib/systemd/systemd-udevd",
	"/usr/lib64/liblz4.so.1",
	"/usr/bin/udevadm",
	"/usr/lib/systemd/systemd-journald",
	"/usr/bin/systemd-tmpfiles",
	"/usr/bin/clr_power",
	"/usr/lib/systemd/systemd-timesyncd",
	NULL
};

int main(void)
{
	int i, fd;
	struct stat st;
	pid_t pid = fork();

	if (pid == -1) {
		DEBUG_PRINT("fork failed\n");
		return 1;
	} else if (pid > 0 ) {
		usleep(5);
		execl("/usr/lib/systemd/systemd-bootchart", "systemd-bootchart", NULL);
	} else {
		DEBUG_PRINT("readahead files:\n");
		for (i = 0; ra_fns[i] != NULL; i++) {
			DEBUG_PRINT("%s\n", ra_fns[i]);
			fd = open(ra_fns[i], O_RDONLY);
			if (!fd) {
				DEBUG_PRINT("open failed to open %s\n", ra_fns[i]);
			}
			if (fstat(fd, &st) < 0) {
				DEBUG_PRINT("fstat failed on %s\n", ra_fns[i]);
			}
			if (readahead(fd, 0, st.st_size) < 0) {
				DEBUG_PRINT("readahead failure on %s: %s\n", ra_fns[i], strerror(errno));
			}
		}
	}

	return 0;
}

