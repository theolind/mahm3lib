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
	//To be determined, might be joined to tft_settings
} tft_screen;

// Struct defining a point on the screen
typedef struct tft_point {
	uint32_t x;
	uint32_t y;
} tft_point;

// Struct defining a color
typedef struct tft_color {
	uint32_t r;
	uint32_t g;
	uint32_t b;
} tft_color;

/**
 * Initialize the tft screen
 * @param screen the screen instance
 */
void *tft_init(tft_screen &screen);

/**
 * Writes a pixel to the screen memory. Alternative name tft_write_pixel / tft_put_pixel / tft_render_pixel
 * @param screen screen instance
 * @param point point on screen to render to
 * @param color color of pixel
 */
void tft_write(tft_screen &screen, tft_point &point, tft_color &color);

/**
 * Reads a pixel from the screen, this will be useful if a user wants to
 * render things with alpha values (transperancy)
 * @param screen screen instance
 * @param point point of pixel to get data from
 * @return tft_color, the color of the pixel
 */
tft_color *tft_read(tft_screen &screen, tft_point &point);

/**
 * Updates the screen. This must be done to show new data.
 * @param screen screen instance
 */
void tft_update(tft_screen &screen);

/**
 * Poll for input
 * @param screen screen instance
 * @return tft_point the point where the screen was touched
 */
tft_point *tft_read_input(tft_screen &screen);
