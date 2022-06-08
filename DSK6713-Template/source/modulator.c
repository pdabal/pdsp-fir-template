/*
 * modulator.c
 *
 *  Created on: 18 maj 2022
 *      Author: pdabal
 */


#include "pdsp.h"
#include "generator_arbitralny.h"
#include "modulator.h"

void MOD_AM_Init(MOD_AM_Handle_st * pHandle, MOD_AM_Config_st config){
    config.parameter = fabsf(config.parameter);
    pHandle->parameter = (config.parameter < 1.0f) ? config.parameter : 1.0f;
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_AM_GetValue(MOD_AM_Handle_st * pHandle, float messageSample){
    float carrierValue = GEN_GetValue(&pHandle->oscCarrier);
    float modulatorValue = (1 + pHandle->parameter * messageSample);
    float modulatorSample = carrierValue * modulatorValue;
    return modulatorSample;
}

void MOD_PM_Init(MOD_PM_Handle_st * pHandle, MOD_PM_Config_st config){
    config.parameter = fabsf(config.parameter);
    pHandle->parameter = (config.parameter < PDSP_2PI) ? config.parameter : PDSP_2PI;
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_PM_GetValue(MOD_PM_Handle_st * pHandle, float messageSample){
    ACU_SetPhaseOffset(&pHandle->oscCarrier.acu, pHandle->parameter * messageSample);
    float modulatorSample = GEN_GetValue(&pHandle->oscCarrier);
    return modulatorSample;
}

void MOD_FM_Init(MOD_FM_Handle_st * pHandle, MOD_FM_Config_st config){
    config.parameter = fabsf(config.parameter);
    pHandle->parameter = (config.parameter < (CODEC_fs / 4)) ? config.parameter : (CODEC_fs / 4);
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_FM_GetValue(MOD_FM_Handle_st * pHandle, float messageSample){
    float modulatedFreq = pHandle->parameter * messageSample;
    float modulatedPhase = modulatedFreq * PDSP_2PI_DIV_FS;
    ACU_AddPhase(&pHandle->oscCarrier.acu, modulatedPhase);
    float modulatorSample = GEN_GetValue(&pHandle->oscCarrier);
    return modulatorSample;
}

void MOD_DIGITAL_ASK_Init(MOD_DIGITAL_ASK_Handle_st * pHandle, MOD_DIGITAL_Config_st config){    
    config.symbolLengthInPeriod = (config.symbolLengthInPeriod < 256) ? config.symbolLengthInPeriod : 1;
    pHandle->symbolLengthInBits = ((config.symbolLengthInBits > 0) && (config.symbolLengthInBits <= 8)) ? config.symbolLengthInBits : 1;
    pHandle->symbolLengthInSample = config.symbolLengthInPeriod * (CODEC_fs / config.carrierFrequency);
    pHandle->symbolSampleCnt = 0;
    uint32_t amplitudeNumber = powf(2, config.symbolLengthInBits);
    float amplitudeDelta = 1.0f / (float)amplitudeNumber;
    float amplitude = 0.0f;
    Uint32 i;
    for(i = 0; i < amplitudeNumber; i++){
        amplitude += amplitudeDelta;
        pHandle->amplitudeValue[i] = amplitude;    
    }
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_DIGITAL_ASK_GetValue(MOD_DIGITAL_ASK_Handle_st * pHandle, uint8_t symbol){
    uint8_t shift = (8 - pHandle->symbolLengthInBits);
            shift = (0xFF >> shift);
    symbol &= shift;
    float carrierValue = GEN_GetValue(&pHandle->oscCarrier);
    float modulatorValue = pHandle->amplitudeValue[symbol];
    float modulatorSample = carrierValue * modulatorValue;
    pHandle->symbolSampleCnt++;

    return modulatorSample;
}

void MOD_DIGITAL_PSK_Init(MOD_DIGITAL_PSK_Handle_st * pHandle, MOD_DIGITAL_Config_st config){
    config.symbolLengthInPeriod = (config.symbolLengthInPeriod < 256) ? config.symbolLengthInPeriod : 1;
    pHandle->symbolLengthInBits = ((config.symbolLengthInBits > 0) && (config.symbolLengthInBits <= 8)) ? config.symbolLengthInBits : 1;
    pHandle->symbolLengthInSample = config.symbolLengthInPeriod * (CODEC_fs / config.carrierFrequency);
    pHandle->symbolSampleCnt = 0;
    uint32_t phaseNumber = powf(2, config.symbolLengthInBits);
    float phaseDelta = PDSP_2PI / (float)phaseNumber;
    float phase = 0.0f;
    Uint32 i;
    for(i = 0; i < phaseNumber; i++){
        pHandle->phaseValue[i] = phase;
        phase += phaseDelta;
    }
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_DIGITAL_PSK_GetValue(MOD_DIGITAL_PSK_Handle_st * pHandle, uint8_t symbol){
    uint8_t shift = (8 - pHandle->symbolLengthInBits);
            shift = (0xFF >> shift);
    symbol &= shift;
    ACU_SetPhaseOffset(&pHandle->oscCarrier.acu, pHandle->phaseValue[symbol]);
    float carrierValue = GEN_GetValue(&pHandle->oscCarrier);
    pHandle->symbolSampleCnt++;

    return carrierValue;
}

void MOD_DIGITAL_FSK_Init(MOD_DIGITAL_FSK_Handle_st * pHandle, MOD_DIGITAL_Config_st config){
    config.symbolLengthInPeriod = (config.symbolLengthInPeriod < 256) ? config.symbolLengthInPeriod : 1;
    config.parameter = (config.parameter < (CODEC_fs / 4)) ? config.parameter : (CODEC_fs / 4);
    pHandle->symbolLengthInBits = ((config.symbolLengthInBits > 0) && (config.symbolLengthInBits <= 8)) ? config.symbolLengthInBits : 1;
    pHandle->symbolLengthInSample = config.symbolLengthInPeriod * (CODEC_fs / config.carrierFrequency);
    pHandle->symbolSampleCnt = 0;
    pHandle->bandwidth = config.parameter;
    uint32_t freqNumber = powf(2, config.symbolLengthInBits);
    float freqDelta = ((pHandle->bandwidth) / (float)freqNumber);
    float freq = 0.0f;
    Uint32 i;
    for(i = 0; i < freqNumber; i++){
        pHandle->freqValue[i] = freq + (config.carrierFrequency - (pHandle->bandwidth / 2));
        freq += freqDelta;
    }
    GEN_InitSin(&pHandle->oscCarrier, config.carrierAmplitude, config.carrierFrequency);
}

float MOD_DIGITAL_FSK_GetValue(MOD_DIGITAL_FSK_Handle_st * pHandle, uint8_t symbol){
    uint8_t shift = (8 - pHandle->symbolLengthInBits);
            shift = (0xFF >> shift);
    symbol &= shift;
    float modulatedPhase = pHandle->freqValue[symbol] * PDSP_2PI_DIV_FS;
    ACU_AddPhase(&pHandle->oscCarrier.acu, modulatedPhase);
    float carrierValue = GEN_GetValue(&pHandle->oscCarrier);
    pHandle->symbolSampleCnt++;

    return carrierValue;
}
