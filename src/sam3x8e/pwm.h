/**
 * @file pwm.c
 * @anchor <pwm>
 * @brief Pulse Width Modulation (PWM)
 * @details {This class is used to output a pulse width modulated waveform
 * using the PWM peripheral on the MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.}
 * @author {Saeed Ghasemi}
 * @version {v0.1}
 * @date {28 sep 2014}
 * @pre {The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.}
 * @bug {Manual and automated testing are being designed.}
 */

#ifndef PWM_H_
#define PWM_H_

/**
 * MASKs are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_MASK
 */
#define PWM_CLK_PREA_MASK				(0x00000F00)
#define PWM_CLK_PREB_MASK				(0x0F000000)
#define PWM_CLK_DIVA_MASK				(0x000000FF)
#define PWM_CLK_DIVB_MASK				(0x00FF0000)

/**
 * @def <defines>
 * These defines are masks for the PWM channels and can be used as the channel
 * input of every function.
 */
#define PWM_CHANNEL_0_MASK				(1<<0)
#define PWM_CHANNEL_1_MASK				(1<<1)
#define PWM_CHANNEL_2_MASK				(1<<2)
#define PWM_CHANNEL_3_MASK				(1<<3)
#define PWM_CHANNEL_4_MASK				(1<<4)
#define PWM_CHANNEL_5_MASK				(1<<5)
#define PWM_CHANNEL_6_MASK				(1<<6)
#define PWM_CHANNEL_7_MASK				(1<<7)
#define PWM_CHANNEL_ALL_MASK			(0xFF)

#define PWM_CMRx_CPRE_MASK				(0x0000000F)
#define PWM_CMRx_CALG_MASK				(1 << 8)
#define PWM_CMRx_CPOL_MASK				(1 << 9)
#define PWM_CMRx_CES_MASK				(1 << 10)
#define PWM_CMRx_DTE_MASK				(1 << 16)
#define PWM_CMRx_DTHI_MASK				(1 << 17)
#define PWM_CMRx_DTLI_MASK				(1 << 18)

#define PWM_CDTYx_CDTY_MASK				(0x0000FFFF)
#define PWM_CDTYUPDx_CDTYUPD_MASK		(0x0000FFFF)

#define PWM_CPRDx_CPRD_MASK				(0x0000FFFF)
#define PWM_CPRDUPDx_CPRDUPD_MASK		(0x0000FFFF)
/////////////////////////////////////////////////////////////////////////////
/**
 * Parameters are being defined like this:
 * [PERIPHERAL]_[REGISTER]_[SECTION]_VALUE
 */
//PESCALLERS FOR CLOCK REGISTER
#define PWM_CLK_PRES_1					(0b0000)
#define PWM_CLK_PRES_2					(0b0001)
#define PWM_CLK_PRES_4					(0b0010)
#define PWM_CLK_PRES_8					(0b0011)
#define PWM_CLK_PRES_16					(0b0100)
#define PWM_CLK_PRES_32					(0b0101)
#define PWM_CLK_PRES_64					(0b0110)
#define PWM_CLK_PRES_128				(0b0111)
#define PWM_CLK_PRES_256				(0b1000)
#define PWM_CLK_PRES_512				(0b1001)
#define PWM_CLK_PRES_1024				(0b1010)
//PESCALLERS FOR CHANNEL MODE REGISTER
#define PWM_CMRx_PRES_1					(0b0000)
#define PWM_CMRx_PRES_2					(0b0001)
#define PWM_CMRx_PRES_4					(0b0010)
#define PWM_CMRx_PRES_8					(0b0011)
#define PWM_CMRx_PRES_16				(0b0100)
#define PWM_CMRx_PRES_32				(0b0101)
#define PWM_CMRx_PRES_64				(0b0110)
#define PWM_CMRx_PRES_128				(0b0111)
#define PWM_CMRx_PRES_256				(0b1000)
#define PWM_CMRx_PRES_512				(0b1001)
#define PWM_CMRx_PRES_1024				(0b1010)
#define PWM_CMRx_PRES_CLOCKA			(0b1011)
#define PWM_CMRx_PRES_CLOCKB			(0b1100)
// PARAMETERS FOR THE ALIGNMENT
#define PWM_CMRx_ALIGN_LEFT				0
#define PWM_CMRx_ALIGN_CENTER			1
// PARAMETERS FOR THE POLARITY
#define PWM_CMRx_POLARITY_HIGH			1
#define PWM_CMRx_POLARITY_LOW			0

//DIVIDERS FOR CLKA AND CLKB
#define PWM_CLK_DIVx_TURNOFF			0


//////////////////////////////////////////////////////////////////////////

// Externally available typedefs, variables and definitions
/**
 * @typedef
 * This structure is used with pwm_init() to set the settings for the clocks A
 * and B of the PWM peripheral.
 * @param clkA_prescaler {This is the prescaler for clock A.
 * Parameter prefix: PWM_CLK_PRES_}
 * @param clkA_divisor {This is the divisor for clock A. Set this between 0 and
 * 255. 0 will turn the clock off.}
 * @param clkB {This is the prescaler for clock B.
 * Parameter prefix: PWM_CLK_PRES_}
 * @param clkA_divisor {This is the divisor for clock B. Set this between 0 and
 * 255. 0 will turn the clock off.}
 */
typedef struct pwm_clk_setting{
	uint32_t clkA_prescaler;
	uint32_t clkA_divisor;
	uint32_t clkB_prescaler;
	uint32_t clkB_divisor;
}pwm_clk_setting;

/**
 * @typedef
 * This structure is used with pwm_init_channel() to set the settings of a
 * channel. Be aware that either frequency or prescaler must be specified.
 *
 * @param channel {The channel to be initialized. Prefix: PWM_CHANNEL_}
 * @param polarity {Sets the polarity of the channel.
 * Parameter prefix: PWM_POLARITY_}
 * @param alignment {Sets the alignment of the channel.
 * Parameter prefix: PWM_ALIGN_}
 * @param duty_cycle {The initial duty cycle of the channel. (Optional)}
 * @param use_prescaler {Must be 1 or 0 to indicate whether prescaler or
 * frequency must be used.}
 * @param prescaler {Sets the channel prescaler. This can also select clock A
 * and B. Parameter prefix: PWM_CMRx_PRES_ (Needed only if use_prescaler it
 * set to 1)}
 * @param frequency {The frequency of the PWM waveform for this channel.
 * (Set only if use_prescaler is set to 0)}
 * @param clock_ID {In case that frequency is specified, then clock_ID must
 * specify which CLKx to be used for this purpose. Prefix: PWM_CLK_ID_}
 */
typedef struct pwm_channel_setting{
	uint32_t channel;
	uint32_t polarity;
	uint32_t alignment;
	uint32_t duty_cycle;
	uint32_t use_prescaler;
	uint32_t prescaler;
	uint32_t frequency;
	uint32_t clock_ID;
}pwm_channel_setting;

/**
 * @def
 * These are parameters used in conjunction with initializing a PWM channel.
 */
#define PWM_POLARITY_HIGH		1
#define PWM_POLARITY_LOW		0
#define PWM_ALIGN_LEFT			0
#define PWM_ALIGN_CENTER		1

/**
 * @def
 * These are parameters used in conjunction with turning of clkA and B.
 */
#define PWM_CLK_ID_CLKA			0
#define PWM_CLK_ID_CLKB			1

//////////////////////////////////////////////////////////////////////////
// Function Prototypes

/**
 * Default initialization for the PWM peripheral
 * This leaves clkA and clkB off and starts the peripheral clock.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 * @pre {This function requires the PMC API.}
 */
uint8_t	 pwm_init_peripheral_default(void);
/**
 * Initialize the PWM peripheral with a structure containing clock_settings.
 * This function controls clkA and clkB and starts the peripheral clock.
 * It is recommended to use pwm_set_channel_frequency() to select a clock.
 *
 * @return error (0 = FAIL, 1 = SUCCESS)
 * @pre {This function requires the PMC API.}
 */
uint8_t	 pwm_init_peripheral(struct pwm_clk_setting clk_settings);
/**
 * This function will enable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to enable all channel at once.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return error Will always return 1 = SUCCESS
 */
uint8_t pwm_channel_enable(uint32_t channel);
/**
 * This function will disable the selected channel, identified with predefined
 * values, like: PWM_CHANNEL_x_MASK.
 *
 * Alternatively use PWM_CHANNEL_ALL_MASK to disable all channel at once.
 *
 * @param channel {The channel to be disabled, use prefix: PWM_CHANNEL_}
 * @return error (1 = SUCCESS and 0 = FAIL)
 */
uint8_t pwm_channel_disable(uint32_t channel);
/**
 * Turns off one of two clocks in PWM that are called clkA and clkB.
 *
 * @param clock_id
 * @return error (0 = FAIL, 1 = SUCCESS)
 */
uint8_t  pwm_turn_off_clkx(uint8_t clock_id);
/**
 * Initializes a single channel in the peripheral out of 8 in total.
 * This function will not multiplex the pin to the peripheral channel and
 * neither enable the channel.
 *
 * @param channel
 * @return error (0 = FAIL, 1 = SUCCESS)
 */
uint8_t  pwm_init_channel(struct pwm_channel_setting channel);
/**
 * Set the channel polarity.
 * This can reverse the duty cycle. Important when using the PWMLx pins.
 *
 * @param channel {The channel to set the polarity for. ex PWM_CHANNEL_0_MASK}
 * @return
 */
uint8_t  pwm_set_channel_polarity(uint32_t channel, uint32_t pwm_polarity);
/**
 * Choose either clkA or B to be the source for the PWM channel.
 *
 * @param channel {Indicated for which channel the source must be selected.}
 * @param pwm_clk_id {Choose one of two predefined values, ex PWM_CLK_ID_CLKA}
 * @return
 */
uint8_t  pwm_set_channel_clocksource(uint32_t channel, uint32_t pwm_clk_id);
/**
 * Set the channel alignment
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return
 */
uint8_t  pwm_set_channel_alignment(uint32_t channel, uint32_t PWM_ALIGN_);
/**
 * Set the channel prescaler
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param prescaler {This is the prescaler to be set.
 * Use one of the predefined. prefix: PWM_CMRx_PRES_}
 * @return error
 */
uint8_t  pwm_set_channel_prescaler(uint32_t channel, uint32_t prescaler);
/**
 * Shuts down the peripheral but keeps all settings
 * @return
 */
uint8_t  pwm_shutdown(void);
/**
 * Reset and turns off the peripheral
 * @return
 */
uint8_t  pwm_close(void);
/**
 * Resets the peripheral and disables all channels
 * @return error
 */
uint8_t  pwm_reset(void);
/**
 * Read what was earlier written to the channel
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @return {Previously set duty cycle (if 0 is received then it could mean
 * error)}
 */
uint32_t pwm_read(uint32_t channel);
/**
 * Writes an output to a given channel by setting the channel duty cycle.
 *
 * @param channel {The channel to be enabled, use prefix: PWM_CHANNEL_}
 * @param duty_cycle {must be between 0 and period as in CPRD in the register PWM_CPRDx.}
 * @return error (1 = SCCESS and 0 = FAIL)
 */
uint8_t  pwm_write(uint32_t channel, uint32_t duty_cycle);
// Set the duty cycle between 0 and period
//uint32_t pwm_set_channel_duty_cycle(uint32_t channel, uint32_t duty_cycle);

/**
 * This function will return the state of the PWM channel.
 *
 * @param channel {the channel to get the status for}
 * @return 1 if the channel is enabled, 0 if it is disabled
 */
uint8_t pwm_channel_status(uint32_t channel);

/**
 * This function will automatically select the necessary prescaler and divider
 * for the chosen clock. The clocks can either be clkA or clkB.
 * This function also update the necessary register for this setting.
 * This function will not change the state of the channel. The channel may not
 * be enabled when invoking this function.
 *
 * The frequency set will be the nearest to the chosen frequency as possible
 * but not exactly.
 *
 * This function will return an error if it can't find a setting for the frequency.
 * In case of error, the function will not have modified any registers.
 *
 * @param channel {The channel to set the frequency for}
 * @param frequency {The frequency to calculate for}
 * @param pwm_clk_id {the ID for the clock you want to modify,
 * ex: PWM_CLK_ID_CLKA}
 * @return {error, this will indicate whether a setting could be found for the chosen frequency.}
 */
uint8_t pwm_set_channel_frequency(uint32_t channel, uint32_t frequency,
		uint32_t pwm_clk_id);

/**
 * The PWM peripheral has 13 different clocks. Among those, 11 are scaled down
 * clocks of the system clock and the two others are the more flexible clocks
 * that can be set to much lower freuencies than the prescalers. These clock go
 * by the name Clock A and Clock B. They are derived by the SYS_CLK_FREQ which
 * they prescale and the outcome of that they can furthere divide with a divisor
 * and achieve lower frequencies for the PWM peripheral. These clocks can be
 * turned off when not needed.
 *
 * This function will set the prescaler and divisor for the indicated clock.
 * If the prescaler is other than 0, the clock will be turned on.
 *
 * @param clock_id {The id for the clock to be set. Use prefix: PWM_CLK_ID_}
 * @param prescaler {Use one of the predefined prescalers.
 * Prefix: PWM_CLK_PRES_}
 * @param divisor {Use a value between 1 and 255.}
 * @return error
 */
uint8_t pwm_set_clkx(uint32_t clock_id, uint32_t prescaler, uint32_t divisor);

//////////////////////////////////////////////////////////////////////////

#endif /* PWM_H_ */
