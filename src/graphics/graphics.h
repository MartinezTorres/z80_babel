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

ML_REQUEST_C(graphics);

extern const uint16_t font_newsgeek_pts[];
extern const uint16_t font_newsgeek_pos[];
extern const uint8_t font_newsgeek_len[];
ML_REQUEST_D(font_newsgeek);

extern const uint16_t font_didone_pts[];
extern const uint16_t font_didone_pos[];
extern const uint8_t font_didone_len[];
ML_REQUEST_D(font_didone);

extern const uint16_t font_tiny_pts[];
extern const uint16_t font_tiny_pos[];
extern const uint8_t font_tiny_len[];
ML_REQUEST_D(font_tiny);

extern const uint16_t font_thin_pts[];
extern const uint16_t font_thin_pos[];
extern const uint8_t font_thin_len[];
ML_REQUEST_D(font_thin);

inline void select_font_tiny() {
    
    textProperties.font_segment = ML_SEGMENT_D(font_tiny);
    textProperties.font_pts = font_tiny_pts;
    textProperties.font_pos = font_tiny_pos;
    textProperties.font_len = font_tiny_len;
}

inline void select_font_thin() {
    
    textProperties.font_segment = ML_SEGMENT_D(font_thin);
    textProperties.font_pts = font_thin_pts;
    textProperties.font_pos = font_thin_pos;
    textProperties.font_len = font_thin_len;    
}
