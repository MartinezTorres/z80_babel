#include <hal/msxhal.h>

#ifdef LINUX
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////
// VIDEO EMULATOR
#include <tms99X8.h>

typedef struct { uint8_t r,g,b; } RGB;
static RGB framebuffer     [TEX_HEIGHT][TEX_WIDTH];
static RGB framebufferOld  [TEX_HEIGHT][TEX_WIDTH];
static RGB framebufferMixed[TEX_HEIGHT][TEX_WIDTH];

static const RGB colors[16] = {
{   0,    0,    0},
{   0,    0,    0},
{  33,  200,   66},
{  94,  220,  120},
{  84,   85,  237},
{ 125,  118,  252},
{ 212,   82,   77},
{  66,  235,  245},
{ 252,   85,   84},
{ 255,  121,  120},
{ 212,  193,   84},
{ 230,  206,  128},
{  33,  176,   59},
{ 201,   91,  186},
{ 204,  204,  204},
{ 255,  255,  255}	
};

static TMS99X8_Status TMS99X8_status;
uint8_t TMS99X8_readStatus() { return TMS99X8_status.status; }
 
static inline void drawMode2(const T_PN PN, const T_CT CT, const T_PG PG, const T_SA SA, const T_SG SG) {
	
	uint8_t pnMask = TMS99X8.pg11 & 3;
	uint8_t ctMask1 = (TMS99X8.ct6>>5) & 3;
	uint8_t ctMask2 = ((TMS99X8.ct6&31)<<3)+7;
	
	// TILES
	for (int i=0; i<TILE_HEIGHT; i++) {
		for (int j=0; j<TILE_WIDTH; j++) {
			for (int ii=0; ii<8; ii++) {
				uint8_t p = PG[(i/8)&pnMask][PN[i][j]][ii];
				uint8_t c = CT[(i/8)&ctMask1][PN[i][j]&ctMask2][ii];
				RGB *pix = &framebuffer[i*8+ii][j*8];
				for (int jj=0; jj<8; jj++) {
					if (p&128) {
						if (c>>4) {
							pix[jj]=colors[c>>4];
						}
					} else {
						if (c & 0xF) {
							pix[jj]=colors[c&0xF];
						}
					}
					p*=2;
				}
			}
		}
	}
	
	
	// SPRITES	
    TMS99X8_status._5S = 0;
    TMS99X8_status.illegalSprite = 31;
	for (int i=0; i<TILE_HEIGHT*8; i++) {
		
		int maxSprite;
		{
			int nShownSprites=0;

			for (maxSprite=0; maxSprite<N_SPRITES; maxSprite++) {

				uint8_t spriteLine = (i-SA[maxSprite].y-1) >> TMS99X8.magnifySprites;
				
				if (spriteLine>=8 * (1+TMS99X8.sprites16)) continue;
                
                if (SA[maxSprite].y==208) {  break; };
                if (nShownSprites==4) { 
                    if (TMS99X8_status._5S == 0)
                        TMS99X8_status.illegalSprite = maxSprite; 
                    TMS99X8_status._5S = 1; 
                    break; 
                }
				nShownSprites++;
			}
		}


		for (int j=maxSprite-1; j>=0; j--) {

			uint8_t spriteLine = (i-SA[j].y-1) >> TMS99X8.magnifySprites;
			
			if (spriteLine>=8 * (1+TMS99X8.sprites16)) continue;
			
			uint8_t pattern = SA[j].pattern;			
			if (TMS99X8.sprites16) pattern = (pattern & 252) + !!(spriteLine>7);

			int y = i;
			int x = SA[j].x - (32*!!(SA[j].color&128));

			for (int k=0; k<=TMS99X8.sprites16; k++) {

				uint8_t p = SG[pattern+2*k][spriteLine%8];
				for (int jj=0; jj<8; jj++) {
					
					for (int m=0; m<=TMS99X8.magnifySprites; m++) {

						if (x>=0 && x<TILE_WIDTH*8 && (p&128) && (SA[j].color&0xF))
							framebuffer[y][x]=colors[SA[j].color&0xF];
						x++;
					}
					p*=2;
				}
			}
		}
	}
}

static inline void drawScreen() {

	for (int i=0; i<TEX_HEIGHT; i++)
		for (int j=0; j<TEX_WIDTH; j++)
			framebuffer[i][j] = colors[TMS99X8.backdrop];
			
	if (! TMS99X8.blankScreen) return;

	if (TMS99X8.mode2) {
		const T_PN *PN = (const T_PN *)&TMS99X8VRAM[(uint16_t)(TMS99X8.pn10)<<10];
		const T_CT *CT = (const T_CT *)&TMS99X8VRAM[(uint16_t)(TMS99X8.ct6&0x80)<< 6];
		const T_PG *PG = (const T_PG *)&TMS99X8VRAM[(uint16_t)(TMS99X8.pg11&0xFC)<<11];
		const T_SA *SA = (const T_SA *)&TMS99X8VRAM[(uint16_t)(TMS99X8.sa7 )<< 7];
		const T_SG *SG = (const T_SG *)&TMS99X8VRAM[(uint16_t)(TMS99X8.sg11)<<11];

		drawMode2(*PN, *CT, *PG, *SA, *SG); //only mode2 is supported
	}
}




////////////////////////////////////////////////////////////////////////
// IO FUNCTIONS

volatile uint8_t interrupt_count;

volatile bool enable_keyboard_routine;

#define N_KEYS  8831
static bool keys[N_KEYS];
static uint8_t keyBuffer[40];
static uint8_t keyBufferStart = 0;
static uint8_t keyBufferEnd = 0;

static inline void keyboard_init(void) {
	memset(keys, 0, sizeof(keys));
}

static inline void keyboard_update(SDL_Event e) {
	switch( e.type ){
	case SDL_KEYDOWN:
		//printf("KEY PRESSED: %d\n",e.key.keysym.sym);
		keys[e.key.keysym.sym%N_KEYS] = true;
		
		if (e.key.keysym.sym==SDLK_RIGHT) e.key.keysym.sym =  0x1C; 
		if (e.key.keysym.sym==SDLK_LEFT ) e.key.keysym.sym =  0x1D; 
		if (e.key.keysym.sym==SDLK_UP   ) e.key.keysym.sym =  0x1E; 
		if (e.key.keysym.sym==SDLK_DOWN ) e.key.keysym.sym =  0x1F; 
		
		if (e.key.keysym.sym && e.key.keysym.sym<128) {
			keyBuffer[keyBufferEnd++] = e.key.keysym.sym;
			if (keyBufferEnd==40) keyBufferEnd=0;
			if (keyBufferEnd==keyBufferStart) keyBufferEnd++;
			if (keyBufferStart==40) keyBufferStart=0;
		}
		break;
	case SDL_KEYUP:
		//printf("KEY RELEASED: %d\n",e.key.keysym.sym);
		keys[e.key.keysym.sym%N_KEYS] = false;
		break;
	default:
		break;
	}
}

uint8_t msxhal_joystick_read(uint8_t joystickId) { 
	
	uint8_t joystickStatus[2];
	
	joystickStatus[0] = 0;
	joystickStatus[1] = 0;
	
	if (keys[SDLK_RIGHT % N_KEYS]) joystickStatus[0] += J_RIGHT;
	if (keys[SDLK_DOWN  % N_KEYS]) joystickStatus[0] += J_DOWN;
	if (keys[SDLK_UP    % N_KEYS]) joystickStatus[0] += J_UP;
	if (keys[SDLK_LEFT  % N_KEYS]) joystickStatus[0] += J_LEFT;
	if (keys[SDLK_DELETE% N_KEYS]) joystickStatus[0] += J_DEL;
	if (keys[SDLK_INSERT% N_KEYS]) joystickStatus[0] += J_INS;
	if (keys[SDLK_HOME  % N_KEYS]) joystickStatus[0] += J_HOME;
	if (keys[SDLK_SPACE % N_KEYS]) joystickStatus[0] += J_SPACE;

	return joystickStatus[joystickId]; 	
}

uint8_t msxhal_getch(void) { 
	
	uint8_t c = 0;
	if (keyBufferEnd==keyBufferStart) return c;
	c = keyBuffer[keyBufferStart++];
	if (keyBufferStart==40) keyBufferStart=0;
	printf("0x%02X\n", c);
	return c;
}



////////////////////////////////////////////////////////////////////////
// SDL BACKEND

static bool SDL_is_initialized = false;

static SDL_Window* gWindow = nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Texture* tex = nullptr;


#include <ay8912.h>
#include <psg.h>
static ayemu_ay_t ay;
static void fill_audio(void *reg, uint8_t *stream, int len) {
	
	ayemu_set_regs  (&ay, reg);
	ayemu_gen_sound (&ay, stream, len);
	
}

static inline int8_t initSDL() {
	
	SDL_AudioSpec wanted;

	wanted.freq = 44100;
	wanted.format = AUDIO_S16;
	wanted.channels = 1;
	wanted.samples = 2*44100/60;
	wanted.callback = fill_audio;
	wanted.userdata = &AY_3_8910_Registers.reg;

	if (SDL_OpenAudio(&wanted, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		return -1;
	}

	ayemu_init(&ay);
	ayemu_set_sound_format(&ay, wanted.freq, wanted.channels, 16);
	ayemu_reset(&ay);
	ayemu_set_chip_type(&ay, AYEMU_AY, NULL);
	ayemu_set_chip_freq(&ay, AYEMU_DEFAULT_CHIP_FREQ);
//	ayemu_set_stereo(&ay, AYEMU_MONO, NULL);
	ayemu_set_stereo(&ay, AYEMU_ABC, NULL);
	
	SDL_PauseAudio(0);

	    
    // Intialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //std::cout << "SDL could not initialize! error: " << SDL_GetError() << "\n";
        return -1;
	}

	// create window
	gWindow = SDL_CreateWindow("SDL Skeleton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TEX_WIDTH*4, TEX_HEIGHT*4, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		//std::cout << "Window could not be created! error: " << SDL_GetError() << "\n";
        return -2;
	}
	// create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr) {
		//std::cout << "Renderer could not be created. error: " << SDL_GetError() << "\n";
        return -3;
	}


	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	tex = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STREAMING,TEX_WIDTH,TEX_HEIGHT);

    return 0;
}

static int8_t displayFramebufferSDL() {
	
	
		// clear screen
		SDL_RenderClear(gRenderer);
		
		void *mPixels;
		int mPitch;

		//Lock texture for manipulation
		SDL_LockTexture( tex, nullptr, &mPixels, &mPitch );
		
		for (int i=0; i<TEX_HEIGHT; i++) {
			for (int j=0; j<TEX_WIDTH; j++) {
				framebufferMixed[i][j].r = (uint8_t)((framebuffer[i][j].r + framebufferOld[i][j].r)/2);
				framebufferMixed[i][j].g = (uint8_t)((framebuffer[i][j].g + framebufferOld[i][j].g)/2);
				framebufferMixed[i][j].b = (uint8_t)((framebuffer[i][j].b + framebufferOld[i][j].b)/2);
				framebufferOld[i][j] = framebuffer[i][j];
			}
		}

				
		//Copy loaded/formatted surface pixels
		memcpy( mPixels, framebufferMixed, sizeof(framebufferMixed));

		//Unlock texture to update
		SDL_UnlockTexture( tex );
		
		SDL_RenderCopy(gRenderer, tex,nullptr,nullptr);
		// update screen
		SDL_RenderPresent(gRenderer);
		
		return 0;
}

static inline void closeSDL() {
	
	SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;
    SDL_Quit();
}

void msxhal_init() {
	
	if (initSDL()<0) {
		printf("Failed to initialize SDL!\n");
		exit(-1);
	}

	keyboard_init();
	
	SDL_is_initialized = true;
}

static isr_function custom_isr;
isr_function msxhal_install_isr(isr_function new_isr) {
	
	isr_function old = custom_isr;
	custom_isr = new_isr;
	return old;
}

void yield() {

	if (!SDL_is_initialized) {
		printf("yield called before init()\n");
		exit(-1);
	}
}

void wait_frame() {

	
	if (!SDL_is_initialized) {
		printf("wait_frame called before init()\n");
		exit(-1);
	}

	interrupt_count++;

	if (custom_isr != nullptr)
		(*custom_isr)();

	SDL_Event e;
	// handle event on queue
	while (SDL_PollEvent(&e) != 0) {
		
		keyboard_update(e);
		
		switch( e.type ){			
		case SDL_QUIT:
			closeSDL();
			exit(-1);
		default:
			break;
		}
	}
	
	drawScreen();
	
	displayFramebufferSDL();
	
	uint32_t delay = SDL_GetTicks()%(1000/60);
	SDL_Delay(1000/60-delay);
}


#endif

