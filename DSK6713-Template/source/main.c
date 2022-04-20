/*
 * Nazwa projektu:  Projekt referencyjny dla zaj�� laboratoryjnych z przedmiotu "Procesory DSP"
 * Nazwa pliku:     main.c
 * Autor:           Pawe� D�bal (pdabal@wat.edu.pl)
 * Student:         Imi� Nazwisko
 * Nr albumu:       00000
 * Przeznaczenie:   Funkcja wej�cia dla programu
 */

#include "stdio.h"
#include "csl.h"

#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_aic23.h"

DSK6713_AIC23_CodecHandle hAIC23;                                   // Uchwyt do sterownika kodeka
DSK6713_AIC23_Config AIC23_regs_cfg = DSK6713_AIC23_DEFAULTCONFIG;  // Domy�lna konfiguracja kodeka

int main(void)
{
    Uint32  sample;

    CSL_init();
    DSK6713_init();
    DSK6713_LED_init();

    printf("Hello World - Procesory DSP.\n");
    printf("Data: %s - %s - ", __DATE__, __TIME__);
    printf("wersja systemu: %d\n", DSK6713_getVersion());

    hAIC23 = DSK6713_AIC23_openCodec(0, &AIC23_regs_cfg);   // Konfiguracja interfejs�w i rejestr�w kodeka
    DSK6713_AIC23_setFreq(hAIC23, DSK6713_AIC23_FREQ_8KHZ); // Ustawienie cz�stotliwo�ci pr�bkowania

    while (1)
    {
        while(DSK6713_AIC23_read(hAIC23, &sample) == 0);    // Odczyt pr�bki odebranej od kodeka
        while(DSK6713_AIC23_write(hAIC23, sample * 2) == 0);// Wys�anie pr�bki do kodeka
        DSK6713_LED_toggle(1);
    }
}

