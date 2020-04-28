/********************************************************************************************
 *
 * Module Name	:	Digital Input Output header
 * File Name	:	Dio.h
 * Version		:	1.0.0
 * Created on  	: 	25/04/2020
 * Author      	: 	Team_2
 * Description	:	Header file for Dio Module.
 *
 ********************************************************************************************/

#ifndef DIO_H_
#define DIO_H_



/*
 * 	Module Identifier
 */
#define DIO_MODULE_ID						(120U)

/*
 *	Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION				(1U)
#define DIO_SW_MINOR_VERSION				(0U)
#define DIO_SW_PATCH_VERSION				(0U)


/*
 *	AUTOSAR version implemented by this file
 */
#define DIO_AR_RELEASE_MAJOR_VERSION		(4U)
#define DIO_AR_RELEASE_MINOR_VERSION		(3U)
#define DIO_AR_RELEASE_PATCH_VERSION		(1U)






/*
 *	Include Standard types of AUTOSAR Version 4.3.1
 */
#include "Std_Types.h"
#if ((DIO_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION) ||\
		(DIO_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION) ||\
		(DIO_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
#error ("The AUTOSAR Version of Std_Types.h module and Dio.h module does not match")
#endif


/*
 *	Include Dio Pre-Compile Configuration header file
 */
#include "Dio_Cfg.h"
#if ((DIO_AR_RELEASE_MAJOR_VERSION != DIO_CFG_AR_RELEASE_MAJOR_VERSION) || \
		(DIO_AR_RELEASE_MINOR_VERSION != DIO_CFG_AR_RELEASE_MINOR_VERSION) ||\
		(DIO_AR_RELEASE_PATCH_VERSION != DIO_CFG_AR_RELEASE_PATCH_VERSION))
#error ("The AUTOSAR Version of Dio_Cfg.h header and Dio.h module does not match")
#endif



/********************************************************************************************
 * 									Dio Module Type definitions
 ********************************************************************************************/

/* Type definition for Dio_ChannelType used by the Dio API's */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_ChannelType used by the Dio API's */
/* [SWS_Dio_00183] Name: Dio_PortType, Type: uint8
*/
typedef uint8 Dio_PortType;
typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;


/**
 * @brief typedefs used for Channel Groups
 *
 */
typedef uint8 Dio_ChannelGroupMaskType;

typedef struct 
{
	Dio_ChannelGroupMaskType mask;
	uint8 offset;
	Dio_PortType port;
} Dio_ChannelGroupType;


#define DIO_PORT_LEVEL_HIGH 				((Dio_PortLevelType) 0xFF)
#define DIO_PORT_LEVEL_LOW  				((Dio_PortLevelType) 0x00)


/********************************************************************************************
 * 									Define values
 ********************************************************************************************/
#define DIO_CHANNEL_A0		((uint8) 0x00)
#define DIO_CHANNEL_A1		((uint8) 0x01)
#define DIO_CHANNEL_A2		((uint8) 0x02)
#define DIO_CHANNEL_A3		((uint8) 0x03)
#define DIO_CHANNEL_A4		((uint8) 0x04)
#define DIO_CHANNEL_A5		((uint8) 0x05)
#define DIO_CHANNEL_A6		((uint8) 0x06)
#define DIO_CHANNEL_A7		((uint8) 0x07)


#define DIO_CHANNEL_B0		((uint8) 0x00)
#define DIO_CHANNEL_B1		((uint8) 0x01)
#define DIO_CHANNEL_B2		((uint8) 0x02)
#define DIO_CHANNEL_B3		((uint8) 0x03)
#define DIO_CHANNEL_B4		((uint8) 0x04)
#define DIO_CHANNEL_B5		((uint8) 0x05)
#define DIO_CHANNEL_B6		((uint8) 0x06)
#define DIO_CHANNEL_B7		((uint8) 0x07)


#define DIO_CHANNEL_C0		((uint8) 0x00)
#define DIO_CHANNEL_C1		((uint8) 0x01)
#define DIO_CHANNEL_C2		((uint8) 0x02)
#define DIO_CHANNEL_C3		((uint8) 0x03)
#define DIO_CHANNEL_C4		((uint8) 0x04)
#define DIO_CHANNEL_C5		((uint8) 0x05)
#define DIO_CHANNEL_C6		((uint8) 0x06)
#define DIO_CHANNEL_C7		((uint8) 0x07)


#define DIO_CHANNEL_D0		((uint8) 0x00)
#define DIO_CHANNEL_D1		((uint8) 0x01)
#define DIO_CHANNEL_D2		((uint8) 0x02)
#define DIO_CHANNEL_D3		((uint8) 0x03)
#define DIO_CHANNEL_D4		((uint8) 0x04)
#define DIO_CHANNEL_D5		((uint8) 0x05)
#define DIO_CHANNEL_D6		((uint8) 0x06)
#define DIO_CHANNEL_D7		((uint8) 0x07)


#define DIO_PORT_A			((uint8) 0x01)
#define DIO_PORT_B			((uint8) 0x02)
#define DIO_PORT_C			((uint8) 0x03)
#define DIO_PORT_D			((uint8) 0x04)




/********************************************************************************************
 * 							Function Prototypes
 ********************************************************************************************/
/*
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/*
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/**
 * @brief Reads the value of a specified channel group
 * 
 * @param ChannelGroupIdPtr is a pointer to struct containing group info (Port, mask, offset)
 * @return Dio_PortLevelType is the value of the group (a range from 0 to 255)
 *
 */
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr );

/**
 * @brief Writes values to a specified channel group
 * 
 * @param ChannelGroupIdPtr is a pointer to struct containing group info (Port, mask, offset)
 * @param Level contains the values to be written on the group
 *
 */
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level );

/*
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/*
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);


/*
 */
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif



/*
 */
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);
#endif


/*
 */
#if (DIO_DevErrorDetect_API == STD_ON)
void Dio_DevErrorDetect(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);
#endif




#endif /* DIO_H_ */
