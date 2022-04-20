#ifndef INCLUDE_PDSP_PDSP_CODEC_H_
#define INCLUDE_PDSP_PDSP_CODEC_H_

#include "dsk6713_aic23.h"              // Support file for codec DSK
#include "pdsp_config.h"

/* Stale przetwornika ADC/DAC - 16 bitowy, max 1 V_RMS */
#define CODEC_Vpp                    2.8284271f
#define CODEC_Bres               65536.0f
#define CODEC_Vres                   (CODEC_Vpp / CODEC_Bres)
#define CODEC_V_TO_BIT               (CODEC_Bres / CODEC_Vpp)

/* Stale przetwarzania DSP */
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_96KHZ
#define CODEC_fs                 96000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_48KHZ
#define CODEC_fs                 48000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_44KHZ
#define CODEC_fs                 44000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_32KHZ
#define CODEC_fs                 32000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_24KHZ
#define CODEC_fs                 24000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_16KHZ
#define CODEC_fs                 16000.0f
#endif
#if PDSP_FS_AIC23 == DSK6713_AIC23_FREQ_8KHZ
#define CODEC_fs                 8000.0f
#endif

#define CODEC_Ts                 1/CODEC_fs

/* Okreœlenie numeru kanalu */
#define LEFT        1                   // Data structure for union of 32-bit data into two 16-bit data
#define RIGHT       0                   //

/*---------------------------------------------------------------------------------------*/
                                                        // LRS LIM  xx    LIV
                                                        // RLS RIM  xx    RIV
#define DSK6713_AIC23_L_IN_VOL_0            0x0017      //   0   0  00  10111
#define DSK6713_AIC23_R_IN_VOL_0            0x0017      //   0   0  00  10111
/*---------------------------------------------------------------------------------------*/
                                                        // LRS LZC      LHV
                                                        // RLS RZC      RHV
#define DSK6713_AIC23_L_HP_VOL_0            0x01F9      //   1   1  1111001
#define DSK6713_AIC23_R_HP_VOL_0            0x01F9      //   1   1  1111001
/*---------------------------------------------------------------------------------------*/
                                                        // STA STE DAC BYP INSEL MICM MICB
#define DSK6713_AIC23_ANA_PATH_INPUT_MIC    0x0015      // 000   0   1   0     1    0    1
#define DSK6713_AIC23_ANA_PATH_INPUT_LINE   0x0011      // 000   0   1   0     0    0    1
/*---------------------------------------------------------------------------------------*/
                                                        // DACM  DEEMP  ADCHP
#define DSK6713_AIC23_DIG_PATH_             0x0015      //    0     00      0
/*---------------------------------------------------------------------------------------*/
                                                        // OFF CLK OSC OUT DAC ADC MIC LINE
#define DSK6713_AIC23_POWERDOWN_ALL_ON      0x0000      //   0   0   0   0   0   0   0    0
/*---------------------------------------------------------------------------------------*/
                                                        // xx MS  LRSWAP LRP IWL FOR
#define DSK6713_AIC23_DIGIF_                0x0043      // 00  1       0   0  00  11
/*---------------------------------------------------------------------------------------*/
                                                        // x CLKOUT CLKIN   SR BOSR USB
#define DSK6713_AIC23_SAMPLERATE_           0x0001      // 0      0     0 0000    0   1
/*---------------------------------------------------------------------------------------*/
                                                        // x RES RES xxxxx ACT
#define DSK6713_AIC23_DIGACT_               0x0001      // 0   0   0 00000   1
/*---------------------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------- */

/* Unia do przechowywania próbki z kodeka AIC23 */
typedef union {
    Uint32  uint;
    Int16   channel[2];
} CODEC_Data;

typedef struct{
    float   channel[2];
}CODEC_DataF;

/* ------------------------------------------------------------------------- */
/* Zmienne deklarowane na zewn¹trz */

extern  CODEC_Data                  DataIn, DataOut;
extern  CODEC_Data                  Samples[];

extern  DSK6713_AIC23_CodecHandle   hAIC23;

void CODEC_SetSampleStereo(CODEC_Data sample);
void CODEC_SetSampleMono(Int16 sample);
void CODEC_SetSampleFloat(float sample);

CODEC_Data CODEC_GetSampleStereo(void);
Int16 CODEC_GetSampleMono(void);
float CODEC_GetSampleFloat(void);

#endif /* INCLUDE_PDSP_PDSP_CODEC_H_ */
