#pragma once

#include "mem.h"

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
	char params;
} Command;

#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define pc reg[7]

typedef struct
{
	word val;
	word adr;
} Arg;

extern Arg ss, dd;

void run();
void print_reg();
