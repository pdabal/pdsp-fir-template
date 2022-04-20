/*
 * pdsp_types.h
 *
 *  Created on: 10 mar 2021
 *      Author: pdabal
 */

#ifndef INCLUDE_PDSP_PDSP_TYPES_H_
#define INCLUDE_PDSP_PDSP_TYPES_H_

typedef enum
{
    LP, HP, BP, BS, MA, MBP, MBS
} FIR_t;

/* */
typedef enum
{
    PDSP_AIC_LineInput,
    PDSP_AIC_MicInput_0db,
    PDSP_AIC_MicInput_20db
} PDSP_AIC_INPUT_t;

/* */
typedef enum
{
    PDSP_LED0 = 1,
    PDSP_LED1 = 2,
    PDSP_LED2 = 4,
    PDSP_LED3 = 8,
    PDSP_LED_MASK = 15
} PDSP_LED_t;

typedef enum
{
    PDSP_DIP0 = 1,
    PDSP_DIP1 = 2,
    PDSP_DIP2 = 4,
    PDSP_DIP3 = 8,
    PDSP_DIP_MASK = 15
} PDSP_DIP_t;

#endif /* INCLUDE_PDSP_PDSP_TYPES_H_ */
