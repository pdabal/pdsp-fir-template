/*
 * generator.h
 *
 *  Created on: 20 kwi 2022
 *      Author: pdabal
 */

#ifndef INCLUDE_GENERATOR_H_
#define INCLUDE_GENERATOR_H_

typedef struct {
    float amplitude;
    float phase;
    float phaseStep;
}OSC_Cfg_t;

typedef struct {
    float amplitude;
    float frequency;
    float cos_theta;
    float sin_theta;
    float y[3];
}SIN_Cfg_t;

typedef struct {
    float amplitude;
    uint16_t phaseIndex;
    uint16_t length;
    float * samples;
}TAB_Cfg_t;

void    OSC_Init        (OSC_Cfg_t * hOscCfg, float amplitude, float frequency);
float   OSC_GetValue    (OSC_Cfg_t * hOscCfg);
void    OSC_SetFrequency(OSC_Cfg_t * hOscCfg, float frequency);
void    OSC_SetAmplitude(OSC_Cfg_t * hOscCfg, float amplitude);

void    SIN_Init        (SIN_Cfg_t * hSinOsc, float amplitude, float frequency);
float   SIN_GetValue    (SIN_Cfg_t * hSinOsc);
void    SIN_SetFrequency(SIN_Cfg_t * hSinOsc, float frequency);
void    SIN_SetAmplitude(SIN_Cfg_t * hSinOsc, float amplitude);

void    TAB_Init        (TAB_Cfg_t * hSinTab, float amplitude, float frequency);
float   TAB_GetValue    (TAB_Cfg_t * hSinTab);
void    TAB_SetFrequency(TAB_Cfg_t * hSinTab, float frequency);
void    TAB_SetAmplitude(TAB_Cfg_t * hSinTab, float amplitude);

#endif /* INCLUDE_GENERATOR_H_ */
