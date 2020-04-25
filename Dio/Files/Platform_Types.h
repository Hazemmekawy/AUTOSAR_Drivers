/*******************************************************************************
**  FILENAME     : Platform_Types.h                                           **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-04-22                                                 **
**                                                                            **
**  PLATFORM     :  AVR                                                       **
**                                                                            **
**  AUTHOR       : Alzahraa Mohamed & Esraa Khairy                            **
**                                                                            **                                                                           **
**  DESCRIPTION  : Dio platform types header file                             **
**                                                                            **
**  SPECIFICATION(S) : Platform Types , AUTOSAR Release 4.3.1                 **
*******************************************************************************/

#ifndef PLATFROM_TYPES_H
#define PLATFROM_TYPES_H

/*********************** PUBLISHED INFORMATION ELEMENTS ***********************/

/* Module Identifier */
#define PLATFORM_MODULE_ID						199U

/* AUTOSAR Release Version */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION		4U
#define PLATFORM_AR_RELEASE_MINOR_VERSION		3U
#define PLATFORM_AR_RELEASE_REVISION_VERSION	1U

/* Module Version */
#define PLATFORM_SW_MAJOR_VERSION				1U
#define PLATFORM_SW_MINOR_VERSION				0U
#define PLATFORM_SW_PATCH_VERSION				0U


/***************************** TYPE DEFINITIONS *******************************/

typedef unsigned char boolean;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;

typedef unsigned char uint8_least;
typedef unsigned short uint16_least;
typedef unsigned long uint32_least;

typedef signed char sint8_least;
typedef signed short sint16_least;
typedef signed long sint32_least;

typedef float float32;
typedef double float64;


/**************************** SYMBOL DEFINITIONS ******************************/

/* Boolean Range Definitons */

#ifndef TRUE 
#define TRUE 1U
#endif 

#ifndef FALSE 
#define FALSE 0U 
#endif

/* General Definitons */

#define CPU_TYPE_8 		 	8U
#define CPU_TYPE_16 	 	16U
#define CPU_TYPE_32 	 	32U
#define CPU_TYPE_64 	 	64U

#define MSB_FIRST 		 	0U
#define LSB_FIRST 		 	1U

#define HIGH_BYTE_FIRST  	0U
#define LOW_BYTE_FIRST   	1U


/* Specific Definitons for AVR */

#define CPU_TYPE		CPU_TYPE_8

#define CPU_BIT_ORDER	LSB_FIRST

#define CPU_BYTE_ORDER	LOW_BYTE_FIRST


#endif /* PLATFROM_TYPES_H */