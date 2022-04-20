/*
 * pdsp.h
 *
 *  Created on: 12 lis 2018
 *      Author: pdabal
 */

#ifndef INCLUDE_PDSP_H_
#define INCLUDE_PDSP_H_

#include "pdsp_types.h"
#include "pdsp_codec.h"


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


#include "csl.h"
#include "csl_irq.h"
#include "csl_edma.h"
#include "csl_timer.h"

#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"
#include "dsk6713_aic23.h"

#include "math.h"

/* Stale matematyczne */
#define PDSP_PI                     3.14159265359f
#define PDSP_2PI                    6.28318530718f
#define PDSP_2PI_DIV_FS             (PDSP_2PI / CODEC_fs)
#define PDSP_2PI_TS                 (PDSP_2PI * CODEC_Ts)

/**/
#define PDSP_NUM_CHANNELS_MONO      1
#define PDSP_NUM_CHANNELS_STEREO    2

/**/
#define PDSP_MODE_INT               0
#define PDSP_MODE_INT_FRAME         1
#define PDSP_MODE_DMA_FRAME         2
#define PDSP_MODE_POLL              3

//-------------------------------------------------------------------------------------------------
/* Deklaracje stalych dla trybu pracy z potrójnym buforem */
#define BUFFER_LENGTH                         16 // Liczba próbek w buforze
#define BUFFER_NUM                   PDSP_BUFFOR // Liczba buforów
#define INITIAL_FILL_INDEX                     0 // Indeks bufora do wypelniania
#define INITIAL_DUMP_INDEX                     1 // Indeks bufora do odczytywania

#define BUFFER_SIZE                             8*1024
#define BUFFER_MASK                             0x00001FFF

#define CODEC_IRQ                               interrupt void c_int11_aic23(void)
#define TIMER0_IRQ                              interrupt void c_int14_tim0(void)
#define TIMER1_IRQ                              interrupt void c_int15_tim1(void)

/* Deklaracja zmiennych do odczytywania i zapisywania prÃ³bek z interfejsu */
#if   PDSP_NUM_CHANNELS ==  PDSP_NUM_CHANNELS_MONO
extern  Int16   sampleIn;
extern  Int16   sampleOut;
#elif PDSP_NUM_CHANNELS == PDSP_NUM_CHANNELS_STERO
extern  CODEC_Data   sampleIn;
extern  CODEC_Data   sampleOut;
#endif

#include "pdsp_config.h"

extern far void vectors();
/* */
extern  volatile bool               NewData;

/* */
void PDSP_Init();
void PDSP_CODEC_Init();
void PDSP_INT_Init(void);

uint32_t PDSP_GetValue();
void PDSP_SetValue(CODEC_Data value);

Uint8 PDSP_DIP_getValue(void);
void PDSP_LED_setValue(Uint8 bin);

#endif /* INCLUDE_PDSP_H_ */
