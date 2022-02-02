#pragma once 
#include <common.h>

void initCanvas();

void setROI(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void setPoint(int16_t x, int16_t y, uint8_t value, uint8_t color);
void setPoints_v8(int16_t x16, int16_t y16, uint8_t value);
void setPoints_v8c(uint8_t x, uint8_t y, uint8_t value, uint8_t color);
uint8_t getPoints_v8(int16_t x16, int16_t y16);

void setHistoricPoint(uint8_t hist, uint8_t value, uint8_t color);
void restoreHistoricPoint(uint8_t hist);
void undoPoint();

void setPointFG(uint16_t xy) __z88dk_fastcall; 
void setPointBG(uint16_t xy) __z88dk_fastcall; 

void rectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t pattern, uint8_t color);
void setHLine(uint8_t n, int16_t x16, int16_t y16, uint8_t value, uint8_t color);

void line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t pattern, uint8_t color);
void lineFast(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void rectangleColor(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);


typedef struct {
	uint8_t font_segment;
    const uint16_t *font_pts;
    const uint16_t *font_pos;
    const uint8_t *font_len;
    uint8_t space_between_lines;

    int16_t x, y;
    uint8_t value;
    uint8_t color;
    uint8_t sz;
    uint8_t faster; // Skips color, history, and ROI calculations
    
    void (*dotCallback)();
    void (*charCallback)();    
} TTextProperties;
extern TTextProperties textProperties;
extern T_SA SA;

void writeText(const char *str);
void putNumber(int32_t number, uint8_t padding, uint8_t zero_fill, uint8_t exponent_bits, uint8_t n_fractional_digits); 

//void graphicsInitCO(uint8_t co, EObjectClass oClass);
//void graphicsUpdateCOs();
