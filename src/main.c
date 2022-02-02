#define DEBUG

#include <common.h>


static volatile uint16_t isr_counter;
void bench_isr() __nonbanked {
	
	isr_counter++;
	
	// DISABLE KEYBOARD SCAN
	*((uint8_t *)(0xF3F6)) = 3;
}

uint16_t results[512];
uint8_t work_area[2*1024];

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

static uint16_t execute_sieve_of_eratosthenes(uint8_t y, uint16_t calibration, const char *text, uint8_t segment, uint16_t (*sieve_of_eratosthenes)(uint16_t *, uint8_t *, uint16_t)) {	

	lineFast(0,y,255,y);
	lineFast(255,y,255,y+26);
	lineFast(0,y+26,255,y+26);
	lineFast(0,y+26,0,y);
	
	rectangle(1,y+1,254,y+25,0,FWhite + BTransparent);
	
	textProperties.y = y+1;
	textProperties.x = 2;
	writeText(text); writeText(": ");

	lineFast(2,y+12,253,y+12);
	lineFast(253,y+12,253,y+24);
	lineFast(253,y+24,2,y+24);
	lineFast(2,y+24,2,y+12);
	
	isr_counter = 65530;

	EI();			
	while (isr_counter);
	DI();
	
	uint8_t old = ML_LOAD_SEGMENT_B(segment);
	
	uint16_t n_primes = 0;
	for (uint8_t x = 4; x < 252; x+=8) {

		DI();
		lineFast(x,y+14,x,y+22); yield();
		lineFast(x+1,y+14,x+1,y+22); yield();
		lineFast(x+2,y+14,x+2,y+22); yield();
		lineFast(x+3,y+14,x+3,y+22); yield();
		EI();
		
		n_primes = (*sieve_of_eratosthenes)(&results[0], &work_area[0], 2*1024);
	}
	
	ML_RESTORE_B(old);

	uint16_t counter = isr_counter;

	if (calibration) {
		writeText(" done. Found "); writeText(itoa(n_primes)); writeText(" primes in "); writeText(itoa(counter - calibration)); writeText(" frames.\n\n");
	} else {
		writeText(" done. Calibration delay is "); writeText(itoa(counter));  writeText(" frames.\n\n");
	}
	
	return counter;
}

static void main_int(void) {


    DI();

	msxhal_install_isr(bench_isr);

	//msxhal_request60Hz();
	
	ML_LOAD_MODULE_C(graphics);
	
	initCanvas();

	uint8_t c = 0;

	writeText("Benchmark: Sieve of Eratosthenes:");
		

	while (true) {
		
		int16_t calibration = execute_sieve_of_eratosthenes(11, 0, "Calibration", ML_SEGMENT_B(bench_calibration), &sieve_of_eratosthenes_calibration);
		
		execute_sieve_of_eratosthenes(11+28*5, calibration, "RUST", ML_SEGMENT_B(bench_rs), &sieve_of_eratosthenes_rust);

		execute_sieve_of_eratosthenes(11+28*4, calibration, "ZIG", ML_SEGMENT_B(bench_zig), &sieve_of_eratosthenes_zig);

		execute_sieve_of_eratosthenes(11+28*3, calibration, "D", ML_SEGMENT_B(bench_d), &sieve_of_eratosthenes_d);

		execute_sieve_of_eratosthenes(11+28*1, calibration, "C", ML_SEGMENT_B(bench_c), &sieve_of_eratosthenes_c);

		execute_sieve_of_eratosthenes(11+28*2, calibration, "C++", ML_SEGMENT_B(bench_cc), &sieve_of_eratosthenes_cc);
		
		while (true);
	}
}

int main(void) __nonbanked {
	
	ML_EXECUTE_A(main, main_int() );
}


