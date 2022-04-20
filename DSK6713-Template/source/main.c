/*
 * Nazwa projektu:  Projekt referencyjny dla zajêæ laboratoryjnych z przedmiotu "Procesory DSP"
 * Nazwa pliku:     main.c
 * Autor:           Pawe³ D¹bal (pdabal@wat.edu.pl)
 * Student:         Imiê Nazwisko
 * Nr albumu:       00000
 * Przeznaczenie:   Funkcja wejœcia dla programu
 */

#include "pdsp.h"

volatile bool NewData = false;              // Flaga informuj¹ca o otrzymaniu nowej próbki

CODEC_Data DataIn, DataOut;                 // Zmienne do przechowywania próbek odebranej/wysy³anej
CODEC_Data Samples[BUFFER_LENGTH];          // Bufor próbek
Uint32 SampleNumber;

void main()
{
    PDSP_Init();
    PDSP_CODEC_Init();
    PDSP_INT_Init();

    while (1)
    {
#if PDSP_MODE == PDSP_MODE_POLL
        DataIn = CODEC_GetSampleStereo();  // Odczytanie nowej próbki od kodeka
        CODEC_SetSampleStereo(DataOut);  // Wys³anie próbki do kodeka
        SampleNumber++;
        // Przetwarzanie
        DataOut = DataIn;
#elif PDSP_MODE == PDSP_MODE_INT
        if (NewData == true)
        {
            NewData = false;
            // Przetwarzanie
            DataOut = DataIn;
        }
#endif
    }
}

/*----------------------------------------------------------------------*/
/*
 * Funkcja obs³ugi przerwania od kodeka AIC23
 */
CODEC_IRQ
{
    DataIn = CODEC_GetSampleStereo();   // Odczytanie nowej próbki od kodeka
    CODEC_SetSampleStereo(DataOut);// Wys³anie próbki do kodeka

    NewData = true;// Ustawienie flagi obecnoœci nowych danych

    SampleNumber++;

    DSK6713_LED_toggle(3);// Sygnalizacja obs³ugi przerwania
    return;
}

/**
 * Funkcja obs³ugi przerwania INT15 dla licznika TIM0
 */
TIMER0_IRQ
{
    DSK6713_LED_toggle(0);
    return;
}

/**
 * Funkcja obs³ugi przerwania INT15 dla licznika TIM1
 */
TIMER1_IRQ
{
    DSK6713_LED_toggle(1);
    return;
}
