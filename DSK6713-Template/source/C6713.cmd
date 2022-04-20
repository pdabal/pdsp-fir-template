/****************************************************************************/
/*  C6713.cmd                                                               */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an TMS320C6713        */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific C6xxx    */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

-stack	0x0800			/* Stos */
-heap	0x0800			/* Sterta */

MEMORY
{
	IVECS:  	org = 0x00000000, len = 0x00000220  /* Wektor przerwañ w pamiêci wewnêtrznej RAM */
	IRAM:		org = 0x00000220, len = 0x0002FDE0  /* 192kB - Pamiêæ wewnêtrzna RAM */
	L2RAM:  	org = 0x00030000, len = 0x00010000  /* 64kB  - Pamiêæ wewnêtrzny RAM/CACHE */
	EMIFCE0:	org = 0x80000000  len = 0x01000000  /* SDRAM in 6713 DSK */
	EMIFCE1:  	org = 0x90000000  len = 0x00020000  /* Flash/CPLD in 6713 DSK */
	EMIFCE2:  	org = 0xA0000000  len = 0x10000000  /* Daughterboard in 6713 DSK */
	EMIFCE3:  	org = 0xB0000000  len = 0x10000000  /* Daughterboard in 6713 DSK */
}


/*  */
SECTIONS
{
	.EXT_RAM 		> EMIFCE0
	.vectors 		> IVECS		/* Wektro obs³ugi przerwañ */

	.text    		> IRAM		/* Code */
	.stack   		> IRAM		/* Stack (local variables) */
	.bss     		> IRAM		/* Global and static variables */
	.cio     		> EMIFCE0	/* Buffers for stdio functions */
	.const   		> IRAM		/* Global and static string literals */
	.data			> IRAM
	.switch  		> IRAM		/* Tables for switch instructions */	
	.sysmem  		> IRAM		/* Memory for malloc fcns (heap) */
	.far     		> IRAM		/* Aggregates (arrays & structures) */
	.args			> IRAM
	.ppinfo			> IRAM
	.ppdata			> IRAM
	
	.csldata 		> IRAM		/* Dane dla biblioteki CSL */

    /* COFF sections */
	.cinit   		> IRAM		/* Initial values for global/static vars */
	.pinit   		> IRAM		/* Initial values for C++ constructors */  

    /* EABI sections */
    .binit         	> IRAM
    .init_array    	> IRAM
    .neardata      	> IRAM
    .fardata       	> IRAM
    .rodata        	> IRAM
    .c6xabi.exidx  	> IRAM
    .c6xabi.extab  	> IRAM
}
