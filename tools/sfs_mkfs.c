#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define		_FILE_OFFSET_BITS 64


typedef struct {
	char			padding[404];
	unsigned int		timestamp_l;
	unsigned int		timestamp_h;
	unsigned int		data_area_sz 	: 64;
	unsigned int		index_area_sz 	: 64;
	unsigned int		magic_number;
	unsigned int		volume_sz	: 64;
	unsigned int		reserved_blocks;
	unsigned int		block_size 	: 8;
	unsigned int		checksum	: 8;
	char			dostable_compat[66];
} __attribute__((packed)) SUPERBLOCK;



//int writeSuperBlock(FILE *fp, off_t volume_size, int block_size) {


int main(int argv, char **argv) {
	FILE *fp;
	int blocksize, time;
	char buff[512];
	off_t volume_size;

	if (argc <3) {
		fprintf(stderr, "Usage: %s <volume> <blocksize>\n", argv[0]);
		return -1;
	}

	blocksize = atoi(argv[2]);

	if ((fp = fopen(argv[1], "r+b")) == NULL) {
		fprintf(stderr, "Error: Unable to open volume %s for read/write\n", argv[1]);
		return -1;
	}

	if (blocksize < 512) {
		fprintf(stderr, "Block-size needs to be >= 512 Bytes\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	volume_size = ftello(fp);
	fseek(fp, 0, SEEK_SET);

	time = time(NULL);

