#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>

int main() {
	int ret;
	ssize_t sz;
	int fd;
	uint8_t buf[1];

	fd = open("/dev/i2c-1", O_RDWR);
	if (fd < 0) {
		perror("open");
		return 1;
	}
	ret = ioctl(fd, I2C_SLAVE, 0x76);
	if (ret < 0) {
		perror("ioctl");
		return 1;
	}
	buf[0] = 0xD0;
	sz = write(fd, buf, 1);
	if (sz != 1) {
		perror("write");
		return 1;
	}
	sz = read(fd, buf, 1);
	if (sz != 1) {
		perror("read");
		return 1;
	}
	printf("0xD0: %02x\n", buf[0]);

	puts("OK");
	return 0;
}
