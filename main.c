#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "mem.h"
#include "run.h"


int main (int argc, char * argv[]) {
	char * filename = NULL;
	if (argc > 1)
		filename = argv[1];
	else
		printf("EMPTY FILE NAME!!!\n");

	load_file(filename);
	run();
	return 0;
}
