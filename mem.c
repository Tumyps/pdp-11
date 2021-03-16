#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef word Adress;

#define MEMSIZE (64 * 1024)

byte mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem()
{
	byte b0 = 0x0a;

	b_write(2, b0);
	byte bres = b_read(2);
	printf("%02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);

	Adress a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a + 1, b1);
	word wres = w_read(a);
	printf("ww/br \t %04hx=%02hhx%02hhx\n", wres, b1, b0);
	assert(w == wres);

	w_write(a, w);
	wres = w_read(a);
	printf("ww/wr %04hx=%04hx\n", wres, w);
	assert(w == wres);
}

int main () {
	test_mem();
	return 0;
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

void w_write(Adress adr, word w){
	mem[adr] = w & 511;
	mem[adr + 1] = w >> 8;
}