/*
 * codec.c
 *
 *  Created on: 18 mar 2021
 *      Author: pdabal
 */
#include "pdsp.h"

void CODEC_SetSampleStereo(CODEC_Data sample){
    PDSP_SetValue(sample);
}

void CODEC_SetSampleMono(int16_t sample)
{
    CODEC_Data value;

    value.channel[0] = sample;
    value.channel[1] = sample;
    PDSP_SetValue(value);
}
void CODEC_SetSampleFloat(float sample)
{
    CODEC_Data value;

    value.channel[0] = (Int16)sample;
    value.channel[1] = (Int16)sample;
    PDSP_SetValue(value);
}

CODEC_Data CODEC_GetSampleStereo(void)
{
    CODEC_Data value;

    value.uint = PDSP_GetValue();
    return value;
}

Int16 CODEC_GetSampleMono(void)
{
    Int16 sample;
    CODEC_Data value;

    value.uint = PDSP_GetValue();
    sample = ((value.channel[0] + value.channel[1]) >> 2);

    return sample;
}

float CODEC_GetSampleFloat(void)
{
    float sample;
    CODEC_Data value;

    value.uint = PDSP_GetValue();
    sample = ((float) value.channel[0] + (float) value.channel[1]) / 2.0f;

    return sample;
}

