/********************************************************************************************
 *
 * Module Name	:	Default Error Tracer
 * File Name	:	Det.h
 * Version		:	1.0.0
 * Created on  	: 	25/04/2020
 * Author      	: 	Team_2
 * Description	:	Default error tracer stores the development errors
 * 					reported by the other modules.
 * 
 ********************************************************************************************/

#ifndef DET_H_
#define DET_H_


/*
 * 	Module Identifier
 */
#define DET_MODULE_ID						(15U)

/*
 *	Module Version 1.0.0
 */
#define DET_SW_MAJOR_VERSION				(1U)
#define DET_SW_MINOR_VERSION				(0U)
#define DET_SW_PATCH_VERSION				(0U)


/*
 *	AUTOSAR version implemented by this file
 */
#define DET_AR_RELEASE_MAJOR_VERSION		(4U)
#define DET_AR_RELEASE_MINOR_VERSION		(3U)
#define DET_AR_RELEASE_PATCH_VERSION		(1U)



/* Include AUTOSAR standard types of  */
#include "Std_Types.h"

#if ((DET_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) ||\
		(DET_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION) ||\
		(DET_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
#error ("The AUTOSAR Version of Std_Types.h module and Det.h module does not match")
#endif


#include "Rte_Det_Type.h"
#if ((DET_AR_RELEASE_MAJOR_VERSION != RTE_DET_TYPE_AR_RELEASE_MAJOR_VERSION) ||\
		(DET_AR_RELEASE_MINOR_VERSION != RTE_DET_TYPE_AR_RELEASE_MINOR_VERSION) ||\
		(DET_AR_RELEASE_PATCH_VERSION != RTE_DET_TYPE_AR_RELEASE_PATCH_VERSION))
#error ("The AUTOSAR Version of Std_Types.h module and Det.h module does not match")
#endif


typedef struct Det_Config{
	/* implementation of expected errors */
}Det_ConfigType;


/********************************************************************************************
 * 									Function Prototypes
 ********************************************************************************************/

void Det_Init(const Det_ConfigType* ConfigPtr);

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

void Det_Start(void);

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);

void Det_GetVersionInfo(Std_VersionInfoType* versioninfo);


Std_ReturnType Det_InformError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

Std_ReturnType Det_ReportRuntimeErrorCallout(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

Std_ReturnType Det_ReportTransientFaultCallout(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);


#endif /* DET_H_ */
