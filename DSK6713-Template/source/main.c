/*
 * Nazwa projektu:  Projekt referencyjny dla zaj�� laboratoryjnych z przedmiotu "Procesory DSP"
 * Nazwa pliku:     main.c
 * Autor:           Pawe� D�bal (pdabal@wat.edu.pl)
 * Student:         Imi� Nazwisko
 * Nr albumu:       00000
 * Przeznaczenie:   Funkcja wej�cia dla programu
 */

#include "pdsp.h"

volatile bool NewData = false;              // Flaga informuj�ca o otrzymaniu nowej pr�bki

CODEC_Data DataIn, DataOut;                 // Zmienne do przechowywania pr�bek odebranej/wysy�anej
CODEC_Data Samples[BUFFER_LENGTH];          // Bufor pr�bek
Uint32 SampleNumber;

void main()
{
    PDSP_Init();
    PDSP_CODEC_Init();
    PDSP_INT_Init();

    while (1)
    {
#if PDSP_MODE == PDSP_MODE_POLL
        DataIn = CODEC_GetSampleStereo();  // Odczytanie nowej pr�bki od kodeka
        CODEC_SetSampleStereo(DataOut);  // Wys�anie pr�bki do kodeka
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
 * Funkcja obs�ugi przerwania od kodeka AIC23
 */
CODEC_IRQ
{
    DataIn = CODEC_GetSampleStereo();   // Odczytanie nowej pr�bki od kodeka
    CODEC_SetSampleStereo(DataOut);// Wys�anie pr�bki do kodeka

    NewData = true;// Ustawienie flagi obecno�ci nowych danych

    SampleNumber++;

    DSK6713_LED_toggle(3);// Sygnalizacja obs�ugi przerwania
    return;
}

/**
 * Funkcja obs�ugi przerwania INT15 dla licznika TIM0
 */
TIMER0_IRQ
{
    DSK6713_LED_toggle(0);
    return;
}

/**
 * Funkcja obs�ugi przerwania INT15 dla licznika TIM1
 */
TIMER1_IRQ
{
    DSK6713_LED_toggle(1);
    return;
}
