#include <common.h>

ML_MOVE_SYMBOLS_TO(tests, quicksort_common);

typedef struct {
	
	uint16_t  array[2048];

} T_QUICKSORT;

__at ((48+2)*1024U) T_QUICKSORT quicksort_data;

typedef void (*T_FN_QUICKSORT)(uint16_t *A, uint16_t len );

static struct {
  uint32_t a, b, c, d;
  uint32_t count;
} xorwow_state;

static uint32_t xorwow() {

	uint32_t t = xorwow_state.d;

	uint32_t s = xorwow_state.a;
	xorwow_state.d = xorwow_state.c;
	xorwow_state.c = xorwow_state.b;
	xorwow_state.b = s;

	t ^= t >> 2;
	t ^= t << 1;
	t ^= s ^ (s << 4);
	xorwow_state.a = t;

	xorwow_state.count += 362437;
	return t + xorwow_state.count;
}

void run_quicksort(T_FN_QUICKSORT f) {

	uint32_t seed = 0;
	xorwow_state.a = 0x12345678U ^ seed;
	xorwow_state.b = 0x56781234U ^ seed;
	xorwow_state.c = 0x34567878U ^ seed;
	xorwow_state.d = 0x81238123U ^ seed;
	xorwow_state.count = 0xDEADBEEFU ^ seed;

	
	for (uint16_t i = 0; i < 2048; i++) 
		quicksort_data.array[i] = (uint16_t)xorwow() ;
	
	if (f)
		(*f)(quicksort_data.array, 2048);
}

void reference_quicksort() {

	return;
}

bool verify_quicksort(T_TEST *t, T_TEST_CASE *tc) {
	
	(void)t;
	(void)tc;
	
	for (uint16_t i=1; i<2048; i++)
		if (quicksort_data.array[i-1] > quicksort_data.array[i]) return false;
		
	return true;
}
