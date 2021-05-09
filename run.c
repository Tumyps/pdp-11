#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "mem.h"
#include "run.h"
#include "do_func.h"

word reg[8];

Arg ss, dd;
int is_byte;

Command cmd[] = {
	{0177777, 0000000, "halt", do_halt},
	{0170000, 0010000, "mov",  do_mov},
	{0170000, 0060000, "add",  do_add},
	{0000000, 0000000, "unknown", 	do_unknown}
};


Arg get_mr(word w) {
	Arg res;
	int r = w & 7;
	int mode = (w >> 3) & 7;
	switch (mode) {
	case 0:		// R3
		res.adr = r;
		res.val = reg[r];
		printf("R%o ", r);
		break;
	case 1:		// (R3)
		res.adr = reg[r];
		if(is_byte)
			res.val = b_read(res.adr);
		else
			res.val = w_read(res.adr);
		printf("(R%o) ", r);
		break;
	case 2:		// (R3)+	#3
		res.adr = reg[r];
		
		if(is_byte)
			res.val = b_read(res.adr);
		else
			res.val = w_read(res.adr);

		reg[r] += 2 - is_byte;
		
		if (r == 7)
			printf("#%o ", res.val);
		else
			printf("(R%o)+", r);
		break;
	default:
		fprintf(stderr, "Mode %o NOT IMPLEMENTED YET\n", mode);
		exit(1);
	}
	return res;
}

void run() {
	pc = 01000;
	while (1) {
		word w = w_read(pc);
		printf("%06o %06o: ", pc, w);
		pc += 2;
		is_byte = (w >> 15) & 1;
		for (int i = 0; cmd[i].mask == 0; ++i) {
			Command com = cmd[i];
			if ((w & com.mask) == com.opcode) {
				printf("%s ", com.name);
				if (com.params & HAS_SS)
					ss = get_mr(w >> 6);
				if (com.params & HAS_DD)
					dd = get_mr(w);
				com.do_func();
				printf("\n");
				print_reg();
				break;
			}
		}
	}
}

void print_reg() {
	for (int i = 0; i < 6; ++i)
		printf("R%d=%06o ", i, reg[i]);
	printf("SP=%06o PC=%06o\n", reg[6], reg[7]);
}