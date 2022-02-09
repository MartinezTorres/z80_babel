#define DEBUG

#include <common.h>

T_SELECTED_SORT selected_sort;

static uint8_t sort_line_order[192];
static uint8_t sort_line_order_idx[192];
static uint8_t tmp_line[32];

void sort_tests_b(const T_TEST *t) {


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

void adjust_bars_b(const T_TEST *t) {

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
