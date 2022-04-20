/*
 * This example uses a timer to generate interrupt at a specific period.
 *
 * Bazowa czêstotliwoœæ taktowania licznika to CPU/4 (225 MHZ / 4 => 56,25 MHz).
 * The timers have two signaling modes and can be clocked by an internal or an external source.
 * The timers have an input pin and an output pin.
 * The input and output pins (TINP and TOUT) can function as timer clock input and clock output.
 *
 */

#include "pdsp.h"

/*----------------------------------------------------------------------------*/
static TIMER_Handle hTimer0;
static TIMER_Handle hTimer1;

static Uint32 Timer0EventId;
static Uint32 Timer1EventId;

/*----------------------------------------------------------------------*/
/* Konfiguracja Timer0 - generacja odcinak czasu 1s */
TIMER_Config cfgTimer0 = { /* Timer Control Register (CTL) */
    TIMER_FMKS(CTL, CLKSRC, CPUOVR4) | /* Timer input clock source (CLKSRC) - CPU clock /4 */
    TIMER_FMKS(CTL, CP, PULSE) | /* Clock/pulse mode enable bit (CP) - pulse mode */
    TIMER_FMKS(CTL, PWID, ONE) | /* Pulse width bit (PWID) only used in pulse mode (CP = 0) - */
    TIMER_FMKS(CTL, FUNC, GPIO), /* Function of TOUT pin (FUNC) - TOUT is a general-purpose output pin */
    0x00000000, /* Period Register  (PRD) */ // 225 MHZ / 4 => 56,250 MHZ / 2 => 28,125 MHz
    0x00000000  /* Counter Register (CNT) */
};

/* Konfiguracja Timer1 - praca ci¹g³a do okreœlenia szybkoœci realizacji kodu */
TIMER_Config cfgTimer1 = { /* Timer Control Register (CTL) */
    TIMER_FMKS(CTL, CLKSRC, CPUOVR4) | /* Timer input clock source (CLKSRC) - CPU clock /4 */
    TIMER_FMKS(CTL, CP, PULSE) | /* Clock/pulse mode enable bit (CP) - pulse mode */
    TIMER_FMKS(CTL, PWID, ONE) | /* Pulse width bit (PWID) only used in pulse mode (CP = 0) - */
    TIMER_FMKS(CTL, FUNC, GPIO), /* Function of TOUT pin (FUNC) - TOUT is a general-purpose output pin */
    0x00000000, /* Period Register  (PRD) */ // 225 MHZ / 4 => 56,250 MHZ / 2 => 28,125 MHz
    0x00000000  /* Counter Register (CNT) */
};

/*----------------------------------------------------------------------*/
/* Funkcja inicjuj¹ca Timer0 -  */
void PDSP_TIMER0_Init(Uint32 Period)
{
    cfgTimer0.prd = Period - 1;
    /* Open TIMER0 device, and reset them to power-on default state */
    hTimer0 = TIMER_open(TIMER_DEV0, TIMER_OPEN_RESET);
    TIMER_reset(hTimer0);
    TIMER_config(hTimer0, &cfgTimer0);

#ifdef PDSP_TIMER0_INT
    Timer0EventId = TIMER_getEventId(hTimer0); /* Obtain the event ID for the timer device */

    IRQ_map(Timer0EventId, 14); /* Map TIMER events to physical interrupt number */
    IRQ_reset(Timer0EventId); /* Reset the timer events */
    IRQ_enable(Timer0EventId); /* Enable the timer events(events are disabled while resetting) */
#endif
    TIMER_start(hTimer0); /* Start the timers */
}

/*----------------------------------------------------------------------*/
void PDSP_TIMER1_Init(Uint32 Period)
{
    cfgTimer1.prd = Period - 1;
    /* Open TIMER1 device, and reset them to power-on default state */
    hTimer1 = TIMER_open(TIMER_DEV1, TIMER_OPEN_RESET);
    TIMER_reset(hTimer1);
    TIMER_config(hTimer1, &cfgTimer1);

#ifdef PDSP_TIMER1_INT
    Timer1EventId = TIMER_getEventId(hTimer1); /* Obtain the event ID for the timer device */

    IRQ_map(Timer1EventId, 15); /* Map TIMER events to physical interrupt number */
    IRQ_reset(Timer1EventId); /* Reset the timer events */
    IRQ_enable(Timer1EventId); /* Enable the timer events(events are disabled while resetting) */
#endif						
    TIMER_start(hTimer1); /* Start the timers */
}

void PDSP_TIMER_Init(){
    PDSP_TIMER0_Init(PDSP_TIMER0_PERIOD);                          /* Initialize TIMER0 interupt */
    PDSP_TIMER1_Init(PDSP_TIMER1_PERIOD);                          /* Initialize TIMER1 interupt */
}
