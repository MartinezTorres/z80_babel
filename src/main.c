#define DEBUG

#include <common.h>
#include <test.h>
#include <sieve.h>
#include <tests.h>



static uint8_t selected_test;

static bool is_irq_50Hz;

volatile uint16_t isr_counter;
volatile bool keyboard_enabled;

static struct  {
	
	uint8_t y0;
	uint8_t y1;
	
	uint16_t x_sub;
	uint16_t x_speed;
	
	uint8_t x;
	uint8_t x_min;
	uint8_t x_target;
	
} progress_bar;


void main_irq() {
		
	isr_counter++;
	
	if (progress_bar.x_target) {

		
		while (progress_bar.x < progress_bar.x_min) {
			
			line(progress_bar.x, progress_bar.y0, progress_bar.x, progress_bar.y1);
			progress_bar.x_sub = (progress_bar.x_min) << 8; 
			progress_bar.x++;
		}

		if (progress_bar.x_sub < (uint16_t)(progress_bar.x_min << 8)) {
			
			progress_bar.x_sub = (progress_bar.x_min << 8);
		}
		
		while (progress_bar.x < (progress_bar.x_sub >> 8)) {
			
			line(progress_bar.x, progress_bar.y0, progress_bar.x, progress_bar.y1);
			progress_bar.x++;
		}
		
		progress_bar.x_sub += progress_bar.x_speed;
		
		if (progress_bar.x_sub > (uint16_t)(progress_bar.x_target << 8)) {
			
			progress_bar.x_sub = (progress_bar.x_target << 8);
		}
		
	} else {
		
		progress_bar.x_sub = 0;
	}
	
	
	// DISABLE KEYBOARD SCAN
	if (!keyboard_enabled)
		*((uint8_t *)(0xF3F6)) = 3;

	//TMS99X8_debugBorder(5);
	
	//TMS99X8_debugBorder(0);
}


static char msxhal_getch() {


#ifdef MSX
	__asm
		call #0x009C      ; call CHSNS
		ld l,#0
        di
		ret z
		call #0x009f		; call CHGET
		ld l,a
        di
		ret
	__endasm;	
#endif	
	
	return 0;
}



char text_tmp[10];
static const char *itoa(uint16_t n) {
	
	uint8_t len = 1;
	text_tmp[0] = '0';
	text_tmp[1] = '0';
	text_tmp[2] = '0';
	text_tmp[3] = '0';
	text_tmp[4] = '0';
	text_tmp[5] = 0;

	if (n > 9) len = 2;
	if (n > 99) len = 3;
	if (n > 999) len = 4;
	if (n > 9999) len = 5;
	
	while (n>9999) { text_tmp[0]++; n-=10000; }
	while (n>999) { text_tmp[1]++; n-=1000; }
	while (n>99) { text_tmp[2]++; n-=100; }
	while (n>9) { text_tmp[3]++; n-=10; }
	while (n) { text_tmp[4]++; n-=1; }
	
	return &text_tmp[5-len];
} 

static uint16_t hzToCentsOfSeconds(uint16_t nFrames) {

	
	if (is_irq_50Hz) return nFrames * 2;
		
	// 60 Hz
	uint16_t cs = 0;
	
	while (nFrames >= 3) {
		cs += 5;
		nFrames-=3;
	}
	while (nFrames --> 0) cs += 2;
	
	return cs;
}

// r = 150 * a / b
static uint8_t calc_150a_b(uint16_t a, uint16_t b) {

	// 150 = 3*(32+16+2)
	uint32_t A    = a;
	uint32_t A16  = A<<4;
	uint32_t A32  = A16+A16;
	uint32_t A50  = A32 + A16 + A + A;
	uint32_t A150 = A50 + A50 + A50;
	
	uint32_t B    = b;
	uint32_t B16  = B<<4;
	
	uint8_t  C    = 0;
	while (A150 > B16) { C += 16; A150 -= B16; }
	while (A150 >   b) { C += 1;  A150 -= b; }

	return C;
}


static enum { SORT_SIZE, SORT_SPEED } selected_sort;

static uint8_t sort_line_order[192];
static uint8_t sort_line_order_idx[192];
static uint8_t tmp_line[32];

static void sort_tests(const T_TEST *t) {


	{

		for (uint8_t i=0; i<192; i++)
			sort_line_order[i] = i;

		uint8_t y_min = 255;

		bool sorted = false;
		while (! sorted) {
			
			sorted = true;
			

			for (uint8_t i=1; i<t->n_test_cases; i++) {
				
				T_TEST_RESULT *r0 = &t->test_results[i-1];
				T_TEST_RESULT *r1 = &t->test_results[i  ];

				if (r0->executed == 0) break;
				if (r1->executed == 0) break;

				y_min = (y_min < r0->y ? y_min : r0->y);
				y_min = (y_min < r1->y ? y_min : r1->y);
				
				bool is_sorted;
				if (selected_sort==SORT_SIZE) {
					
					is_sorted = (r0->size <= r1->size);
				} else {
					
					is_sorted = (r0->frames <= r1->frames);
				}
				
				if (!is_sorted) {
						
					T_TEST_RESULT r_tmp;
					r_tmp = *r0;
					*r0 = *r1;
					*r1 = r_tmp;
					
				
					sorted = false;
				}
			}
		}

		if (y_min != 255) {
			for (uint8_t i=0; i<t->n_test_cases; i++) {
				
				T_TEST_RESULT *r0 = &t->test_results[i];
				if (r0->executed == 0) break;
				
				for (uint8_t j = 0; j < 13; j++) {
					sort_line_order[r0->y + j] = y_min + j;
					sort_line_order_idx[r0->y + j] = j + (r0->verified ? 0x80 : 0x00);
				}
				
				r0->y = y_min;
				y_min += 13;
			}
		}
	}
	
	{

		bool sorted = false;
		while (!sorted) {
			
			sorted = true;
			for (uint8_t i=1; i<192; i++) {
				if (sort_line_order[i-1]<sort_line_order[i]) continue;
				sorted = false;
				
				uint8_t li = sort_line_order[i-1];
				uint8_t lii = sort_line_order_idx[i-1];
				readLine( &tmp_line[0], i-1 );
				
				uint8_t j = i;
				while (li>sort_line_order[j]) {

					push_bar_up(j - 1, sort_line_order_idx[j] & 0x80);
					
					for (uint8_t k = 0; k < 13; k++) {
					
						sort_line_order[j-1] = sort_line_order[j];
						sort_line_order_idx[j-1] = sort_line_order_idx[j];
						j++;
					}					
				}

				if (0) while (li>sort_line_order[j]) {

					sort_line_order[j-1] = sort_line_order[j];
					sort_line_order_idx[j-1] = sort_line_order_idx[j];

					copyLine(j-1, j);
					draw_color_bar( j-1, sort_line_order_idx[j-1] );

					j++;
				}
				
				sort_line_order[j-1] = li;
				sort_line_order_idx[j-1] = lii;
				writeLine( &tmp_line[0], j-1 );
				draw_color_bar( j-1, lii );
				
				i = j-1;
			}
		}
	}

	
}

static void draw_bar_update(uint8_t x, uint8_t y) {

	setPointXG(x, y+1);
	setPointXG(x, y+2);
	setPointXG(x, y+3);
	setPointXG(x, y+4);
	setPointXG(x-1, y+5);	
}

static void adjust_bars(const T_TEST *t) {

	bool updated = true;
	while (updated) {
		
		for (uint8_t i=0; i<t->n_test_cases; i++) {
			
			updated = false;
			for (uint8_t i=0; i<t->n_test_cases; i++) {
				
				T_TEST_RESULT *r = &t->test_results[i];
				
				if (r->executed == 0) break;
				
				
				if (r->size_x > r->size_x_target) {
					
					draw_bar_update( 
						r->size_x--,
						r->y + 6);
					updated = true;
				}

				if (r->size_x < r->size_x_target) {
					
					draw_bar_update( 
						++r->size_x,
						r->y + 6);
					updated = true;
				}

				if (r->frames_x > r->frames_x_target) {
					
					draw_bar_update( 
						r->frames_x--,
						r->y);
					updated = true;
				}

				if (r->frames_x < r->frames_x_target) {
					
					draw_bar_update( 
						++r->frames_x,
						r->y);
					updated = true;
				}
			}
		
			if (!updated) break;
		}
		
		wait_frame();
	}
}

static void execute_test(const T_TEST *t, bool first_execution) {

	// Clear and Draw rectangle area.
	rectangle(0,11,255,191,0x00,0x00, FWhite + BTransparent);
	
	// Draw graph horizontal Axis
	line(2, 180, 253, 180);
	
	// Draw graph vertical Axis
	//line(40, 13, 40, 180);
	
	// Draw graph Title
	{

		textProperties.font_segment = ML_SEGMENT_D(font_thin);
		textProperties.font_pts = font_thin_pts;
		textProperties.font_pos = font_thin_pos;
		textProperties.font_len = font_thin_len;

		textProperties.y = 182;
		textProperties.x = 128 - getTextWidth(t->name) / 2;

		writeText(t->name);
	}

	// Draw Test Index
	{
		textProperties.y = 182;
		textProperties.x = 0;

		writeText(itoa(selected_test+1));
		writeText(" of ");
		writeText(itoa(SELECTED_TESTS.N));
		
		
	}
	
	(* t->fn_reference)();
	//uint16_t calibration;

	if (first_execution) {
		for (uint8_t i = 0; i < t->n_test_cases; i++) {
			T_TEST_RESULT *r = & t->test_results[i];
			r->executed = false;
			r->test = t;			
			r->test_case = &t->test_cases[i];
		}
	}
	
	uint16_t calibration = 0;
	{				

		isr_counter = 65533;
		keyboard_enabled = false;

		EI();			
		while (isr_counter) {};
		(* t->fn_run_test)(nullptr);
		DI();

		progress_bar.x_speed = 16;
		{
			uint16_t steps = 20*16;
			if (isr_counter==0) isr_counter++;
			
			while (steps > isr_counter) {
				progress_bar.x_speed += 16;
				steps -= isr_counter;
			}
		}
			
		rectangle(50, 12, 253, 12 + 11, 0x00, 0x00, FTransparent + BTransparent);

		progress_bar.x = 52;
		progress_bar.x_sub = (52 << 8);
		progress_bar.y0 = 12+2;
		progress_bar.y1 = 12+9;
		

		EI();			
		isr_counter = 65533;
		while (isr_counter) {};
		
		for (uint8_t x = 52; x < 252; x+=20) {
			
			progress_bar.x_min = x;
			progress_bar.x_target = x + 20;
			
			(* t->fn_run_test)(nullptr);
		}
		while (((volatile uint8_t)progress_bar.x) != 252) {};
		DI();

		calibration = isr_counter;

		progress_bar.x_target = 0;
		
		rectangle(50, 12, 253,12 + 12, 0x00, 0x00, FWhite + BTransparent);
	}

		
	// Execute names all Tests
	{
		for (uint8_t i = 0; i < t->n_test_cases; i++) {
		
			T_TEST_RESULT *r = & t->test_results[i];

			r->size = (uint16_t)r->test_case->fn_end - (uint16_t)r->test_case->fn_begin;

			r->y = 180 - t->n_test_cases*13 + i * 13;

			textProperties.y = r->y + 1;
			textProperties.font_segment = ML_SEGMENT_D(font_thin);
			textProperties.font_pts = font_thin_pts;
			textProperties.font_pos = font_thin_pos;
			textProperties.font_len = font_thin_len;

			//textProperties.x = 48 - getTextWidth(r->test_case->name);
			textProperties.x = 0;
			writeText(r->test_case->name);
			
			if (!r->executed) {				

				uint8_t old = ML_LOAD_SEGMENT_B(r->test_case->segment);
				isr_counter = 65533;
				keyboard_enabled = false;

				EI();			
				while (isr_counter) {};
				(* t->fn_run_test)(r->test_case->fn_test);
				DI();
				
				progress_bar.x_speed = 16;
				{
					uint16_t steps = 20*16;
					if (isr_counter==0) isr_counter++;
					
					while (steps > isr_counter) {
						progress_bar.x_speed += 16;
						steps -= isr_counter;
					}
				}
				
				r->verified = (* t->fn_verify)(t, r->test_case);
			
				rectangle(50, r->y, 253,r->y + 11,0xFF,0x00, FWhite + BTransparent);

				progress_bar.x = 52;
				progress_bar.x_sub = (52 << 8);
				progress_bar.y0 = r->y+2;
				progress_bar.y1 = r->y+9;

				EI();			
				isr_counter = 65533;
				while (isr_counter) {};
				
				for (uint8_t x = 52; x < 252; x+=20) {
					
					progress_bar.x_min = x;
					progress_bar.x_target = x + 20;
					
					(* t->fn_run_test)(r->test_case->fn_test);
				}
				while (((volatile uint8_t)progress_bar.x) != 252) {};
				DI();

				r->frames = isr_counter - calibration;
				//r->frames = isr_counter;

				progress_bar.x_target = 0;
				
				rectangle(50, r->y, 253,r->y + 12,0x00,0x00, FWhite + BTransparent);


				ML_RESTORE_B(old);
					
			}

			for (uint8_t j=0; j<13; ++j) 
				draw_color_bar( r->y + j, j + (r->verified?0x80:0x00));
			
			//if (!r->executed) 
			{
			
				r->size_x = 103;
				r->max_size = r->size;
				if (i==0) {
				} else if (r->max_size > t->test_results[i-1].max_size) {
					
					for (uint8_t j = i; j > 0; j--) {
						
						// x_target = 104 + 150 * size / max_size
						T_TEST_RESULT *r1 = &t->test_results[j-1];

						r1->max_size = r->max_size;
						
						r1->size_x_target = 104 + calc_150a_b(r1->size, r->max_size);
						r1->size_x_speed = 0;
					}
				} else {
					r->max_size = t->test_results[i-1].max_size;
				}
				r->size_x_target = 104 + calc_150a_b(r->size, r->max_size);
				r->size_x_speed = 0;

				r->frames_x = 103;
				r->max_frames = r->frames;
				if (i==0) {
				} else if (r->max_frames > t->test_results[i-1].max_frames) {
					
					for (uint8_t j = i; j > 0; j--) {

						// x_target = 104 + 150 * frames / max_frames
						T_TEST_RESULT *r1 = &t->test_results[j-1];

						r1->max_frames = r->max_frames;
						
						r1->frames_x_target = 104 + calc_150a_b(r1->frames, r->max_frames);
						r1->frames_x_speed = 0;
					}
				} else {
					r->max_frames = t->test_results[i-1].max_frames;
				}
				r->frames_x_target = 104 + calc_150a_b(r->frames, r->max_frames);
				r->frames_x_speed = 0;
			}

			
			
			textProperties.font_segment = ML_SEGMENT_D(font_tiny);
			textProperties.font_pts = font_tiny_pts;
			textProperties.font_pos = font_tiny_pos;
			textProperties.font_len = font_tiny_len;
			
			{
				textProperties.y += 0;

				textProperties.x = 50;
				writeText("DELAY:");

				uint16_t milliseconds = hzToCentsOfSeconds(r->frames);
				const char *text = itoa(milliseconds);

				textProperties.x = 50 + 22 + 16 - getTextWidth(text);
				writeText(text); writeText("ms");
			}


			{
				textProperties.y += 6;

				textProperties.x = 50+6;
				writeText("SIZE:");
				
				const char *text = itoa(r->size);
				textProperties.x = 50 + 22 + 16 - getTextWidth(text);
				writeText(text); writeText("b");
			}

			r->executed = true;
			
			setPointXG(103, r->y+1);
			setPointXG(103, r->y+2);
			setPointXG(103, r->y+3);
			setPointXG(103, r->y+4);

			setPointXG(103, r->y+1+6);
			setPointXG(103, r->y+2+6);
			setPointXG(103, r->y+3+6);
			setPointXG(103, r->y+4+6);
			
			adjust_bars(t);
			sort_tests(t);
		}
	}
	
}

uint16_t test_irq_speed() {
	
#ifdef __SDCC
	__asm
	push af
	push ix
	ld   de, #0
	ld   ix, #(_isr_counter)
	ld   (ix), #0
	xor  a
	inc a
	inc a
	ei
00001$:
	cp   (ix)
	jr NZ, 00001$
	inc a
	inc a
00002$:
	inc  de
	cp   (ix)
	jr NZ, 00002$
	di
	pop ix
	pop af
	ret
	__endasm;	

#endif	
	return 0;
}



void start() {

	msxhal_enableR800();

	selected_sort = SORT_SPEED;

	progress_bar.x_target = 0;
		
	is_irq_50Hz = test_irq_speed() > 3000;

	ML_LOAD_MODULE_C(graphics);
	ML_LOAD_MODULE_D(scroll_bar);
	
//	int8_t i = 0;
//	while (true) TMS99X8_debugBorder(i++ & 0xF);

	
	initCanvas();

	textProperties.x = 6;

	writeText("Z80 Babel: Language benchmarks ");
	
	keyboard_enabled = false;
//	execute_test(&test_sieve_50k, true);
//	execute_test(&test_sieve_cpp, true);
	
	selected_test = 0;
	execute_test(SELECTED_TESTS.tests[selected_test], true);

	while (true) {

		keyboard_enabled = true;
		
		char c = msxhal_getch();
			
		if (c == ' ') {

			if (selected_sort == SORT_SIZE) {

				selected_sort = SORT_SPEED;
			} else {

				selected_sort = SORT_SIZE;
			}
			sort_tests( SELECTED_TESTS.tests[selected_test] );
			
		}
		
		if (c == 's') {

			selected_sort = SORT_SIZE;
			sort_tests( SELECTED_TESTS.tests[selected_test] );
			
		}

		if (c == 'd') {
			
			selected_sort = SORT_SPEED;
			sort_tests( SELECTED_TESTS.tests[selected_test] );
		}
		
		if (c == 0x1D) { // LEFT
			
			if (selected_test) {

				selected_test--;
			} else {

				selected_test = SELECTED_TESTS.N;
			}			

			keyboard_enabled = false;
			execute_test(SELECTED_TESTS.tests[selected_test], true);
			

		}

		if (c == 0x1C) { // RIGHT

			selected_test++;
			if (selected_test == SELECTED_TESTS.N) 
				selected_test = 0;
				
			keyboard_enabled = false;
			execute_test(SELECTED_TESTS.tests[selected_test], true);
		}

		wait_frame();
	}
}

