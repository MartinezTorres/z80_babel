#include <common.h>

static
__at ((16 + 2 * 8)*1024U) 
const uint16_t offset_y_ct[256] = {
0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 
0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 
0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 
0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 
0x0800, 0x0801, 0x0802, 0x0803, 0x0804, 0x0805, 0x0806, 0x0807, 0x0808, 0x0809, 0x080A, 0x080B, 0x080C, 0x080D, 0x080E, 0x080F, 
0x0810, 0x0811, 0x0812, 0x0813, 0x0814, 0x0815, 0x0816, 0x0817, 0x0818, 0x0819, 0x081A, 0x081B, 0x081C, 0x081D, 0x081E, 0x081F, 
0x0820, 0x0821, 0x0822, 0x0823, 0x0824, 0x0825, 0x0826, 0x0827, 0x0828, 0x0829, 0x082A, 0x082B, 0x082C, 0x082D, 0x082E, 0x082F, 
0x0830, 0x0831, 0x0832, 0x0833, 0x0834, 0x0835, 0x0836, 0x0837, 0x0838, 0x0839, 0x083A, 0x083B, 0x083C, 0x083D, 0x083E, 0x083F, 
0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, 0x1008, 0x1009, 0x100A, 0x100B, 0x100C, 0x100D, 0x100E, 0x100F, 
0x1010, 0x1011, 0x1012, 0x1013, 0x1014, 0x1015, 0x1016, 0x1017, 0x1018, 0x1019, 0x101A, 0x101B, 0x101C, 0x101D, 0x101E, 0x101F, 
0x1020, 0x1021, 0x1022, 0x1023, 0x1024, 0x1025, 0x1026, 0x1027, 0x1028, 0x1029, 0x102A, 0x102B, 0x102C, 0x102D, 0x102E, 0x102F, 
0x1030, 0x1031, 0x1032, 0x1033, 0x1034, 0x1035, 0x1036, 0x1037, 0x1038, 0x1039, 0x103A, 0x103B, 0x103C, 0x103D, 0x103E, 0x103F, 
0x1800, 0x1801, 0x1802, 0x1803, 0x1804, 0x1805, 0x1806, 0x1807, 0x1808, 0x1809, 0x180A, 0x180B, 0x180C, 0x180D, 0x180E, 0x180F, 
0x1810, 0x1811, 0x1812, 0x1813, 0x1814, 0x1815, 0x1816, 0x1817, 0x1818, 0x1819, 0x181A, 0x181B, 0x181C, 0x181D, 0x181E, 0x181F, 
0x1820, 0x1821, 0x1822, 0x1823, 0x1824, 0x1825, 0x1826, 0x1827, 0x1828, 0x1829, 0x182A, 0x182B, 0x182C, 0x182D, 0x182E, 0x182F, 
0x1830, 0x1831, 0x1832, 0x1833, 0x1834, 0x1835, 0x1836, 0x1837, 0x1838, 0x1839, 0x183A, 0x183B, 0x183C, 0x183D, 0x183E, 0x183F, 
};

static 
__at ((16 + 2 * 8)*1024U +  512U) 
const uint16_t offset_x_ct[256] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 
0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 
0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 0x0140, 
0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x01C0, 0x01C0, 0x01C0, 0x01C0, 0x01C0, 0x01C0, 0x01C0, 0x01C0, 
0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0240, 0x0240, 0x0240, 0x0240, 0x0240, 0x0240, 0x0240, 0x0240, 
0x0280, 0x0280, 0x0280, 0x0280, 0x0280, 0x0280, 0x0280, 0x0280, 0x02C0, 0x02C0, 0x02C0, 0x02C0, 0x02C0, 0x02C0, 0x02C0, 0x02C0, 
0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0300, 0x0340, 0x0340, 0x0340, 0x0340, 0x0340, 0x0340, 0x0340, 0x0340, 
0x0380, 0x0380, 0x0380, 0x0380, 0x0380, 0x0380, 0x0380, 0x0380, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 0x03C0, 
0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0440, 0x0440, 0x0440, 0x0440, 0x0440, 0x0440, 0x0440, 0x0440, 
0x0480, 0x0480, 0x0480, 0x0480, 0x0480, 0x0480, 0x0480, 0x0480, 0x04C0, 0x04C0, 0x04C0, 0x04C0, 0x04C0, 0x04C0, 0x04C0, 0x04C0, 
0x0500, 0x0500, 0x0500, 0x0500, 0x0500, 0x0500, 0x0500, 0x0500, 0x0540, 0x0540, 0x0540, 0x0540, 0x0540, 0x0540, 0x0540, 0x0540, 
0x0580, 0x0580, 0x0580, 0x0580, 0x0580, 0x0580, 0x0580, 0x0580, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 0x05C0, 
0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 
0x0680, 0x0680, 0x0680, 0x0680, 0x0680, 0x0680, 0x0680, 0x0680, 0x06C0, 0x06C0, 0x06C0, 0x06C0, 0x06C0, 0x06C0, 0x06C0, 0x06C0, 
0x0700, 0x0700, 0x0700, 0x0700, 0x0700, 0x0700, 0x0700, 0x0700, 0x0740, 0x0740, 0x0740, 0x0740, 0x0740, 0x0740, 0x0740, 0x0740, 
0x0780, 0x0780, 0x0780, 0x0780, 0x0780, 0x0780, 0x0780, 0x0780, 0x07C0, 0x07C0, 0x07C0, 0x07C0, 0x07C0, 0x07C0, 0x07C0, 0x07C0, 
};

static 
__at ((16 + 2 * 8)*1024U +  1024U) 
const uint8_t shift8_ct[256] = {
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 
};

#define offset_y ((const uint16_t *)((16 + 2 * 8)*1024U))
#define offset_x ((const uint16_t *)((16 + 2 * 8)*1024U + 512U))
#define shift8   ((const uint8_t *)((16 + 2 * 8)*1024U + 1024U))


T_SA SA;

TTextProperties textProperties;

#ifdef __SDCC
    // Stack is at 0xfc4a ~ 63K
    static __at ((48+6)*1024U) uint8_t screen_copy_ram[3*32*64];
    #define screen_copy ((uint8_t *)((48+6)*1024U))

#else
    static uint8_t screen_copy[3*32*64];

#endif


void initCanvas() {
    
    UNUSED(offset_x_ct);
    UNUSED(offset_y_ct);
    UNUSED(shift8_ct);
    
    // Activates mode 2 and clears the screen (in black)
    TMS99X8_activateMode2(); 


    // Disables individually all sprites
    for (uint8_t n=0; n<32; n++) { SA[n].y = 209; }
    TMS99X8_writeSpriteAttributes0(SA);
    
    // Enables 16 pixel sprites
    TMS99X8.sprites16 = true;
    TMS99X8_syncFlags();

    // Places the tiles in a way that columns are consective tiles
    {
        uint8_t i=0;
        do {
            screen_copy[((i<<5)&0xFF) + (i>>3)] = i;
        } while (++i != 0);
    }
    
    TMS99X8_memcpy(MODE2_ADDRESS_PN0 + 0x0000, (const uint8_t *)screen_copy, 256);    
    TMS99X8_memcpy(MODE2_ADDRESS_PN0 + 0x0100, (const uint8_t *)screen_copy, 256);    
    TMS99X8_memcpy(MODE2_ADDRESS_PN0 + 0x0200, (const uint8_t *)screen_copy, 256);    

    TMS99X8_memset(MODE2_ADDRESS_PG, 0, sizeof(T_PG));
    memset(screen_copy,0,3*32*64);

    TMS99X8_memset(MODE2_ADDRESS_CT, FWhite + BTransparent, sizeof(T_CT));
    
    //history_pt = 0;

    memset(&textProperties,0,sizeof(textProperties));

    textProperties.font_segment = ML_SEGMENT_D(font_thin);
    textProperties.font_pts = font_thin_pts;
    textProperties.font_pos = font_thin_pos;
    textProperties.font_len = font_thin_len;
    
    textProperties.value = 1;
    textProperties.color = FWhite + BTransparent;
    textProperties.sz = 1;
    textProperties.space_between_lines = 7;
    
//    setROI(0,0,255,191);

    TMS99X8.blankScreen = 1;
    TMS99X8_syncRegister(1);
}

void repaintScreen() {

    TMS99X8_memcpy(MODE2_ADDRESS_PG, (const uint8_t *)screen_copy, sizeof(T_PG));    
}

void setPoints_v8(uint8_t x, uint8_t y, uint8_t value) {

    uint16_t offset = offset_x[x] + offset_y[y];
    TMS99X8_setPtr(MODE2_ADDRESS_PG + offset);
    TMS99X8_write(screen_copy[offset] = value);
}


void setPoints_v8c(uint8_t x, uint8_t y, uint8_t value, uint8_t color) {

    uint16_t offset = offset_x[x] + offset_y[y];
    TMS99X8_setPtr(MODE2_ADDRESS_PG + offset);
    TMS99X8_write(screen_copy[offset] = value);
    TMS99X8_setPtr(MODE2_ADDRESS_CT + offset);
    TMS99X8_write(color);    
}



void readLine(uint8_t *data, uint8_t idx) {
    
    const uint8_t *psrc = &screen_copy[offset_y[idx]];

    UNROLL(32, {
	*data = *psrc;
	data ++;
	psrc += 0x40;
    });
}

void writeLine(const uint8_t *data, uint8_t idx) {

    {
	const uint8_t *psrc = data;
	uint8_t *pdst = &screen_copy[offset_y[idx]];

	UNROLL(32, {
	    *pdst = *psrc;
	    pdst += 0x40;
	    psrc ++;
	});
    }

    uint16_t odst = MODE2_ADDRESS_PG + offset_y[idx];
    const uint8_t *psrc = data;

    UNROLL(32, {
	TMS99X8_setPtr(odst);
	TMS99X8_write(*psrc);
	odst += 0x40;
	psrc ++;
    });
}


static inline uint16_t getOffset(uint8_t x, uint8_t y) {

    uint16_t offset = offset_x[x] + offset_y[y];
    return offset;
}


void setPointColor(uint8_t x, uint8_t y, uint8_t color) {

    uint16_t offset = getOffset(x,y);
    TMS99X8_setPtr(MODE2_ADDRESS_CT + offset);
    TMS99X8_write(color);    
}

uint8_t getPoints_v8(uint8_t x, uint8_t y) {

    uint16_t offset = getOffset(x,y);
    return screen_copy[offset];
}


void setPointFG(uint8_t x, uint8_t y) {
    
    uint16_t offset = getOffset(x,y);

    TMS99X8_setPtr(MODE2_ADDRESS_PG + offset);
    TMS99X8_write(screen_copy[offset] |= shift8[x]);    
}

void setPointBG(uint8_t x, uint8_t y) {
    
    uint16_t offset = getOffset(x,y);

    TMS99X8_setPtr(MODE2_ADDRESS_PG + offset);
    TMS99X8_write(screen_copy[offset] &= ~shift8[x]);    
}

void setPointXG(uint8_t x, uint8_t y) {
    
    uint16_t offset = getOffset(x,y);

    TMS99X8_setPtr(MODE2_ADDRESS_PG + offset);
    TMS99X8_write(screen_copy[offset] ^= shift8[x]);    
}

void rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t border_pattern, uint8_t fill_pattern, uint8_t color) {
    
    if (x0>x1) {uint8_t tmp = x0; x0=x1; x1=tmp;}
    if (y0>y1) {uint8_t tmp = y0; y0=y1; y1=tmp;}

    if (border_pattern == 0xFF && fill_pattern == 0) {

	line(x0,y0,x1-1,y0);
	line(x1,y0,x1,y1-1);
	line(x1,y1,x0+1,y1);
	line(x0,y1,x0,y0+1);

	x0++;
	y0++;
	x1--;
	y1--;
	border_pattern = fill_pattern;
	
    } else if (border_pattern != fill_pattern) {
	
	rectangle(x0,y0,x1,y1,border_pattern, border_pattern, color);
	x0++;
	y0++;
	x1--;
	y1--;
	border_pattern = fill_pattern;
    }
    
    yield();

    if (y0<64 && y1>=64) {
        rectangle(x0,y0,x1,63,border_pattern, fill_pattern, color);
        y0=64;
    }
    if (y0<128 && y1>=128) {
        rectangle(x0,y0,x1,127,border_pattern, fill_pattern, color);
        y0=128;
    }

    if ((x0&0x7)==0) {
        while (x1-7>=x0) {
	    
	    yield();

            uint8_t sz = y1-y0+1;
            uint16_t offset = offset_x[x0] + offset_y[y0];
//            printf("XX %d %d\n", sz, offset);
            TMS99X8_memset(MODE2_ADDRESS_PG + offset, fill_pattern, sz);
            TMS99X8_memset(MODE2_ADDRESS_CT + offset, color, sz);
            { uint8_t *p = &screen_copy[offset]; while (sz--) *p++=fill_pattern; }
            x0 += 8;
	    if (x0 < 8) return;
        }
    }

//    printf( "MID: %d %d %d %d %d\n", x0, y0, x1, y1, pattern);

    if (x0==x1) {

        uint8_t sz = y1-y0+1;
        uint16_t offset = offset_x[x0] + offset_y[y0];
        TMS99X8_memset(MODE2_ADDRESS_CT + offset, color, sz);
        
        if ((shift8[x0] & fill_pattern)!=0) {
            while (sz--) {
		setPointFG(x0,y0++);
	    }
        } else {
            while (sz--) {
		setPointBG(x0,y0++);
	    }
        }
        
    } else if (x1>x0) {
        rectangle(x0  ,y0,x0,y1,border_pattern, fill_pattern,color);
        rectangle(x0+1,y0,x1,y1,border_pattern, fill_pattern,color);
    }
}

static void writeChar(char cr) {

    yield();
    
    uint8_t c = cr-32;
    const uint16_t *begin = &textProperties.font_pts[textProperties.font_pos[c]];
    const uint16_t *end   = &textProperties.font_pts[textProperties.font_pos[c+1]];
    while (begin != end) {
	uint16_t xy0 = *begin++;
	uint16_t xy = 0; 
	for (uint8_t i=textProperties.sz; i; i--) { xy += xy0; }
	setPointXG(textProperties.x + (xy>>8), textProperties.y + (xy & 0xFF));
	if (textProperties.dotCallback != nullptr) (*textProperties.dotCallback)();
    }
    uint8_t len0 = textProperties.font_len[c];
    uint8_t len  = 0;
    for (uint8_t i=textProperties.sz; i; i--) { len += (int8_t)len0; }
    textProperties.x += len;
    if (textProperties.charCallback != nullptr) (*textProperties.charCallback)();
}

void writeText(const char *str) {
    
    uint8_t old = ML_LOAD_SEGMENT_D(textProperties.font_segment);

    uint8_t orig_x = textProperties.x;
    uint8_t orig_y = textProperties.y;

    while (*str) {
	if (*str == '\n') {
	    textProperties.x = orig_x;
	    orig_y = textProperties.y = orig_y + textProperties.space_between_lines;
	    str++;
	    continue;
	}
	writeChar(*str++);
    }
    
    ML_RESTORE_D(old);
}


uint8_t getTextWidth(const char *str) {
    
    uint8_t old = ML_LOAD_SEGMENT_D(textProperties.font_segment);
    
    uint8_t textWidth = 0;
    
    while (*str) {
	if (*str == '\n') {
	    str++;
	    continue;
	}

	uint8_t c = *str++ - 32;
	uint8_t len0 = textProperties.font_len[c];
	uint8_t len  = 0;
	for (uint8_t i=textProperties.sz; i; i--) { len += (int8_t)len0; }
	
	textWidth += len;
    }
    
    ML_RESTORE_D(old);
    
    return textWidth;
}

static void lineV(uint8_t x0, uint8_t y0, uint8_t y1) { do setPointXG(x0,y0); while (y0++!=y1); }
static void lineH(uint8_t x0, uint8_t x1, uint8_t y0) { do setPointXG(x0,y0); while (x0++!=x1); }

static void lineQ0(uint8_t x0, uint8_t y0, int8_t dx, int8_t dy) { 

	int8_t d=2*dx-dy;
	for (uint8_t y=y0, x=x0;;y++) {
		setPointXG(x,y);
		if (d<=0)
			d+=2*dx;
		else {
			d+=2*(dx-dy);
			x++;
		}
		if (y==y0+dy) break;
	}
}

static void lineQ1(uint8_t x0, uint8_t y0, int8_t dx, int8_t dy) { 


	int8_t d=2*dy-dx;
	for (uint8_t y=y0, x=x0;;x++) {
		setPointXG(x,y);
		if (d<=0)
			d+=2*dy;
		else {
			d+=2*(dy-dx);
			y++;
		}
		if (x==x0+dx) break;
	}
}

static void lineQ2(uint8_t x0, uint8_t y0, int8_t dx, int8_t dy) { 

	int8_t d=2*dy-dx;
	for (uint8_t y=y0, x=x0;;x++) {
		setPointXG(x,y);
		if (d<=0)
			d+=2*dy;
		else {
			d+=2*(dy-dx);
			y--;
		}
		if (x==x0+dx) break;
	}
}

static void lineQ3(uint8_t x0, uint8_t y0, int8_t dx, int8_t dy) { 

	int8_t d=2*dx-dy;
	for (uint8_t y=y0, x=x0;;y--) {
		setPointXG(x,y);
		if (d<=0)
			d+=2*dx;
		else {
			d+=2*(dx-dy);
			x++;
		}
		if (y==y0-dy) break;
	}
}

void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	    
    if (x0==x1) {
		if (y0==y1) {
			setPointXG(x0,y0);
		} else if (y0<y1) {
			lineV(x0,y0,y1); 
		} else {
			lineV(x0,y1,y0);
		}
	} else {
		if (y0==y1) {
			if (x0<x1) {
				lineH(x0,x1,y0); 
			} else {
				lineH(x1,x0,y0);
			}
		} else {
			if (x1<x0) {
				uint8_t tmp = x0;
				x0 = x1;
				x1 = tmp;
				tmp = y0;
				y0 = y1;
				y1 = tmp;
			}
			uint8_t dx = x1-x0;
			if (y0<y1) {
				uint8_t dy = y1-y0;
				if (dx<dy) {
					lineQ0(x0,y0,dx,dy);
				} else {
					lineQ1(x0,y0,dx,dy);
				}
			} else {
				uint8_t dy = y0-y1;
				if (dx<dy) {
					lineQ3(x0,y0,dx,dy);
				} else {
					lineQ2(x0,y0,dx,dy);
				}
			}
		}
	}	
}



