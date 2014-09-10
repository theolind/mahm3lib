/*
 * unity_hw_setup.h
 *
 * Created: 2014-09-07 15:43:32
 *  Author: m11p0910
 */ 

#ifndef UNITY_HW_SETUP_H_
#define UNITY_HW_SETUP_H_

#include <setjmp.h>
#include <stdio.h>
//#include <stdio_serial.h>

// EEFC Flash Mode Register 0
#define EEFC_FMR_0 (*p_EEFC_FMR_0)
// EEFC Flash Mode Register 1
#define EEFC_FMR_1 (*p_EEFC_FMR_1)

#define PMC_SR (*((volatile uint32_t *)0x400E0668U))

/* -------- EEFC_FMR : (EFC Offset: 0x00) EEFC Flash Mode Register -------- */
#define EEFC_FMR_FRDY (0x1u << 0) /**< \brief (EEFC_FMR) Ready Interrupt Enable */
#define EEFC_FMR_FWS_Pos 8
#define EEFC_FMR_FWS_Msk (0xfu << EEFC_FMR_FWS_Pos) /**< \brief (EEFC_FMR) Flash Wait State */
#define EEFC_FMR_FWS(value) ((EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos)))

#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))

void unity_hw_setup(void);

#endif /* UNITY_HW_SETUP_H_ */
