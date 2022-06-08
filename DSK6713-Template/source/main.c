/*
 * Nazwa projektu:  Projekt referencyjny dla zajùù laboratoryjnych z przedmiotu "Procesory DSP"
 * Nazwa pliku:     main.c
 * Autor:           Paweù Dùbal (pdabal@wat.edu.pl)
 * Student:         Imiù Nazwisko
 * Nr albumu:       00000
 * Przeznaczenie:   Funkcja wejùcia dla programu
 */

#include "pdsp.h"
#include "generator.h"
#include "generator_arbitralny.h"
#include "modulator.h"

volatile bool NewData = false; // Flaga informujùca o otrzymaniu nowej prùbki

CODEC_Data DataIn, DataOut;        // Zmienne do przechowywania prùbek odebranej/wysyùanej
CODEC_Data Samples[BUFFER_LENGTH]; // Bufor prùbek
Uint32 SampleNumber;

//-------------------------------------------------------------------
MOD_DIGITAL_Config_st MASK_Config;
MOD_DIGITAL_ASK_Handle_st MASK_Handle;
MOD_DIGITAL_PSK_Handle_st MPSK_Handle;
MOD_DIGITAL_FSK_Handle_st MFSK_Handle;

void main()
{
    MASK_Config.carrierAmplitude = 1.0f;
    MASK_Config.carrierFrequency = 1000.0f;
    MASK_Config.symbolLengthInPeriod = 2;
    MASK_Config.symbolLengthInBits = 1;
    MASK_Config.parameter = 200.0f;

    
    PDSP_Init();
    PDSP_CODEC_Init();
    PDSP_INT_Init();

    MOD_DIGITAL_ASK_Init(&MASK_Handle, MASK_Config);
    MOD_DIGITAL_PSK_Init(&MPSK_Handle, MASK_Config);
    MOD_DIGITAL_FSK_Init(&MFSK_Handle, MASK_Config);

    uint8_t symbol = 0x75;
    uint8_t symbolBit = 0;
    while (1)
    {
        Int16 value = 0;
        float valueF = 0;
#if PDSP_MODE == PDSP_MODE_POLL
        DataIn = CODEC_GetSampleStereo(); // Odczytanie nowej prùbki od kodeka
        CODEC_SetSampleStereo(DataOut);   // Wysùanie prùbki do kodeka
        SampleNumber++;
        // Przetwarzanie
        DataOut = DataIn;
//        valueF = MOD_DIGITAL_PSK_GetValue(&MPSK_Handle, symbol);
         valueF = MOD_DIGITAL_FSK_GetValue(&MFSK_Handle, symbol);
        DataOut.channel[0] = (Int16)(valueF *CODEC_V_TO_BIT);
         valueF = MOD_DIGITAL_ASK_GetValue(&MASK_Handle, symbol);
        DataOut.channel[1] = (Int16)(valueF *CODEC_V_TO_BIT);
        // DataOut.channel[1] = (Int16)(valueF * CODEC_V_TO_BIT);
        if((SampleNumber % (4*(Uint32)(CODEC_fs / MASK_Config.carrierFrequency) + 1)) == 0){
            symbol >>= 1;
            symbolBit++;
            if(symbolBit == 8){
                symbol = 0x75;
                symbolBit = 0;
            }
        }
#elif PDSP_MODE == PDSP_MODE_INT
        if (NewData == true)
        {
            NewData = false;
            DataOut = DataIn;
            Int16 value = (Int16)0;
            DataOut.channel[0] = value;
            DataOut.channel[1] = value;
        }
#endif
    }
}

/*----------------------------------------------------------------------*/
/*
 * Funkcja obsùugi przerwania od kodeka AIC23
 */
CODEC_IRQ
{
    DataIn = CODEC_GetSampleStereo(); // Odczytanie nowej prùbki od kodeka
    CODEC_SetSampleStereo(DataOut);   // Wysùanie prùbki do kodeka

    NewData = true; // Ustawienie flagi obecnoùci nowych danych

    SampleNumber++;

    DSK6713_LED_toggle(3); // Sygnalizacja obsùugi przerwania
    return;
}

/**
 * Funkcja obsùugi przerwania INT15 dla licznika TIM0
 */
TIMER0_IRQ
{
    DSK6713_LED_toggle(0);
    return;
}

/**
 * Funkcja obsùugi przerwania INT15 dla licznika TIM1
 */
TIMER1_IRQ
{
    DSK6713_LED_toggle(1);
    return;
}
