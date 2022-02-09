//#define DEBUG

#include <common.h>

#ifdef __SDCC
    // Stack is at 0xfc4a ~ 63K
    //static __at ((48+6)*1024U) uint8_t screen_copy_ram[3*32*64];
    #define screen_copy ((uint8_t *)((48+6)*1024U))

#else
    static uint8_t screen_copy[3*32*64];

#endif


#define offset_y ((const uint16_t *)((16 + 2 * 8)*1024U))
#define offset_x ((const uint16_t *)((16 + 2 * 8)*1024U + 512U))
#define shift8   ((const uint8_t *)((16 + 2 * 8)*1024U + 1024U))

void copyLine(uint8_t dst, uint8_t src) {

    {
	uint8_t *psrc = &screen_copy[offset_y[src]];
	uint8_t *pdst = &screen_copy[offset_y[dst]];

	UNROLL(32, {
	    *pdst = *psrc;
	    pdst += 0x40;
	    psrc += 0x40;
	});
    }

    {
	uint16_t osrc = MODE2_ADDRESS_PG + offset_y[dst];
	uint8_t *pdst = &screen_copy[offset_y[dst]];

	UNROLL(32, {
	    TMS99X8_setPtr(osrc);
	    TMS99X8_write(*pdst);
	    pdst += 0x40;
	    osrc += 0x40;
	});
    }
}

		
static const uint8_t color_bar[] = { 
	0, FLightRed, FLightRed, FLightRed, FLightRed, FDarkRed,
	0, FLightBlue, FLightBlue, FLightBlue, FLightBlue, FDarkBlue,
	0 };

static const uint8_t color_shade[] = { 
	0, 0, FDarkRed, FDarkRed, FDarkRed, FDarkRed,
	0, 0, FDarkBlue, FDarkBlue, FDarkBlue, FDarkBlue,
	0 };

void draw_color_bar(uint8_t y, uint8_t y_test) {

    uint16_t o = offset_y[y];
    for (uint8_t k=0; k!=48; k+=8) {
		TMS99X8_setPtr(MODE2_ADDRESS_CT + o);
		TMS99X8_write(y_test >=128 ? FLightGreen : FLightRed);
		o += 0x40;   
    }
    
    y_test = y_test & 0x0F;
    
    for (uint8_t k=48; k!=0; k+=8) {
		TMS99X8_setPtr(MODE2_ADDRESS_CT + o);
		TMS99X8_write(color_bar[y_test]);
		o += 0x40;
    }
	
    TMS99X8_setPtr(MODE2_ADDRESS_CT + offset_y[y] + offset_x[96] );
    TMS99X8_write(color_shade[y_test]);
}

static void draw_color_bar_6_A(uint8_t y) {

	TMS99X8_debugBorder(BDarkBlue);
	

    uint16_t o = offset_y[y] + offset_x[48];

    for (uint8_t k=48; k!=0; k+=8) {
		TMS99X8_setPtr(MODE2_ADDRESS_CT + o);

		TMS99X8_write(color_bar[1 + 0]);
		TMS99X8_write(color_bar[1 + 1]);
		TMS99X8_write(color_bar[1 + 2]);

		TMS99X8_write(color_bar[1 + 3]);
		TMS99X8_write(color_bar[1 + 4]);
		TMS99X8_write(color_bar[1 + 5]);
		o += 0x40;
    }
	
    TMS99X8_setPtr(MODE2_ADDRESS_CT + offset_y[y] + offset_x[96] );

    TMS99X8_write(color_shade[1 + 0]);
    TMS99X8_write(color_shade[1 + 1]);
    TMS99X8_write(color_shade[1 + 2]);

    TMS99X8_write(color_shade[1 + 3]);
    TMS99X8_write(color_shade[1 + 4]);
    TMS99X8_write(color_shade[1 + 5]);

	TMS99X8_debugBorder(0);
}

static void draw_color_bar_6_B(uint8_t y) {

	TMS99X8_debugBorder(BDarkBlue);
	

    uint16_t o = offset_y[y] + offset_x[48];

    for (uint8_t k=48; k!=0; k+=8) {
		TMS99X8_setPtr(MODE2_ADDRESS_CT + o);

		TMS99X8_write(color_bar[7 + 0]);
		TMS99X8_write(color_bar[7 + 1]);
		TMS99X8_write(color_bar[7 + 2]);

		TMS99X8_write(color_bar[7 + 3]);
		TMS99X8_write(color_bar[7 + 4]);
		TMS99X8_write(color_bar[7 + 5]);
		o += 0x40;
    }
	
    TMS99X8_setPtr(MODE2_ADDRESS_CT + offset_y[y] + offset_x[96] );

    TMS99X8_write(color_shade[7 + 0]);
    TMS99X8_write(color_shade[7 + 1]);
    TMS99X8_write(color_shade[7 + 2]);

    TMS99X8_write(color_shade[7 + 3]);
    TMS99X8_write(color_shade[7 + 4]);
    TMS99X8_write(color_shade[7 + 5]);

	TMS99X8_debugBorder(0);
}


static void push_up_lines_6(uint8_t idx) {

	TMS99X8_debugBorder(BDarkRed);

    {
		uint8_t *psrc = &screen_copy[offset_y[idx+1]];
		uint8_t *pdst = &screen_copy[offset_y[idx]];

		for (uint8_t k=0; k<32; k++) {
			UNROLL(6, {
				*pdst = *psrc;
				pdst++;
				psrc++;
			});
			pdst += 0x40-6;
			psrc += 0x40-6;
		}
    }

    {
		uint16_t osrc = MODE2_ADDRESS_PG + offset_y[idx];
		uint8_t *pdst = &screen_copy[offset_y[idx]];

		for (uint8_t k=0; k<32; k++) {
			
			TMS99X8_setPtr(osrc);
			UNROLL(6, {
				TMS99X8_write(*pdst);
				osrc++;
				pdst++;
			});
			pdst += 0x40-6;
			osrc += 0x40-6;
		}
    }

	TMS99X8_debugBorder(0);
}


void push_bar_up(uint8_t y, uint8_t verified) {

	TMS99X8_debugBorder(BDarkGreen);
    
    copyLine(y, y+1); draw_color_bar(y+0,0+(verified?0x80:00));
    
    if (0) {
		for (uint8_t k=1; k<13; k++) {
			copyLine(y+k, y+1+k); 
			draw_color_bar(y+k,k+(verified?0x80:00));
		}
			
		return;
	}
   
	if (((y+1) & 63) > 57) {
	
		copyLine(y+1, y+2); draw_color_bar(y+1,1+(verified?0x80:00));
		copyLine(y+2, y+3); draw_color_bar(y+2,2+(verified?0x80:00));
		copyLine(y+3, y+4); draw_color_bar(y+3,3+(verified?0x80:00));

		copyLine(y+4, y+5); draw_color_bar(y+4,4+(verified?0x80:00));
		copyLine(y+5, y+6); draw_color_bar(y+5,5+(verified?0x80:00));
		copyLine(y+6, y+7); draw_color_bar(y+6,6+(verified?0x80:00));

    } else {
	
		draw_color_bar_6_A(y+1);
		push_up_lines_6(y+1);
    }

    if (((y+7) & 63) > 57) {
	
		copyLine(y+ 7, y+ 8); draw_color_bar(y+ 7, 7+(verified?0x80:00));
		copyLine(y+ 8, y+ 9); draw_color_bar(y+ 8, 8+(verified?0x80:00));
		copyLine(y+ 9, y+10); draw_color_bar(y+ 9, 9+(verified?0x80:00));

		copyLine(y+10, y+11); draw_color_bar(y+10,10+(verified?0x80:00));
		copyLine(y+11, y+12); draw_color_bar(y+11,11+(verified?0x80:00));
		copyLine(y+12, y+13); draw_color_bar(y+12,12+(verified?0x80:00));

    } else {
	
		draw_color_bar_6_B(y+7);
		push_up_lines_6(y+7);
    }

	TMS99X8_debugBorder(0);
}

