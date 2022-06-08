/*
 * generator_arbitralny.c
 *
 *  Created on: 6 maj 2022
 *      Author: pdabal
 */

#include "pdsp.h"
#include "generator_arbitralny.h"

float AWGN_generator(void);

void ACU_Init(ACU_Handle_st *pHandle, ACU_Config_st *pConfig)
{
    pConfig->frequency = fabsf(pConfig->frequency);
    pConfig->frequency = (pConfig->frequency < (CODEC_fs / 2.0f)) ? pConfig->frequency : (CODEC_fs / 2.0f);
    pConfig->phaseOffset = (fabsf(pConfig->phaseOffset) < PDSP_2PI) ? pConfig->phaseOffset : PDSP_2PI;
    pConfig->phaseOffset = (pConfig->phaseOffset >= 0.0f) ? pConfig->phaseOffset : (PDSP_2PI + pConfig->phaseOffset);
    pHandle->phaseOffset = pConfig->phaseOffset;
    pHandle->phaseStep = (pConfig->frequency * PDSP_2PI_DIV_FS);
    pHandle->phase = -pHandle->phaseStep;

}

float ACU_GetValue(ACU_Handle_st *pHandle)
{
    float phase;
    pHandle->phase += pHandle->phaseStep;
    pHandle->phase =
        (pHandle->phase > PDSP_2PI) ? (pHandle->phase - PDSP_2PI) : pHandle->phase;

    phase = pHandle->phase + pHandle->phaseOffset;
    return phase;
}

float ACU_GetValueNorm(ACU_Handle_st *pHandle)
{
    float phase = ACU_GetValue(pHandle);
    float phaseNorm = (phase / PDSP_2PI);

    return phaseNorm;
}

uint32_t ACU_GetValueMiliDegree(ACU_Handle_st *pHandle)
{
    float phase = ACU_GetValue(pHandle);
    uint32_t phaseDegree = (uint32_t)((phase / (180.0f / PDSP_PI)) * 1000.0f);

    return phaseDegree;
}

void ACU_AddPhase(ACU_Handle_st *pHandle, float phase)
{
    pHandle->phase += phase;
    pHandle->phase =
        (pHandle->phase > PDSP_2PI) ? (pHandle->phase - PDSP_2PI) : pHandle->phase;
}

void ACU_SetPhaseOffset(ACU_Handle_st *pHandle, float phaseOffset)
{
    pHandle->phaseOffset = (fabsf(phaseOffset) < PDSP_2PI) ? phaseOffset : PDSP_2PI;
    pHandle->phaseOffset = (pHandle->phaseOffset >= 0.0f) ? pHandle->phaseOffset : (PDSP_2PI + pHandle->phaseOffset);
}

void GEN_Init(GEN_Handle_st *pHandle, GEN_Config_st *pConfig)
{
    ACU_Config_st acuConfig;
    acuConfig.frequency = pConfig->frequency;
    acuConfig.phaseOffset = pConfig->phaseOffset;

    ACU_Init(&pHandle->acu, &acuConfig);

    pHandle->shape = pConfig->shape;
    pHandle->amplitude =
        (fabs(pConfig->amplitude) <= CODEC_Vpp) ? pConfig->amplitude : (pConfig->amplitude > 0.0f) ? CODEC_Vpp
                                                                                                   : -CODEC_Vpp;
    pHandle->amplitudeOffset =
        (fabs(pConfig->amplitudeOffset) <= CODEC_Vpp / 2.0f) ? pConfig->amplitudeOffset : (pConfig->amplitudeOffset > 0.0f) ? (CODEC_Vpp / 2.0f)
                                                                                                                            : (-CODEC_Vpp / 2.0f);
    pHandle->duty = fmodf(fabs(pConfig->duty), 100.0f);
}

void GEN_InitSin(GEN_Handle_st *pHandle, float carrierAmplitude, float carrierFrequency)
{
    GEN_Config_st genConfig;
    genConfig.frequency = carrierFrequency;
    genConfig.phaseOffset = 0.0f;
    genConfig.amplitude = carrierAmplitude;
    genConfig.amplitudeOffset = 0.0f;
    genConfig.duty = 50.0f;
    genConfig.shape = GEN_Shape_Sin;

    GEN_Init(pHandle, &genConfig);
}

void GEN_SetFrequency(GEN_Handle_st *pHandle, float frequency)
{
    frequency =
        (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    pHandle->acu.phaseStep = (frequency * PDSP_2PI_DIV_FS);
}

float GEN_GetFrequency(GEN_Handle_st *pHandle)
{
    return pHandle->acu.phaseStep * (CODEC_fs / PDSP_2PI);
}

float GEN_GetValue(GEN_Handle_st *pHandle)
{
    float value;
    float phase = ACU_GetValue(&pHandle->acu);
    float phaseDuty = PDSP_2PI * pHandle->duty / 100.0f;

    switch (pHandle->shape)
    {
    case GEN_Shape_Sin:
        value = sinf(phase) + pHandle->amplitudeOffset;
        break;
    case GEN_Shape_Square:
        value = ((phase < phaseDuty) ? -1.0f : 1.0f) + pHandle->amplitudeOffset;
        break;
    case GEN_Shape_Triangle:
        if (phase < phaseDuty)
        {
            value = ((2.0f / (phaseDuty)) * phase) - 1.0f;
        }
        else
        {
            value = ((2.0f / (phaseDuty - PDSP_2PI)) * (phase - phaseDuty)) + 1.0f;
        }
        value *= pHandle->amplitude;
        break;
    case GEN_Shape_Sawtooth:
        value = ((2.0f / PDSP_2PI) * phase) - 1.0f;
        break;
    case GEN_Shape_Noise:
        value = ((((float)rand() / RAND_MAX) * 2.0f) - 1.0f);
        break;
    case GEN_Shape_NoiseNormal:
        value = AWGN_generator();
        break;
    default:
        break;
    }

    return value *= pHandle->amplitude;
}

float AWGN_generator(void)
{ /* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
    float temp1, temp2, result;
    int p = 1;
    while (p > 0)
    {
        temp2 = (rand() / ((float)RAND_MAX));
        if (temp2 == 0)
        { // temp2 is >= (RAND_MAX / 2)
            p = 1;
        }
        else
        {
            p = -1;
        }
    }
    temp1 = cosf((PDSP_2PI * rand()) / ((float)RAND_MAX));
    result = sqrtf(-2.0 * logf(temp2)) * temp1;

    return result; // return the generated random sample to the caller
}

void GEN_NOISE_InitUniform(GEN_NOISE_UniformHandle_st *hCfg, long seed,
                           float start, float stop)
{
    hCfg->seed = seed;
    hCfg->start = start;
    hCfg->stop = stop;

    hCfg->a = 16807;      /* a = 7^5 */
    hCfg->m = 2147483647; /* m = 2^31 - 1 */
    hCfg->q = 127773;     /* q = m / a = quotient */
    hCfg->r = 2836;       /* r = m % a = remainder */
}

float GEN_NOISE_GetValueUniform(GEN_NOISE_UniformHandle_st *pHandle)
{
    pHandle->seed = (pHandle->a * (pHandle->seed % pHandle->q)) - (pHandle->r * (pHandle->seed / pHandle->q)); /* update seed */
    if (pHandle->seed < 0)                                                                                     /* wrap to positive values */
        pHandle->seed += pHandle->m;

    float y = ((float)pHandle->seed / (float)pHandle->m); // [0   1)
    y *= (pHandle->stop - pHandle->start);
    y += pHandle->start;

    return y;
}

void GEN_NOISE_InitNormal(GEN_NOISE_NormalHandle_st *hCfg, float mean,
                          float stdDeviation)
{
    hCfg->mean = mean;
    hCfg->stdDeviation = stdDeviation;
    hCfg->call = 0;
    hCfg->X1 = 0.0;
    hCfg->X2 = 0.0;
}

float GEN_NOISE_GetValueNormal(GEN_NOISE_NormalHandle_st *pHandle)
{
    float U1, U2, W, mult, y;

    if (pHandle->call == 1)
    {
        pHandle->call = !(pHandle->call);
        y = (pHandle->mean + pHandle->stdDeviation * pHandle->X2);
    }
    else
    {
        do
        {
            U1 = -1 + ((float)rand() / RAND_MAX) * 2;
            U2 = -1 + ((float)rand() / RAND_MAX) * 2;
            W = powf(U1, 2) + powf(U2, 2);
        } while (W >= 1 || W == 0);

        mult = sqrt((-2 * logf(W)) / W);
        pHandle->X1 = U1 * mult;
        pHandle->X2 = U2 * mult;
        pHandle->call = !(pHandle->call);

        y = (pHandle->mean + pHandle->stdDeviation * pHandle->X1);
    }
    return y;
}

void GEN_NOISE_InitGalois(GEN_NOISE_GaloisHandle_st *hCfg, uint32_t seed,
                          uint32_t key, uint8_t length)
{
    hCfg->key = key;
    hCfg->value = seed;
    hCfg->length = length;
}

uint32_t GEN_NOISE_GetValueGalois(GEN_NOISE_GaloisHandle_st *pHandle)
{
    uint32_t lsb;

    pHandle->value &= ((1 << pHandle->length) - 1);
    lsb = pHandle->value & 1;
    pHandle->value >>= 1;
    if (lsb)
        pHandle->value ^= pHandle->key;

    return pHandle->value;
}

/*
 * @brief Initialization of SWEEP generator instance
 *
 * @param hCfg          Configuration structure for BURS generator
 * @param hCfg          Configuration structure for signal generator
 * @param nCycles       Number of signal period
 * @param burstPeriod   Period of burst [s]
 * @retval None
 */
void GEN_BURST_Init(GEN_BURST_Handle_st *hCfg, GEN_Handle_st *hGen,
                    uint16_t nCycles, float burstPeriod, float phaseOffset)
{
    hCfg->generator = hGen;
    hCfg->generator->acu.phase = phaseOffset;
    hCfg->sampleCycle = (uint32_t)(PDSP_2PI / hCfg->generator->acu.phaseStep);
    hCfg->sampleCycle *= nCycles;
    hCfg->sampleCycleLeft = hCfg->sampleCycle;
    hCfg->samplePeriod = (uint32_t)(burstPeriod * CODEC_fs);
    hCfg->samplePeriodLeft = hCfg->samplePeriod;
    hCfg->phaseOffset = fmodf(phaseOffset, PDSP_2PI);
}

/*
 * @brief   Calculate next value of BURST generator
 *
 * @param   hCfg        Configuration structure for BURST generator
 * @retval              Value of current sample
 */
float GEN_BURST_GetValue(GEN_BURST_Handle_st *hCfg)
{
    float value;

    if (hCfg->sampleCycleLeft > 0)
    {
        value = GEN_GetValue(hCfg->generator);
        if (hCfg->generator->acu.phase > (PDSP_2PI + hCfg->phaseOffset))
        {
            hCfg->generator->acu.phase -= PDSP_2PI;
        }
        hCfg->sampleCycleLeft--;
    }
    else
    {
        value = 0.0f;
    }

    hCfg->samplePeriodLeft--;
    // Check if reach burst period
    if (hCfg->samplePeriodLeft == 0)
    {
        hCfg->sampleCycleLeft = hCfg->sampleCycle;
        hCfg->samplePeriodLeft = hCfg->samplePeriod;
        hCfg->generator->acu.phase = hCfg->phaseOffset;
    }

    return value;
}

/*
 * @brief Initialization of SWEEP generator instance
 *
 * @param hCfg          Configuration structure for generator
 * @param freqStart     Start frequency value [Hz]
 * @param freqStop      Stop frequency value [Hz]
 * @param duration      Time for change from freqStart to freqStop [s]
 * @param phaseOffset   Initial phase offset [radiant]
 * @retval None
 */
void GEN_SWEEP_Init(GEN_SWEEP_Handle_st *hCfg, GEN_Handle_st *hGen,
                    float freqStart, float freqStop, float duration,
                    SWEEP_MODE_t mode)
{
    freqStart = fabsf(freqStart);
    freqStart = (freqStart < (CODEC_fs / 2)) ? freqStart : (CODEC_fs / 2);
    freqStop = fabsf(freqStop);
    freqStop = (freqStop < (CODEC_fs / 2)) ? freqStop : (CODEC_fs / 2);

    hCfg->duration = fabsf(duration);
    hCfg->mode = mode;
    if (mode == SWEEP_MODE_LINEAR)
    {
        hCfg->phaseStepStart = freqStart * PDSP_2PI_DIV_FS; // Phase step on start
        hCfg->phaseStepStop = freqStop * PDSP_2PI_DIV_FS;   // Phase step on stop
    }
    else
    {
        hCfg->phaseStepStart = log10f(freqStart); // Log10 of start frequency
        hCfg->phaseStepStop = log10f(freqStop);   // Log10 of stop frequency
    }
    hCfg->phaseStep = hCfg->phaseStepStart;                                                  // Current phase step / current log10 of frequency step
    hCfg->phaseInc = ((hCfg->phaseStepStop - hCfg->phaseStepStart) / (duration * CODEC_fs)); // Phase change per sample / log10 of frequency change per sample

    hCfg->generator = hGen;
    hCfg->generator->acu.phaseStep = freqStart;
    // GEN_SetFrequency(hCfg->generator, freqStart);
}

/*
 * @brief   Calculate next value of SWEEP generator
 *
 * @param   hCfg        Configuration structure for generator
 * @retval              Value of current sample
 */
float GEN_SWEEP_GetValue(GEN_SWEEP_Handle_st *hCfg)
{
    float value;
    float phaseStep;

    value = GEN_GetValue(hCfg->generator);
    // Increment phase
    hCfg->phaseStep += hCfg->phaseInc;
    // Check if overflow phase step - is over stop frequency
    if (hCfg->phaseStep > hCfg->phaseStepStop)
    {
        hCfg->phaseStep -= (hCfg->phaseStepStop - hCfg->phaseStepStart);
    }
    if (hCfg->mode == SWEEP_MODE_LINEAR)
    {
        phaseStep = hCfg->phaseStep;
    }
    else
    {
        phaseStep = (powf(10.0f, hCfg->phaseStep) * PDSP_2PI_DIV_FS); // Change phase step
    }
    hCfg->generator->acu.phaseStep = phaseStep;

    return value;
}
