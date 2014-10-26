/**
 * @file pwm.c
 * @brief Pulse Width Modulation (PWM)
 * @details An API for controlling the PWM peripheral inside a SAM3X8E MCU.
 * This peripheral is an embedded macrocell within the MCU and all of its 44
 * registers are physically mapped on this macrocell, therefore modifying the
 * register requires that the peripheral clock is enabled in PMC. However, when
 * modified, the register values are stored even it the peripheral clock is
 * turned off and the peripheral will continue its operation when the clock is
 * turned back on.
 * This API implements all 8 independent channels and their change of polarity,
 * alignment, PWM frequency and handles the pin multiplexing for all 16 outputs
 * of the peripheral. The API does not stop any clock once it has started them.
 * @author Saeed Ghasemi
 * @date 28 sep 2014
 * @pre The API handles all of its dependencies on other peripherals
 * internally and will start other clocks in order to properly operate.
 * @bug Manually tested all functions to comply with all demands.
 * The only problem is that the register set defined below is not working when
 * implemented. The register mapping currently working is non conventional.
 */

