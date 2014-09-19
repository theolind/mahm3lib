//#define ADC_CR		(*p_ADC_CR) 	// Control Register
//#define ADC_MR  	(*p_ADC_MR) 	// Mode Register
//#define ADC_CHER  	(*p_ADC_CHER) 	// Channel Enable Register
//#define ADC_CHDR 	(*p_ADC_CHDR) 	// Channel Disable Register
//#define ADC_CHSR 	(*p_ADC_CHSR) 	// Channel Status Register
//#define ADC_LCDR  	(*p_ADC_LCDR) 	// Last Converted Data Register
//#define ADC_CDR0  	(*p_ADC_CDR0) 	// Channel Data Register 0
//
//uint32_t *const p_ADC_CR 	= (uint32_t *) 0x400C0000u;
//uint32_t *const p_ADC_MR 	= (uint32_t *) 0x400C0004u;
//uint32_t *const p_ADC_CHER 	= (uint32_t *) 0x400C0010u;
//uint32_t *const p_ADC_CHDR 	= (uint32_t *) 0x400C0014u;
//uint32_t *const p_ADC_CHSR 	= (uint32_t *) 0x400C0018u;
//uint32_t *const p_ADC_LCDR 	= (uint32_t *) 0x400C0020u;
//uint32_t *const p_ADC_CDR0 	= (uint32_t *) 0x400C0050u;

void setUp(void);
void tearDown(void);
void resetTest(void);
void test_adc_channel_enabled(void);
void test_adc_12bit(void);
void test_adc_10bit(void);
void test_adc_channel_enabled(void);
