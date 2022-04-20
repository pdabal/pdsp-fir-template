#ifndef INCLUDE_PDSP_CONFIG_H_
#define INCLUDE_PDSP_CONFIG_H_

// Do wyboru jedna z lini konfiguruj¹cej tryb pracy:
//#define PDSP_MODE               PDSP_MODE_INT
#define PDSP_MODE               PDSP_MODE_POLL
//#define PDSP_MODE               PDSP_MODE_INT_FRAME
//#define PDSP_MODE               PDSP_MODE_DMA_FRAME

// Do wyboru jedna z lini konfiguruj¹cej liczbê kana³ów:
#define PDSP_NUM_CHANNELS       PDSP_NUM_CHANNELS_MONO
//#define PDSP_NUM_CHANNELS       PDSP_NUM_CHANNELS_STEREO

// Do wyboru jedna z lini konfiguruj¹cej wejœcie kodeka AIC23:
#define PDSP_AIC_INPUT          PDSP_AIC_LineInput
//#define PDSP_AIC_INPUT         PDSP_AIC_MicInput_0db
//#define PDSP_AIC_INPUT         PDSP_AIC_MicInput_20db

/* Konfiguracja czêstotliwoœci próbkowania */
// Do wyboru jedna z lini konfiguruj¹cej czêstotliwoœæ próbkowania
#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_96KHZ    // 6713 DSK at 96kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_48KHZ    // 6713 DSK at 48kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_44KHZ    // 6713 DSK at 44kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_32KHZ    // 6713 DSK at 32kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_24KHZ    // 6713 DSK at 24kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_16KHZ    // 6713 DSK at 16kHz sample rate
//#define PDSP_FS_AIC23          DSK6713_AIC23_FREQ_8KHZ     // 6713 DSK at 8kHz sample rate

#define PDSP_TIMER0_INT          1
#define PDSP_TIMER1_INT          1

#define PDSP_TIMER0_PERIOD       28125000
#define PDSP_TIMER1_PERIOD       28125

/*  */
// Do wyboru jedna z lini konfiguruj¹cej typ bufora
#define PDSP_BUFFOR             1
//#define PDSP_BUFFOR             2
//#define PDSP_BUFFOR             3

//#define PDSP_USE_EDMA           1

#endif /* INCLUDE_PDSP_CONFIG_H_ */
