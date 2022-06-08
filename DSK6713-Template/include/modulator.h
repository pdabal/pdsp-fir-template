/*
 * modulator.h
 *
 *  Created on: 18 maj 2022
 *      Author: pdabal
 */

#ifndef INCLUDE_MODULATOR_H_
#define INCLUDE_MODULATOR_H_

typedef struct
{
    float parameter;        // Modulation index (0..1)
    float carrierAmplitude; // Amplitude of carrier signal
    float carrierFrequency; // Frequency of carrier signal
} MOD_AM_Config_st;

typedef struct
{
    float parameter;
    GEN_Handle_st oscCarrier;
} MOD_AM_Handle_st;

typedef struct
{
    float parameter;        // Modulation index (0..1)
    float carrierAmplitude; // Amplitude of carrier signal
    float carrierFrequency; // Frequency of carrier signal
} MOD_PM_Config_st;

typedef struct
{
    float parameter;
    GEN_Handle_st oscCarrier;
} MOD_PM_Handle_st;

typedef struct
{
    float parameter;        // Modulation index (0..1)
    float carrierAmplitude; // Amplitude of carrier signal
    float carrierFrequency; // Frequency of carrier signal
} MOD_FM_Config_st;

typedef struct
{
    float parameter;
    GEN_Handle_st oscCarrier;
} MOD_FM_Handle_st;

void MOD_AM_Init(MOD_AM_Handle_st *pHandle, MOD_AM_Config_st config);
float MOD_AM_GetValue(MOD_AM_Handle_st *pHandle, float messageSample);

void MOD_PM_Init(MOD_PM_Handle_st * pHandle, MOD_PM_Config_st config);
float MOD_PM_GetValue(MOD_PM_Handle_st * pHandle, float messageSample);

void MOD_FM_Init(MOD_FM_Handle_st * pHandle, MOD_FM_Config_st config);
float MOD_FM_GetValue(MOD_FM_Handle_st * pHandle, float messageSample);

typedef struct{
    uint32_t symbolLengthInPeriod;
    uint32_t symbolLengthInBits;
    float carrierAmplitude; // Amplitude of carrier signal
    float carrierFrequency; // Frequency of carrier signal
    float parameter;
} MOD_DIGITAL_Config_st;

typedef struct {
    uint32_t symbolLengthInBits;
    uint32_t symbolLengthInSample;
    uint32_t symbolSampleCnt;
    float amplitudeValue[256];
    GEN_Handle_st oscCarrier;
} MOD_DIGITAL_ASK_Handle_st;

typedef struct{
    uint32_t symbolLengthInBits;
    uint32_t symbolLengthInSample;
    uint32_t symbolSampleCnt;
    float phaseValue[256];    
    GEN_Handle_st oscCarrier;

} MOD_DIGITAL_PSK_Handle_st;

typedef struct{
    uint32_t symbolLengthInBits;
    uint32_t symbolLengthInSample;
    uint32_t symbolSampleCnt;
    float freqValue[256];
    float bandwidth;
    GEN_Handle_st oscCarrier;
} MOD_DIGITAL_FSK_Handle_st;


void MOD_DIGITAL_ASK_Init(MOD_DIGITAL_ASK_Handle_st * pHandle, MOD_DIGITAL_Config_st config);
float MOD_DIGITAL_ASK_GetValue(MOD_DIGITAL_ASK_Handle_st * pHandle, uint8_t symbol);

void MOD_DIGITAL_PSK_Init(MOD_DIGITAL_PSK_Handle_st * pHandle, MOD_DIGITAL_Config_st config);
float MOD_DIGITAL_PSK_GetValue(MOD_DIGITAL_PSK_Handle_st * pHandle, uint8_t symbol);

void MOD_DIGITAL_FSK_Init(MOD_DIGITAL_FSK_Handle_st * pHandle, MOD_DIGITAL_Config_st config);
float MOD_DIGITAL_FSK_GetValue(MOD_DIGITAL_FSK_Handle_st * pHandle, uint8_t symbol);

#endif /* INCLUDE_MODULATOR_H_ */
