/*!
 * \brief brief description
 * \details detailed description
 *
 * \author Theodor Lindquist
 *
 * \version 0.1
 * \date Sep 18, 2014
 *
 * \pre requirements
 */

#ifndef TEST_PIO_H_
#define TEST_PIO_H_

#include <stdint.h>

void pio_setUp();
void pio_tearDown();
void pio_resetTest();
uint8_t test_pio_pullup();
uint8_t test_pio_output();

#endif /* TEST_PIO_H_ */
