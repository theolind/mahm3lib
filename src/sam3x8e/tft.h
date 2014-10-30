/**
 * @brief TFT display code
 * @details Provides rendering on a TFT display and touch input (both polling
 * and interrupt based)
 *
 * @author Theodor Lindquist
 * @date 28 October 2014
 *
 */

// Struct containing an instace of a tft screen
typedef struct tft_screen {
	uint32_t PORT_CS;
	uint32_t PIN_CS;

	uint32_t PORT_WR;
	uint32_t PIN_WR;

	uint32_t PORT_RS;
	uint32_t PIN_RS;

	uint32_t PORT_D0;
	uint32_t PIN_D0;

	uint32_t PORT_D1;
	uint32_t PIN_D1;

	uint32_t PORT_D2;
	uint32_t PIN_D2;

	uint32_t PORT_D3;
	uint32_t PIN_D3;

	uint32_t PORT_D4;
	uint32_t PIN_D4;

	uint32_t PORT_D5;
	uint32_t PIN_D5;

	uint32_t PORT_D6;
	uint32_t PIN_D6;

	uint32_t PORT_D7;
	uint32_t PIN_D7;
} tft_screen;

/**
 * Initialize the tft screen
 * @param screen the screen instance
 */
void *tft_init(tft_screen &screen);

/**
 * Writes a pixel to the screen memory. Alternative name tft_write_pixel / tft_put_pixel / tft_render_pixel
 * @param screen screen instance
 * @param x xpos
 * @param y ypos
 * @param color color of pixel, format: 0xRRGGBB
 */
void tft_write(tft_screen &screen, uint32_t x, uint32_t y, uint32_t color);

/**
 * Reads a pixel from the screen, this will be useful if a user wants to
 * render things with alpha values (transperancy)
 * @param screen screen instance
 * @param point point of pixel to get data from
 * @return the color of the pixel, format: 0xRRGGBB
 */
uint32_t tft_read(tft_screen &screen, uint32_t &x, uint32_t &y);

/**
 * Updates the screen. This must be done to show new data.
 * @param screen screen instance
 */
void tft_update(tft_screen &screen);

/**
 * Poll for input
 * @param screen screen instance
 * @param x will contain the x-coordinate of the touch
 * @param y will contain the y-coordinate of the touch
 * @return true if touch is occuring
 */
uint32_t tft_read_input(tft_screen &screen, uint32_t *x, uint32_t *y);
