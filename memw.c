#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef word Adress;

#define MEMSIZE (64 * 1024)

word mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem()
{
	word w0 = 0x0b0a;

	w_write(2, w0);
	word wres = w_read(2);
	printf("%04hx = %04hx\n", w0, wres);
	assert(w0 == wres);

	Adress a = 4;
	byte b1 = 0xcb;
	byte b0 = 0x0a;
	word w = 0xcb0a;
	w_write(a, w);
	word b0res = b_read(a);
	word b1res = b_read(a + 1);
	printf("ww/br \t %04hx=%02hhx%02hhx\n", w, b1res, b0res);
	assert(b0 == b0res);
	assert(b1 == b1res);
}

int main () {
	test_mem();
	return 0;
}

word w_read(Adress adr) {
	assert(adr % 2 == 0);
	return mem[adr];
}

void w_write(Adress adr, word w) {
	assert(adr % 2 == 0);
	mem[adr] = w;
}

byte b_read(Adress a) {
	byte b;
	if (a % 2 == 0)
		b = mem[a] & 0xFF;
	else {
		word w = mem[a - 1];
		b = w >> 8 & 0xFF;
	}
	return b;
}

void b_write(Adress a, byte b) {
	if (a % 2 == 0)
		mem[a] = b;
	else
		mem[a - 1] = b << 8;
}

