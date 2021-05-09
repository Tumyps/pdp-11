#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "mem.h"
#include "run.h"


void do_halt() {
	printf("THE END!!!\n");
	print_reg();
	exit(0);
}

void do_mov() {
	w_write(dd.adr, ss.val);
}

void do_add() {
}

void do_unknown() {
}