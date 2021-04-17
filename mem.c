#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef word Adress;

#define MEMSIZE (64 * 1024)
#define COMMAND_SET_SIZE 4

byte mem[MEMSIZE];

word reg[8];
#define pc reg[7]

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void load_file(const char * filename);
void mem_dump(Adress start, word n);
void do_add();
void do_mov();
void do_halt();
void do_unknown();


typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
} Command;
Command cmd[] = {
	{0177777, 0000000, "halt", do_halt},
	{0170000, 0010000, "mov",  do_mov},
	{0170000, 0060000, "add",  do_add},
	{0170000, 0000000, "unknown", 	do_unknown}
};

void test_mem()
{
	load_file("data.txt");
	mem_dump(0x40, 4);
}

void run() {
	pc = 01000;
	while (1) {
		word w = w_read(pc);
		printf("%06o %06o: ", pc, w);
		pc += 2;
		for (int i = 0; i < COMMAND_SET_SIZE; ++i) {
			Command com = cmd[i];
			if ((w & com.mask) == com.opcode) {
				printf("%s\n", com.name);
				com.do_func();
			}
		}
	}
}

int main (int argc, char * argv[]) {
	char * filename = "data.txt";

	load_file(filename);
	run();
	return 0;
}

void do_halt() {
	printf("THE END!!!\n");
	exit(0);
}

void do_mov() {
}

void do_add() {
}

void do_unknown() {
}

word w_read(Adress a) {
	word w = ((word)mem[a + 1]) << 8;
	//printf("w = %x\n", w);
	w = w | mem[a];
	return w;
}

void b_write(Adress adr, byte b) {
	mem[adr] = b;
}

byte b_read(Adress adr) {
	return mem[adr];
}

void w_write(Adress adr, word w) {
	mem[adr] = w & 0xFF;
	mem[adr + 1] = w >> 8;
}

void load_file(const char * filename) {
	FILE * fin  = fopen(filename, "r");
	if (fin == NULL) {
		perror("data.txt");
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
