*******************************************************************************
*           Copyright (C) 1999-2001 Texas Instruments Incorporated.
*                           All Rights Reserved
*------------------------------------------------------------------------------
* FILENAME...... csl_chiphal.inc
* DATE CREATED.. 03/13/1999 
* LAST MODIFIED. 05/19/2004  Added CHIP_DM641 and CHIP_DM640
*                06/26/2003  Added CHIP_6411
*		 06/17/2003  Added CHIP_6712C
*                06/09/2003  Added EMU_SUPPORT
*                05/28/2003  Added CHIP_6711C
*                11/05/2001  -  CHIP_6411 / CHIP_DM642 
*                10/29/2001  -  MCASP + PLL + I2C SUPPORT Macro for 6713
*                10/01/2001  -  CHIP_6713 device 
********************************************************************************
  .if $isdefed("_CSL_CHIPHAL_INC_")==0
_CSL_CHIPHAL_INC_ .set 1

  .if $isdefed(".ASSEMBLER_VERSION")
	.mmsg "asmVersion defined"
	.asg   .ASSEMBLER_VERSION, asmVersion
  .else
      .asg    0, asmVersion
  .endif

********************************************************************************
* macro and constant declarations
********************************************************************************

 .if $isdefed("CHIP_ALL")==0
CHIP_ALL .set 0
  .else
CHIP_6201 .set 1
CHIP_6202 .set 1
CHIP_6203 .set 1
CHIP_6204 .set 1
CHIP_6205 .set 1
CHIP_6211 .set 1
CHIP_6701 .set 1
CHIP_6711 .set 1
CHIP_6712 .set 1
CHIP_6713 .set 1
CHIP_DA610 .set 1
CHIP_DM642 .set 1
CHIP_DM641 .set 1
CHIP_DM640 .set 1
CHIP_6412 .set 1
CHIP_6414 .set 1
CHIP_6415 .set 1
CHIP_6416 .set 1
CHIP_6711C .set 1
CHIP_6712C .set 1
CHIP_6411 .set 1
CHIP_6410 .set 1
CHIP_6413 .set 1
CHIP_6418 .set 1
  .endif


 .if $isdefed("CHIP_6201")==0
CHIP_6201 .set 0
 .endif

 .if $isdefed("CHIP_6202")==0
CHIP_6202 .set 0
 .endif

 .if $isdefed("CHIP_6203")==0
CHIP_6203 .set 0
 .endif

 .if $isdefed("CHIP_6204")==0
CHIP_6204 .set 0
 .endif

 .if $isdefed("CHIP_6205")==0
CHIP_6205 .set 0
 .endif

 .if $isdefed("CHIP_6211")==0
CHIP_6211 .set 0
 .endif

 .if $isdefed("CHIP_6701")==0
CHIP_6701 .set 0
 .endif

 .if $isdefed("CHIP_6711")==0
CHIP_6711 .set 0
 .endif
 
 .if $isdefed("CHIP_6712")==0
CHIP_6712 .set 0
 .endif

 .if $isdefed("CHIP_6713")==0
CHIP_6713 .set 0
 .endif

 .if $isdefed("CHIP_DA610")==0
CHIP_DA610 .set 0
 .endif


 .if $isdefed("CHIP_DM642")==0
CHIP_DM642 .set 0
 .endif

 .if $isdefed("CHIP_DM641")==0
CHIP_DM641 .set 0
 .endif

 .if $isdefed("CHIP_DM640")==0
CHIP_DM640 .set 0
 .endif

 .if $isdefed("CHIP_6412")==0
CHIP_6412 .set 0
 .endif

 .if $isdefed("CHIP_6414")==0
CHIP_6414 .set 0
 .endif

 .if $isdefed("CHIP_6415")==0
CHIP_6415 .set 0
 .endif

 .if $isdefed("CHIP_6416")==0
CHIP_6416 .set 0
 .endif

 .if $isdefed("CHIP_6711C")==0
CHIP_6711C .set 0
 .endif
 
 .if $isdefed("CHIP_6712C")==0
CHIP_6712C .set 0
 .endif

 .if $isdefed("CHIP_6411")==0
CHIP_6411 .set 0
 .endif

 .if $isdefed("CHIP_6410")==0
CHIP_6410 .set 0
 .endif

 .if $isdefed("CHIP_6413")==0
CHIP_6413 .set 0
 .endif

 .if $isdefed("CHIP_6418")==0
CHIP_6418 .set 0
 .endif

 .if ((CHIP_6201|CHIP_6202|CHIP_6203|CHIP_6204|CHIP_6205|CHIP_6211|CHIP_6701|CHIP_6711|CHIP_6712|CHIP_6713|CHIP_DA610|CHIP_DM642|CHIP_DM641|CHIP_DM640|CHIP_6412|CHIP_6414|CHIP_6415|CHIP_6416|CHIP_6711C|CHIP_6712C|CHIP_6411|CHIP_6410|CHIP_6413|CHIP_6418)==0)
 .emsg "NO CHIP DEFINED (use -dCHIP_XXXX where XXXX is chip number, i.e. 6201)"
 .endif

CHIP_NONE .set 0

SUPPORT .macro symbol,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23

 .var r0,r1,r2,r3,r4,r5,r6
 .asg ( c0*CHIP_6201 )|( c1*CHIP_6202 )|( c2*CHIP_6203 )|( c3*CHIP_6204 ),r0
 .asg ( c4*CHIP_6205 )|( c5*CHIP_6211 )|( c6*CHIP_6701 )|( c7*CHIP_6711 ),r1
 .asg ( c8*CHIP_6712 )|( c9*CHIP_6713 )|(c10*CHIP_DA610),r2 
 .asg (c11*CHIP_DM642)|(c12*CHIP_DM641)|(c13*CHIP_DM640),r3
 .asg (c14*CHIP_6412 )|(c15*CHIP_6414 )|(c16*CHIP_6415 )|(c17*CHIP_6416 ),r4
 .asg (c18*CHIP_6711C)|(c19*CHIP_6712C)|(c20*CHIP_6411 ),r5
 .asg (c21*CHIP_6410)|(c22*CHIP_6413)|(c23*CHIP_6418),r6
symbol .set (r0|r1|r2|r3|r4|r5|r6)
 .endm

;*---------------------------------------------------------------------------*/
;*                            6 6 6 6 6 6 6 6 6 6 D D D D 6 6 6 6 6 6 6 6 6 6*/
;*                            2 2 2 2 2 2 7 7 7 7 A M M M 4 4 4 4 7 7 4 4 4 4*/
;*                            0 0 0 0 0 1 0 1 1 1 6 6 6 6 1 1 1 1 1 1 1 1 1 1*/
;*                            1 2 3 4 5 1 1 1 2 3 1 4 4 4 2 4 5 6 1 2 1 0 3 8*/
;*                                                0 2 1 0         C C        */
;*---------------------------------------------------------------------------*/
  SUPPORT   CACHE_SUPPORT,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   DMA_SUPPORT,      1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  SUPPORT   EDMA_SUPPORT,     0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   EMIF_SUPPORT,     1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0
  SUPPORT   EMIFA_SUPPORT,    0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1
  SUPPORT   EMIFB_SUPPORT,    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0
  SUPPORT   GPIO_SUPPORT,     0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   HPI_SUPPORT,      1,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1
  SUPPORT   I2C_SUPPORT,      0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1
  SUPPORT   IRQ_SUPPORT,      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   MCASP_SUPPORT,    0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1
  SUPPORT   MCBSP_SUPPORT,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   PLL_SUPPORT,      0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0
  SUPPORT   TIMER_SUPPORT,    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   XBUS_SUPPORT,     0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  SUPPORT   PCI_SUPPORT,      0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,1,0,0,0
  SUPPORT   DAT_SUPPORT,      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   PWR_SUPPORT,      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   UTOP_SUPPORT,     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0
  SUPPORT   TCP_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
  SUPPORT   VCP_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1
  SUPPORT   L2CACHE_SUPPORT,  0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   TC_SUPPORT,       0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  SUPPORT   FPU_SUPPORT,      0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0
  SUPPORT   C01_SUPPORT,      1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  SUPPORT   C11_SUPPORT,      0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0
  SUPPORT   C64_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1
  SUPPORT   EMU_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1
                                                                             
;*---------------------------------------------------------------------------*/
;* added for DM642, DM641 and DM640 support begin                            */
;*---------------------------------------------------------------------------*/
  SUPPORT   VIC_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0
  SUPPORT   VP_SUPPORT,       0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0
  SUPPORT   EMAC_SUPPORT,     0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0
  SUPPORT   MDIO_SUPPORT,     0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0
;*---------------------------------------------------------------------------*/
;* added for DM642, DM641 and DM640 support end                              */
;*---------------------------------------------------------------------------*/
                                                                             
;*---------------------------------------------------------------------------*/
;* added for DRI300 support begin                                            */
;*---------------------------------------------------------------------------*/
  SUPPORT   ATL_SUPPORT,      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1
;*---------------------------------------------------------------------------*/
;* added for DRI300 support end                                              */
;*---------------------------------------------------------------------------*/
                                                                               
                                                                               
;*-----------------------------------------------------------------------------*/


  .endif  ;_CSL_CHIPHAL_INC_
********************************************************************************
* End of csl_chiphal.inc
********************************************************************************

