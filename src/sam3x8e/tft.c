/**
 * @author Theodor Lindquist
 * @date 30 October 2014
 *
 */

#include "tft.h"

void tft_init(tft_screen *screen) {
	pio_set_pin((pio_reg_t *)screen->PORT_WR, screen->PIN_WR, 1);	//WR high
	pio_set_pin((pio_reg_t *)screen->PORT_CS, screen->PIN_CS, 0);	//CS low

	//write commands to initialize screen
	tft_write_com(screen, 0x11); tft_write_data(screen, 0x2004);
	tft_write_com(screen, 0x13); tft_write_data(screen, 0xCC00);
	tft_write_com(screen, 0x15); tft_write_data(screen, 0x2600);
	tft_write_com(screen, 0x14); tft_write_data(screen, 0x252A);
	tft_write_com(screen, 0x12); tft_write_data(screen, 0x0033);
	tft_write_com(screen, 0x13); tft_write_data(screen, 0xCC04);
	tft_write_com(screen, 0x13); tft_write_data(screen, 0xCC06);
	tft_write_com(screen, 0x13); tft_write_data(screen, 0xCC4F);
	tft_write_com(screen, 0x13); tft_write_data(screen, 0x674F);
	tft_write_com(screen, 0x11); tft_write_data(screen, 0x2003);
	tft_write_com(screen, 0x30); tft_write_data(screen, 0x2609);
	tft_write_com(screen, 0x31); tft_write_data(screen, 0x242C);
	tft_write_com(screen, 0x32); tft_write_data(screen, 0x1F23);
	tft_write_com(screen, 0x33); tft_write_data(screen, 0x2425);
	tft_write_com(screen, 0x34); tft_write_data(screen, 0x2226);
	tft_write_com(screen, 0x35); tft_write_data(screen, 0x2523);
	tft_write_com(screen, 0x36); tft_write_data(screen, 0x1C1A);
	tft_write_com(screen, 0x37); tft_write_data(screen, 0x131D);
	tft_write_com(screen, 0x38); tft_write_data(screen, 0x0B11);
	tft_write_com(screen, 0x39); tft_write_data(screen, 0x1210);
	tft_write_com(screen, 0x3A); tft_write_data(screen, 0x1315);
	tft_write_com(screen, 0x3B); tft_write_data(screen, 0x3619);
	tft_write_com(screen, 0x3C); tft_write_data(screen, 0x0D00);
	tft_write_com(screen, 0x3D); tft_write_data(screen, 0x000D);
	tft_write_com(screen, 0x16); tft_write_data(screen, 0x0007);
	tft_write_com(screen, 0x02); tft_write_data(screen, 0x0013);
	tft_write_com(screen, 0x03); tft_write_data(screen, 0x0003);
	tft_write_com(screen, 0x01); tft_write_data(screen, 0x0127);
	tft_write_com(screen, 0x08); tft_write_data(screen, 0x0303);
	tft_write_com(screen, 0x0A); tft_write_data(screen, 0x000B);
	tft_write_com(screen, 0x0B); tft_write_data(screen, 0x0003);
	tft_write_com(screen, 0x0C); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x41); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x50); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x60); tft_write_data(screen, 0x0005);
	tft_write_com(screen, 0x70); tft_write_data(screen, 0x000B);
	tft_write_com(screen, 0x71); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x78); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x7A); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x79); tft_write_data(screen, 0x0007);
	tft_write_com(screen, 0x07); tft_write_data(screen, 0x0051);
	tft_write_com(screen, 0x07); tft_write_data(screen, 0x0053);
	tft_write_com(screen, 0x79); tft_write_data(screen, 0x0000);
	tft_write_com(screen, 0x22);

	pio_set_pin((pio_reg_t *)screen->PORT_CS, screen->PIN_CS, 1);	//CS high
}

void tft_clear(tft_screen *screen) {
	pio_set_pin((pio_reg_t *)screen->PORT_CS, screen->PIN_CS, 0);
	uint16_t x,y;
	tft_set_xy(screen, 0, (uint16_t) screen->width, 0, (uint16_t) screen->height);
	for(x = 0; x <= screen->width; x++) {
		for(y = 0; y <= screen->height; y++) {
			tft_write_data(screen, 0x0000);
		}
	}
	pio_set_pin((pio_reg_t *)screen->PORT_CS, screen->PIN_CS, 1);
}

void tft_write(tft_screen *screen, uint16_t x, uint16_t y, uint16_t color) {
	pio_set_pin((pio_reg_t *)screen->PORT_CS, screen->PIN_CS, 0);
	tft_set_xy(screen, x, x, y, y);
	tft_write_data(screen, color);
}

/*uint32_t tft_read_input(tft_screen *screen, uint32_t *x, uint32_t *y) {
	return 0;
}*/

// The funcitons below should not be used by the API user
// They are only intended as "helper" functions for the tft-api

void tft_set_xy(tft_screen *screen, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {
	tft_write_com(screen, 0x46); tft_write_data(screen, (uint16_t) ((x2 << 8) | x1) );
	tft_write_com(screen, 0x47); tft_write_data(screen, y2 );
	tft_write_com(screen, 0x48); tft_write_data(screen, y1 );
	tft_write_com(screen, 0x20); tft_write_data(screen, x1 );
	tft_write_com(screen, 0x21); tft_write_data(screen, y1 );
	tft_write_com(screen, 0x22);
}

void tft_write_com(tft_screen *screen, uint8_t com) {
	//RS low
	pio_set_pin((pio_reg_t *)screen->PORT_RS, screen->PIN_RS, 0);
	tft_write_bus(screen, com);
}

void tft_write_data(tft_screen *screen, uint16_t data) {
	//RS high
	pio_set_pin((pio_reg_t *)screen->PORT_RS, screen->PIN_RS, 1);
	tft_write_bus(screen, data);
}

//bus functions

void tft_clear_bus(tft_screen *screen) {
	pio_set_pin((pio_reg_t *)screen->PORT_D0, screen->PIN_D0, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D1, screen->PIN_D1, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D2, screen->PIN_D2, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D3, screen->PIN_D3, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D4, screen->PIN_D4, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D5, screen->PIN_D5, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D6, screen->PIN_D6, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_D7, screen->PIN_D7, 0);
}

void tft_set_bus(tft_screen *screen, uint8_t value) {
	pio_set_pin((pio_reg_t *)screen->PORT_D0, screen->PIN_D0, value & (1<<0));
	pio_set_pin((pio_reg_t *)screen->PORT_D1, screen->PIN_D1, value & (1<<1));
	pio_set_pin((pio_reg_t *)screen->PORT_D2, screen->PIN_D2, value & (1<<2));
	pio_set_pin((pio_reg_t *)screen->PORT_D3, screen->PIN_D3, value & (1<<3));
	pio_set_pin((pio_reg_t *)screen->PORT_D4, screen->PIN_D4, value & (1<<4));
	pio_set_pin((pio_reg_t *)screen->PORT_D5, screen->PIN_D5, value & (1<<5));
	pio_set_pin((pio_reg_t *)screen->PORT_D6, screen->PIN_D6, value & (1<<6));
	pio_set_pin((pio_reg_t *)screen->PORT_D7, screen->PIN_D7, value & (1<<7));
}

void tft_commit_bus(tft_screen *screen) {
	//pulse WR
	pio_set_pin((pio_reg_t *)screen->PORT_WR, screen->PIN_WR, 0);
	pio_set_pin((pio_reg_t *)screen->PORT_WR, screen->PIN_WR, 1);
}

void tft_write_bus(tft_screen *screen, uint16_t data) {
	tft_clear_bus(screen);
	tft_set_bus(screen, (uint8_t)(data>>8));
	tft_commit_bus(screen);
	tft_clear_bus(screen);
	tft_set_bus(screen, (uint8_t)data);
	tft_commit_bus(screen);
}
