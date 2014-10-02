/**
 * @file test_adc.h
 * @brief Analog-to-Digital Converter (ADC) unit tests
 * @details This class is used to test ADC capabilities of this API
 *
 * @author Prince Balabis
 * @author Andreas Drotth
 * @date 30 September 2014
 */

#include "sam3x8e/adc.h"

void test_adc_channel_enabled(void);
void test_adc_channel_disabled(void);
void test_adc_channel_status(void);
void test_adc_set_resolution_12_bit(void);
void test_adc_set_resolution_10_bit(void);
