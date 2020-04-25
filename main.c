#include <joystick.h>
#include <nes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "neslib.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name (push,"ZEROPAGE")

u8 oam_off;

#pragma data-name(pop)
#pragma bss-name (pop)

void str(const char *msg) {
	while (*msg) {
		vram_put(*msg - ' ');
		msg++;
	}
}

static void fill() {

	ppu_off();
	vram_adr(NAMETABLE_A);
	vram_adr(NTADR_A(2, 2));
	str("FOR GOD SO LOVED THE WORLD");
    vram_adr(NTADR_A(2, 4));
    str("THAT HE GAVE HIS ONLY");
    vram_adr(NTADR_A(2, 6));
    str("BEGOTTEN SON, THAT WHOSOEVER");
    vram_adr(NTADR_A(2, 8));
    str("BELIEVETH IN HIM SHOULD NOT");
    vram_adr(NTADR_A(2, 10));
    str("PERISH, BUT HAVE EVERLASTING");
    vram_adr(NTADR_A(2, 12));
    str("LIFE.");
  	ppu_on_all();
}

void splitXY(unsigned x, unsigned y);

int main() {

	char buf[32];
	static char bgbuf[256];

	u8 ctrl, prevctrl;
	u8 i;
	u16 x = 240, y = 128;
	u8 frames = 0, len;

	bgbuf[0] = NT_UPD_EOF;
	set_vram_update(bgbuf);

	joy_install(joy_static_stddrv);

	pal_col(0, 0xf);
	pal_col(1, 0x30);
	pal_col(2, 0x31); // blue
	pal_col(3, 0x35); // pink

	pal_col(17, 0x30);

	fill();
	oam_clear();

	// Sprite 0 hit
	oam_spr(0, 31, 0x3b, 0, 0);

	while (1) {
		bgbuf[0] = NT_UPD_EOF;
		ctrl = joy_read(0);

		ppu_wait_nmi();
		++frames;
		prevctrl = ctrl;
	}

	return 0;
}
