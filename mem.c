#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "mem.h"
#include "run.h"



byte mem[MEMSIZE];

/*void test_mem()
{
	load_file("data.txt");
	mem_dump(0x40, 4);
}*/

word w_read(Adress a) {
	word w = ((word)mem[a + 1]) << 8;
	//printf("w = %x\n", w);
	w = w | mem[a];
	return w;
}

void b_write(Adress adr, byte b) {
	if (adr < 8)
		reg[adr] = (word)b;
	mem[adr] = b;
}

byte b_read(Adress adr) {
	return mem[adr];
}

void w_write(Adress adr, word w) {
	if (adr < 8)
		reg[adr] = w;
	mem[adr] = w & 0xFF;
	mem[adr + 1] = w >> 8;
}

void load_file(const char * filename) {
	FILE * fin  = fopen(filename, "r");
	if (fin == NULL) {
		char * buf = malloc(sizeof(char) * (strlen(filename) + 100));
		sprintf(buf, "Cannot open the file: %s", filename);
		perror(buf);
		free(buf);
		exit(errno);
	}


	int adr, n;
	while (fscanf(fin, "%x%x", &adr, &n) == 2)
	{
		for (int i = 0; i < n; ++i)
		{
			int val;
			fscanf(fin, "%x", &val);
			b_write (adr + i, (byte)val);
		}
	}

	fclose(fin);
}

void mem_dump(Adress start, word n) {
	FILE* f = stdout;
	for (Adress a = start; a < start + n; a += 2)
	{
		fprintf(f, "%06o : %06o\n", a, w_read(a));
	}
}
