#pragma once 
#include <common.h>

void initCanvas();

void setPoints_v8(uint8_t x, uint8_t y, uint8_t value);
void setPoints_v8c(uint8_t x, uint8_t y, uint8_t value, uint8_t color);
uint8_t getPoints_v8(uint8_t x, uint8_t y);

void setPointFG(uint8_t x, uint8_t y); 
void setPointBG(uint8_t x, uint8_t y); 
void setPointXG(uint8_t x, uint8_t y); 

void setPointColor(uint8_t x, uint8_t y, uint8_t color);

void rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t border_pattern, uint8_t fill_pattern, uint8_t color);

void line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void copyLine(uint8_t dst, uint8_t src);

void readLine(uint8_t *data, uint8_t idx);
void writeLine(const uint8_t *data, uint8_t idx);

void draw_color_bar(uint8_t y, uint8_t y_test);
void push_bar_up(uint8_t idx, uint8_t verified);

void repaintScreen();

typedef struct {
	uint8_t font_segment;
    const uint16_t *font_pts;
    const uint16_t *font_pos;
    const uint8_t *font_len;
    uint8_t space_between_lines;

    uint8_t x, y;
    uint8_t value;
    uint8_t color;
    uint8_t sz;
    
    void (*dotCallback)();
    void (*charCallback)();    
} TTextProperties;
extern TTextProperties textProperties;
extern T_SA SA;

uint8_t getTextWidth(const char *str);
void writeText(const char *str);
