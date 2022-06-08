/*
 * generator_arbitralny.h
 *
 *  Created on: 6 maj 2022
 *      Author: pdabal
 */

#ifndef INCLUDE_GENERATOR_ARBITRALNY_H_
#define INCLUDE_GENERATOR_ARBITRALNY_H_

typedef struct
{
    float frequency;
    float phaseOffset;
} ACU_Config_st;

typedef struct
{
    float phase;
    float phaseStep;
    float phaseOffset;
} ACU_Handle_st;

typedef enum
{
    GEN_Shape_Sin,
    GEN_Shape_Square,
    GEN_Shape_Sawtooth,
    GEN_Shape_Triangle,
    GEN_Shape_Pulse,
    GEN_Shape_Noise,
    GEN_Shape_NoiseNormal
} GEN_Shape_et;

typedef struct
{
    float amplitude;
    float amplitudeOffset;
    float duty;
    float frequency;
    float phaseOffset;
    GEN_Shape_et shape;
} GEN_Config_st;

typedef struct
{
    GEN_Shape_et shape;
    float amplitude;
    float amplitudeOffset;
    float duty;
    ACU_Handle_st acu;
} GEN_Handle_st;

//--

typedef struct
{
    bool init;
    long seed;
    float start;
    float stop;
    uint32_t a;
    uint32_t m;
    uint32_t q;
    uint32_t r;
} GEN_NOISE_UniformHandle_st;

typedef struct
{
    int32_t call;
    float X1;
    float X2;
    float mean;
    float stdDeviation;
} GEN_NOISE_NormalHandle_st;

typedef struct
{
    uint32_t value;
    uint32_t key;
    uint8_t length;
} GEN_NOISE_GaloisHandle_st;

typedef struct {
    uint32_t sampleCycle;
    uint32_t sampleCycleLeft;
    uint32_t samplePeriod;
    uint32_t samplePeriodLeft;
    float phaseOffset;
    GEN_Handle_st * generator;
} GEN_BURST_Handle_st;

typedef enum {SWEEP_MODE_LINEAR, SWEEP_MODE_LOG} SWEEP_MODE_t;

typedef struct {
    float duration;
    SWEEP_MODE_t mode;
    float phaseStep;
    float phaseStepStart;
    float phaseStepStop;
    float phaseInc;
    GEN_Handle_st * generator;
} GEN_SWEEP_Handle_st;
//--
void ACU_Init(ACU_Handle_st * pHandle, ACU_Config_st * pConfig);
float ACU_GetValue(ACU_Handle_st * pHandle);
float ACU_GetValueNorm(ACU_Handle_st * pHandle);
uint32_t ACU_GetValueMiliDegree(ACU_Handle_st * pHandle);
void ACU_AddPhase(ACU_Handle_st * pHandle, float phase);
void ACU_SetPhaseOffset(ACU_Handle_st *pHandle, float phaseOffset);

void GEN_Init(GEN_Handle_st * pHandle, GEN_Config_st * pConfig);

void GEN_InitSin(GEN_Handle_st * pHandle, float carrierAmplitude, float carrierFrequency);

float GEN_GetValue(GEN_Handle_st * pHandle);

void GEN_NOISE_InitUniform(GEN_NOISE_UniformHandle_st *hRandUni, long seed, float start,
                    float stop);
float GEN_NOISE_GetValueUniform(GEN_NOISE_UniformHandle_st *hCfg);

void GEN_NOISE_InitNormal(GEN_NOISE_NormalHandle_st *hCfg, float mean, float sigma);
float GEN_NOISE_GetValueNormal(GEN_NOISE_NormalHandle_st *hCfg);


void GEN_SWEEP_Init(GEN_SWEEP_Handle_st *hCfg, GEN_Handle_st *hGen, float freqStart, float freqStop, float duration, SWEEP_MODE_t mode);
float GEN_SWEEP_GetValue(GEN_SWEEP_Handle_st *hSweep);

void GEN_NOISE_InitGalois(GEN_NOISE_GaloisHandle_st *hRandLfsr, uint32_t seed, uint32_t key,
                      uint8_t length);
uint32_t GEN_NOISE_GetValueGalois(GEN_NOISE_GaloisHandle_st *hRandLfsr);

void GEN_BURST_Init(GEN_BURST_Handle_st *hCfg, GEN_Handle_st *hGen,
                    uint16_t nCycles, float burstPeriod, float phaseOffset);
float GEN_BURST_GetValue(GEN_BURST_Handle_st *hCfg);



#endif /* INCLUDE_GENERATOR_ARBITRALNY_H_ */
