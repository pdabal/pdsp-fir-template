/*
 * pdsp.c
 *
 *  Created on: 12 lis 2018
 *      Author: pdabal
 */
#include "pdsp.h"
#include "pdsp_timer.h"

/* Konfiguracja interfsejsu steruj¹cego I2C do kodeka AIC23 */
MCBSP_Config mcbspCfgControl = {
    MCBSP_FMKS(SPCR, FREE, NO)          | MCBSP_FMKS(SPCR, SOFT, NO)        | MCBSP_FMKS(SPCR, FRST, YES)
  | MCBSP_FMKS(SPCR, GRST, YES)         | MCBSP_FMKS(SPCR, XINTM, XRDY)     | MCBSP_FMKS(SPCR, XSYNCERR, NO)
  | MCBSP_FMKS(SPCR, XRST, YES)         | MCBSP_FMKS(SPCR, DLB, OFF)        | MCBSP_FMKS(SPCR, RJUST, RZF)
  | MCBSP_FMKS(SPCR, CLKSTP, NODELAY)   | MCBSP_FMKS(SPCR, DXENA, OFF)      | MCBSP_FMKS(SPCR, RINTM, RRDY)
  | MCBSP_FMKS(SPCR, RSYNCERR, NO)      | MCBSP_FMKS(SPCR, RRST, YES),

    MCBSP_FMKS(RCR, RPHASE, DEFAULT)    | MCBSP_FMKS(RCR, RFRLEN2, DEFAULT) | MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)
  | MCBSP_FMKS(RCR, RCOMPAND, DEFAULT)  | MCBSP_FMKS(RCR, RFIG, DEFAULT)    | MCBSP_FMKS(RCR, RDATDLY, DEFAULT)
  | MCBSP_FMKS(RCR, RFRLEN1, DEFAULT)   | MCBSP_FMKS(RCR, RWDLEN1, DEFAULT) | MCBSP_FMKS(RCR, RWDREVRS, DEFAULT),
    MCBSP_FMKS(XCR, XPHASE, SINGLE)     | MCBSP_FMKS(XCR, XFRLEN2, OF(0))   | MCBSP_FMKS(XCR, XWDLEN2, 8BIT)
  | MCBSP_FMKS(XCR, XCOMPAND, MSB)      | MCBSP_FMKS(XCR, XFIG, NO)         | MCBSP_FMKS(XCR, XDATDLY, 1BIT)
  | MCBSP_FMKS(XCR, XFRLEN1, OF(0))     | MCBSP_FMKS(XCR, XWDLEN1, 16BIT)   | MCBSP_FMKS(XCR, XWDREVRS, DISABLE),
    MCBSP_FMKS(SRGR, GSYNC, FREE)       | MCBSP_FMKS(SRGR, CLKSP, RISING)   | MCBSP_FMKS(SRGR, CLKSM, INTERNAL)
  | MCBSP_FMKS(SRGR, FSGM, DXR2XSR)     | MCBSP_FMKS(SRGR, FPER, OF(0))     | MCBSP_FMKS(SRGR, FWID, OF(19))
  | MCBSP_FMKS(SRGR, CLKGDV, OF(99)),
    MCBSP_MCR_DEFAULT,                    MCBSP_RCER_DEFAULT,                 MCBSP_XCER_DEFAULT,
    MCBSP_FMKS(PCR, XIOEN, SP)          | MCBSP_FMKS(PCR, RIOEN, SP)        | MCBSP_FMKS(PCR, FSXM, INTERNAL)
  | MCBSP_FMKS(PCR, FSRM, EXTERNAL)     | MCBSP_FMKS(PCR, CLKXM, OUTPUT)    | MCBSP_FMKS(PCR, CLKRM, INPUT)
  | MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)  | MCBSP_FMKS(PCR, DXSTAT, DEFAULT)  | MCBSP_FMKS(PCR, FSXP, ACTIVELOW)
  | MCBSP_FMKS(PCR, FSRP, DEFAULT)      | MCBSP_FMKS(PCR, CLKXP, FALLING)   | MCBSP_FMKS(PCR, CLKRP, DEFAULT)
};

/* Konfiguracja interfsejsu danych I2S do kodeka AIC23 */
MCBSP_Config mcbspCfgData = {
    MCBSP_FMKS(SPCR, FREE, NO)          | MCBSP_FMKS(SPCR, SOFT, NO)        | MCBSP_FMKS(SPCR, FRST, YES)
  | MCBSP_FMKS(SPCR, GRST, YES)         | MCBSP_FMKS(SPCR, XINTM, XRDY)     | MCBSP_FMKS(SPCR, XSYNCERR, NO)
  | MCBSP_FMKS(SPCR, XRST, YES)         | MCBSP_FMKS(SPCR, DLB, OFF)        | MCBSP_FMKS(SPCR, RJUST, RZF)
  | MCBSP_FMKS(SPCR, CLKSTP, DISABLE)   | MCBSP_FMKS(SPCR, DXENA, OFF)      | MCBSP_FMKS(SPCR, RINTM, RRDY)
  | MCBSP_FMKS(SPCR, RSYNCERR, NO)      | MCBSP_FMKS(SPCR, RRST, YES),

    MCBSP_FMKS(RCR, RPHASE, SINGLE)     | MCBSP_FMKS(RCR, RFRLEN2, DEFAULT) | MCBSP_FMKS(RCR, RWDLEN2, DEFAULT)
  | MCBSP_FMKS(RCR, RCOMPAND, MSB)      | MCBSP_FMKS(RCR, RFIG, NO)         | MCBSP_FMKS(RCR, RDATDLY, 0BIT)
  | MCBSP_FMKS(RCR, RFRLEN1, OF(0))     | MCBSP_FMKS(RCR, RWDLEN1, 32BIT)   | MCBSP_FMKS(RCR, RWDREVRS, DISABLE),

    MCBSP_FMKS(XCR, XPHASE, SINGLE)     | MCBSP_FMKS(XCR, XFRLEN2, DEFAULT) | MCBSP_FMKS(XCR, XWDLEN2, DEFAULT)
  | MCBSP_FMKS(XCR, XCOMPAND, MSB)      | MCBSP_FMKS(XCR, XFIG, NO)         | MCBSP_FMKS(XCR, XDATDLY, 0BIT)
  | MCBSP_FMKS(XCR, XFRLEN1, OF(0))     | MCBSP_FMKS(XCR, XWDLEN1, 32BIT)   | MCBSP_FMKS(XCR, XWDREVRS, DISABLE),

    MCBSP_FMKS(SRGR, GSYNC, DEFAULT)    | MCBSP_FMKS(SRGR, CLKSP, DEFAULT)  | MCBSP_FMKS(SRGR, CLKSM, DEFAULT)
  | MCBSP_FMKS(SRGR, FSGM, DEFAULT)     | MCBSP_FMKS(SRGR, FPER, DEFAULT)   | MCBSP_FMKS(SRGR, FWID, DEFAULT)
  | MCBSP_FMKS(SRGR, CLKGDV, DEFAULT),

    MCBSP_MCR_DEFAULT,                    MCBSP_RCER_DEFAULT,                 MCBSP_XCER_DEFAULT,

    MCBSP_FMKS(PCR, XIOEN, SP)          | MCBSP_FMKS(PCR, RIOEN, SP)        | MCBSP_FMKS(PCR, FSXM, EXTERNAL)
  | MCBSP_FMKS(PCR, FSRM, EXTERNAL)     | MCBSP_FMKS(PCR, CLKXM, INPUT)     | MCBSP_FMKS(PCR, CLKRM, INPUT)
  | MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT)  | MCBSP_FMKS(PCR, DXSTAT, DEFAULT)  | MCBSP_FMKS(PCR, FSXP, ACTIVEHIGH)
  | MCBSP_FMKS(PCR, FSRP, ACTIVEHIGH)   | MCBSP_FMKS(PCR, CLKXP, FALLING)   | MCBSP_FMKS(PCR, CLKRP, RISING)
};

/* Konfiguracja rejestrów kodeka AIC23 */
DSK6713_AIC23_Config AIC23_regs_cfg = {
    0x001B, /* Set-Up Reg 0       Left line input channel volume control */
            /* LRS     0          simultaneous left/right volume: disabled */
            /* LIM     0          left line input mute: disabled */
            /* XX      00         reserved */
            /* LIV     11011      left line input volume: 7.5 dB - korekta spadku amplitudy na dzielniku wejœciowym */
    0x001B, /* Set-Up Reg 1       Right line input channel volume control */
            /* RLS     0          simultaneous right/left volume: disabled */
            /* RIM     0          right line input mute: disabled */
            /* XX      00         reserved */
            /* RIV     11011      right line input volume: 7.5 dB - korekta spadku amplitudy na dzielniku wejœciowym */
    0x00d8, /* Set-Up Reg 2       Left channel headphone volume control */
            /* LRS     0          simultaneous left/right volume: enabled */
            /* LZC     1          left channel zero-cross detect: enabled */
            /* LHV     1011000    left headphone volume: 0 dB */
    0x00d8, /* Set-Up Reg 3       Right channel headphone volume control */
            /* RLS     0          simultaneous right/left volume: enabled */
            /* RZC     1          right channel zero-cross detect: enabled */
            /* RHV     1011000    right headphone volume: 0 dB */
    0x0012, /* Set-Up Reg 4       Analog audio path control */
            /* X       0          reserved */
            /* STA     00         sidetone attenuation: -6 dB */
            /* STE     0          sidetone: disabled */
            /* DAC     1          DAC: selected */
            /* BYP     0          bypass: off */
            /* INSEL   0          input select for ADC: line */
            /* MICM    1          microphone mute: enabled */
            /* MICB    0          microphone boost: disabled */
    0x0000, /* Set-Up Reg 5       Digital audio path control */
            /* XXXXX   00000      reserved */
            /* DACM    0          DAC soft mute: disabled */
            /* DEEMP   00         deemphasis control: disabled */
            /* ADCHP   0          ADC high-pass filter: disabled */
    0x0000, /* Set-Up Reg 6       Power down control */
            /* X       0          reserved */
            /* OFF     0          device power: on (i.e. not off) */
            /* CLK     0          clock: on */
            /* OSC     0          oscillator: on */
            /* OUT     0          outputs: on */
            /* DAC     0          DAC: on */
            /* ADC     0          ADC: on */
            /* MIC     0          microphone: on */
            /* LINE    0          line input: on */
    0x0043, /* Set-Up Reg 7       Digital audio interface format */
            /* XX      00         reserved */
            /* MS      1          master/slave mode: master */
            /* LRSWAP  0          DAC left/right swap: disabled */
            /* LRP     0          DAC lrp: MSB on 1st BCLK */
            /* IWL     00         input bit length: 16 bit */
            /* FOR     11         data format: DSP format */
    0x0081, /* Set-Up Reg 8       Sample rate control */
            /* X       0          reserved */
            /* CLKOUT  1          clock output divider: 2 (MCLK/2) */
            /* CLKIN   0          clock input divider: 2 (MCLK/2) */
            /* SR,BOSR 00000      sampling rate: ADC  48 kHz DAC  48 kHz */
            /* USB/N   1          clock mode select (USB/normal): USB */
    0x0001  /* Set-Up Reg 9       Digital interface activation */
            /* XX..X   00000000   reserved */
            /* ACT     1          active */
};

Uint32  IRQ_EventId_AIC23;

/*  */
void PDSP_Init(){
    CSL_init();                         /* Inicjalizacja bliblioteki Chip Support Library */
    DSK6713_init();                     /* Inicjalizacja bliblioteki Board Support Library */
    DSK6713_LED_init();                 /* Inicjalizacja modulu LED */
    DSK6713_DIP_init();                 /* Inicjalizacja modulu DIP */
    IRQ_globalDisable();                /* Wy³¹czenie obs³ugi przerwañ */

    /* Informacja o kompilacji */
    printf("Procesory DSP - %s - %s - wersja systemu - %d\n", __DATE__, __TIME__, DSK6713_getVersion());
}

/* */
void PDSP_CODEC_Init()
{
    /* Interfejs McBSP do konfiguracji rejestrów kodeka, pracujacych w trybie I2C */
    DSK6713_AIC23_CONTROLHANDLE = MCBSP_open(MCBSP_DEV0, MCBSP_OPEN_RESET);
    if (DSK6713_AIC23_CONTROLHANDLE == INV)
        return;

    /* Interfejs McBSP do wymiany danych z kodekiem, pracuj¹cy w trybie TI DSP */
    DSK6713_AIC23_DATAHANDLE = MCBSP_open(MCBSP_DEV1, MCBSP_OPEN_RESET);
    if (DSK6713_AIC23_DATAHANDLE == INV)
        return;

    /* Configure codec control McBSP */
    MCBSP_config(DSK6713_AIC23_CONTROLHANDLE, &mcbspCfgControl);

    /* Configure codec data McBSP */
    MCBSP_config(DSK6713_AIC23_DATAHANDLE, &mcbspCfgData);

    /* Uruchomienie interfejsu McBSP1 - dostêp do rejestrów kodeka */
    MCBSP_start(DSK6713_AIC23_CONTROLHANDLE, MCBSP_XMIT_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);

    /* Reset the AIC23 */
    DSK6713_AIC23_rset(0, DSK6713_AIC23_RESET, 0);

    /* Konfiguracja wejœcia kodeka */
    switch(PDSP_AIC_INPUT) {
        case PDSP_AIC_LineInput:
            AIC23_regs_cfg.regs[4] = 0x0012;        // Analog audio path (DAC on, line-in input, 0db)
            break;
        case PDSP_AIC_MicInput_0db:
            AIC23_regs_cfg.regs[4] = 0x0014;        // Analog audio path (DAC on, mic input, 0db)
            break;
        case PDSP_AIC_MicInput_20db:
            AIC23_regs_cfg.regs[4] = 0x0015;        // Analog audio path (DAC on, mic input, +20db)
            break;
    }

    /* Configure the rest of the AIC23 registers */
    DSK6713_AIC23_config(0, &AIC23_regs_cfg);

    /* Ustawienie czêstotliwoœci próbkowania */
    DSK6713_AIC23_setFreq(0, PDSP_FS_AIC23);

    /* Clear any garbage from the codec data port */
    if (MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE))
        MCBSP_read(DSK6713_AIC23_DATAHANDLE);

    /* Uruchomienie interfejsu McBSP2 - dla transmisji danych*/
    MCBSP_start(DSK6713_AIC23_DATAHANDLE, MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);

#if PDSP_MODE == PDSP_MODE_INT
    /* Konfiguracja przerwania dla interfejsu McBSP1 */
    IRQ_EventId_AIC23 = MCBSP_getXmtEventId(DSK6713_AIC23_DATAHANDLE);
    IRQ_map (IRQ_EventId_AIC23, 11);    // Konfiguracja przerwania od interfejsu McBSP1 XMIT do lini INT11
    IRQ_reset (IRQ_EventId_AIC23);      // Skasowanie przerwania od interfejsu McBSP1
    IRQ_enable (IRQ_EventId_AIC23);     // W³¹czenie przerwania

    MCBSP_write(DSK6713_AIC23_DATAHANDLE, 0);
#endif
}

void PDSP_INT_Init(void){
    /* Konfiguracja globalna przerwañ */
    IRQ_setVecs (vectors);              // Konfiguracja wektora przerwañ
    IRQ_nmiEnable ();                   // W³¹czenie przerwania NMI
    IRQ_globalEnable();                 // Globalne w³¹czenie przerwañ
}

//-----------------------------------------------------------------------------
uint32_t PDSP_GetValue(){
#if PDSP_MODE == PDSP_MODE_POLL
    while (!MCBSP_rrdy(DSK6713_AIC23_DATAHANDLE));
#endif
    return MCBSP_read(DSK6713_AIC23_DATAHANDLE);
}

void PDSP_SetValue(CODEC_Data value){
#if PDSP_MODE == PDSP_MODE_POLL
    while(!MCBSP_xrdy(DSK6713_AIC23_DATAHANDLE));                   // If ready to transmit
#endif
    MCBSP_write(DSK6713_AIC23_DATAHANDLE, value.uint);              // Output right channel
}

//-----------------------------------------------------------------------------
uint8_t PDSP_DIP_getValue(void)
{
    return (DSK6713_rget(DSK6713_USER_REG) >> 4);
}
/* */
void  PDSP_LED_setValue(uint8_t bin)
{
    DSK6713_rset(DSK6713_USER_REG, (0x0F & bin));
}


