#include <common.h>

ML_MOVE_SYMBOLS_TO(tests, md5_common);

typedef struct {
	
	uint16_t  array[2048];

} T_MD5;

__at ((48+2)*1024U) T_MD5 md5_data;


typedef uint8_t* (*T_FN_MD5)(uint8_t *ctx, const uint8_t *input, uint16_t input_len);


void run_md5(T_FN_MD5 f) {

	
	if (f) {
		uint8_t* md5 = (*f)((uint8_t *)&md5_data, (const uint8_t *)
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 445);
	}	
}

void reference_md5() {

	return;
}

bool verify_md5(T_TEST *t, T_TEST_CASE *tc) {
	
	(void)t;
	(void)tc;
	
//	for (uint16_t i=1; i<2048; i++)
//		if (quicksort_data.array[i-1] > quicksort_data.array[i]) return false;
		
	return true;
}
