/*
 * generator.c
 *
 *  Created on: 20 kwi 2022
 *      Author: pdabal
 */

#include "pdsp.h"
#include "generator.h"

void OSC_Init(OSC_Cfg_t * hOscCfg, float amplitude, float frequency){
    frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hOscCfg->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);        //
    hOscCfg->phaseStep = (frequency * PDSP_2PI_DIV_FS);
    hOscCfg->phase = 0.0f;
}

float OSC_GetValue(OSC_Cfg_t * hOscCfg){
    float wave;

    wave = hOscCfg->amplitude * sinf(hOscCfg->phase);
    hOscCfg->phase += hOscCfg->phaseStep;
    hOscCfg->phase = fmodf(hOscCfg->phase, PDSP_2PI);

    return wave;
}

void OSC_SetFrequency(OSC_Cfg_t * hOscCfg, float frequency){
    frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hOscCfg->phaseStep = (frequency * PDSP_2PI_DIV_FS);
}

void OSC_SetAmplitude(OSC_Cfg_t * hOscCfg, float amplitude){
    hOscCfg->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);        //
}

void SIN_Init(SIN_Cfg_t * hSinOsc, float amplitude, float frequency){
    hSinOsc->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);
    hSinOsc->frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hSinOsc->cos_theta = (cosf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * 2);
    hSinOsc->sin_theta = (sinf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * hSinOsc->amplitude);
    hSinOsc->y[0] = 0;
    hSinOsc->y[1] = 1;
    hSinOsc->y[2] = 0;
}

float SIN_GetValue(SIN_Cfg_t * hSinOsc){
    hSinOsc->y[0] = (hSinOsc->cos_theta * hSinOsc->y[1]) - hSinOsc->y[2];
    hSinOsc->y[2] = hSinOsc->y[1];
    hSinOsc->y[1] = hSinOsc->y[0];
    return (hSinOsc->sin_theta * hSinOsc->y[0]);
}

void SIN_SetFrequency(SIN_Cfg_t * hSinOsc, float frequency){
    hSinOsc->frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hSinOsc->cos_theta = (cosf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * 2);
    hSinOsc->sin_theta = (sinf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * hSinOsc->amplitude);
}

void SIN_SetAmplitude(SIN_Cfg_t * hSinOsc, float amplitude){
    hSinOsc->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);        //
    hSinOsc->cos_theta = (cosf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * 2);
    hSinOsc->sin_theta = (sinf(PDSP_2PI_DIV_FS * hSinOsc->frequency) * hSinOsc->amplitude);
}

void TAB_Init(TAB_Cfg_t * hSinTab, float amplitude, float frequency){
    frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hSinTab->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);
    hSinTab->phaseIndex = 0;
    hSinTab->length = (int16_t)(CODEC_fs / frequency);
    hSinTab->samples = (float *) malloc(sizeof(float) * hSinTab->length);

    if (hSinTab->samples == NULL)
        return;

    uint16_t i;
    float phase = 0.0f;
    float phaseStep = (PDSP_2PI / hSinTab->length);
    float * pValue = hSinTab->samples;
    for (i = 0; i < hSinTab->length; i++){
        *pValue = sinf(phase);
        phase += phaseStep;
        pValue++;
    }
}

float TAB_GetValue(TAB_Cfg_t * hSinTab){
    float wave;

    wave = (hSinTab->samples[hSinTab->phaseIndex] * hSinTab->amplitude);
    hSinTab->phaseIndex++;
    hSinTab->phaseIndex %= hSinTab->length;

    return wave;
}

void TAB_SetFrequency(TAB_Cfg_t * hSinTab, float frequency){
    free(hSinTab->samples);

    frequency = (frequency < (CODEC_fs / 2.0f)) ? frequency : (CODEC_fs / 2.0f);
    hSinTab->length = (int16_t)(CODEC_fs / frequency);
    hSinTab->phaseIndex = 0;
    hSinTab->samples = (float *) malloc(sizeof(float) * hSinTab->length);
    if (hSinTab->samples == NULL)
        return;

    uint16_t i;
    float phase = 0.0f;
    float phaseStep = (PDSP_2PI / hSinTab->length);
    float * pValue = hSinTab->samples;
    for (i = 0; i < hSinTab->length; i++){
        *pValue = sinf(phase);
        phase += phaseStep;
        pValue++;
    }
}

void TAB_SetAmplitude(TAB_Cfg_t * hSinTab, float amplitude){
    hSinTab->amplitude = (amplitude < (CODEC_Vpp * 0.5f)) ? amplitude : (CODEC_Vpp * 0.5f);        //
}
