/*
 * PIO unit tests
 *
 * Author:	Theodor Lindquist
 * 			Soded Alatia
 * 			Mathias Beckius
 *
 * Date:	12 October 2014
 */

#ifndef TEST_PIO_H_
#define TEST_PIO_H_

void test_pio_enable_pin(void);  // testing pio_enable_pin
void test_pio_disable_pin(void); // testing pio_disable_pin
void test_pio_pullup(void);	//testing pio_conf_*
void test_pio_output(void);	//testing pio_conf_*
void test_pio_read_pin(void);	//testing pio_read_*
void test_pio_set_output(void);	//testing pio_set_*
void test_pio_set_outputs(void);
void test_pio_conf_multiple_pins(void);
void test_pio_select_glitch_filter(void);
void test_pio_enable_glitch_filter(void);

#endif /* TEST_PIO_H_ */
