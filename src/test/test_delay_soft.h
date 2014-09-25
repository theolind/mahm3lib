/**
 * \class test_delay_soft
 * \brief These functions will use hardware timers to test the software delay functions
 * \author Saeed Ghasemi
 * \version 0.2
 * \date 22 sep 2014
 * \bug Caution: These functions are tested but not after integrating the PIO-API. Tests will follow.
 */


#ifndef ITIMERDELAYBYSOFTWARE_H_
#define ITIMERDELAYBYSOFTWARE_H_





//////////////////////////////////////////////////////////////////////////
// Function prototypes
void test_delay_soft_setup(void);
void test_delay_soft_tear_down(void);
void test_delay_soft_reset(void);
void test_delay_soft_delay_3us(void);



#endif /* ITIMERDELAYBYSOFTWARE_H_ */
