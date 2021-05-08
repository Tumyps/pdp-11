#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "mem.c"

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
	char params;
} Command;
Command cmd[] = {
	{0177777, 0000000, "halt", do_halt},
	{0170000, 0010000, "mov",  do_mov},
	{0170000, 0060000, "add",  do_add},
	{0170000, 0000000, "unknown", 	do_unknown}
};

typedef struct 
{
	word val;
	word adr;
} Arg;
Arg ss, dd;

Arg get_mr(word w){
	Arg res;
	int r = w & 7;
	int mode = (w >> 3) & 7;
	switch(mode){
		case 0:		// R3
			res.adr = r;
			res.val = reg[r];
			printf("R%o ", r);
			break;
		case 1:		// (R3)
			res.adr = reg[r];
			res.val = w_read(res.adr);
			printf("R%o ", r);
			break;
		case 2:		// (R3)+	#3
			res.adr = reg[r];
			res.val = w_read(res.adr);
			reg[r] += 2;
			if(r == 7)
				printf("#%o ", res.val);
			else 
				printf("(R%o)", r);
			break;
		default:
			fprintf(stderr, "Mode %o NOT IMPLEMENTED YET\n", mode);
			exit(1);
	}
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

