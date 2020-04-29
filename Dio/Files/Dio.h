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

/**
 * @brief Type definition for Dio_ChannelType used by the Dio API's
 */
typedef uint8 Dio_ChannelType;

/**
 * @brief Type definition used for ports
 */
typedef uint8 Dio_PortType;

/**
 * @brief Type definition used for logical level of channels
 */
typedef uint8 Dio_LevelType;

/**
 * @brief Type definition used for logical level of ports
 */
typedef uint8 Dio_PortLevelType;

/**
 * @brief Type definition structure to settings of channel group
 */
typedef struct Dio_ChannelGroup{
	uint8 mask;
	uint8 offset;
	Dio_PortType port;
}Dio_ChannelGroupType;


#define DIO_PORT_LEVEL_HIGH 				((Dio_PortLevelType) 0xFF)
#define DIO_PORT_LEVEL_LOW  				((Dio_PortLevelType) 0x00)


/********************************************************************************************
 * 									Define values
 ********************************************************************************************/
#define DIO_CHANNEL_1		((uint8) 0x10)
#define DIO_CHANNEL_1		((uint8) 0x11)
#define DIO_CHANNEL_2		((uint8) 0x12)
#define DIO_CHANNEL_3		((uint8) 0x13)
#define DIO_CHANNEL_4		((uint8) 0x14)
#define DIO_CHANNEL_5		((uint8) 0x15)
#define DIO_CHANNEL_6		((uint8) 0x16)
#define DIO_CHANNEL_7		((uint8) 0x17)


#define DIO_CHANNEL_8		((uint8) 0x20)
#define DIO_CHANNEL_9		((uint8) 0x21)
#define DIO_CHANNEL_10		((uint8) 0x22)
#define DIO_CHANNEL_11		((uint8) 0x23)
#define DIO_CHANNEL_12		((uint8) 0x24)
#define DIO_CHANNEL_13		((uint8) 0x25)
#define DIO_CHANNEL_14		((uint8) 0x26)
#define DIO_CHANNEL_15		((uint8) 0x27)


#define DIO_CHANNEL_16		((uint8) 0x30)
#define DIO_CHANNEL_17		((uint8) 0x31)
#define DIO_CHANNEL_18		((uint8) 0x32)
#define DIO_CHANNEL_19		((uint8) 0x33)
#define DIO_CHANNEL_20		((uint8) 0x34)
#define DIO_CHANNEL_21		((uint8) 0x35)
#define DIO_CHANNEL_22		((uint8) 0x36)
#define DIO_CHANNEL_23		((uint8) 0x37)


#define DIO_CHANNEL_24		((uint8) 0x40)
#define DIO_CHANNEL_25		((uint8) 0x41)
#define DIO_CHANNEL_26		((uint8) 0x42)
#define DIO_CHANNEL_27		((uint8) 0x43)
#define DIO_CHANNEL_28		((uint8) 0x44)
#define DIO_CHANNEL_29		((uint8) 0x45)
#define DIO_CHANNEL_30		((uint8) 0x46)
#define DIO_CHANNEL_31		((uint8) 0x47)


#define DIO_PORT_A			((uint8) 0x51)
#define DIO_PORT_B			((uint8) 0x52)
#define DIO_PORT_C			((uint8) 0x53)
#define DIO_PORT_D			((uint8) 0x54)




/********************************************************************************************
 * 							Function Prototypes
 ********************************************************************************************/

/**
 * @brief Returns the value of the specified DIO channel.
 * @param ChannelId: ID of DIO channel
 * @return Dio_LevelType:
 * 					- STD_HIGH
 *					- STD_LOW
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/**
 * @brief Service to set a level of a channel
 * @param ChannelId: ID of DIO channel
 * @param Level: Value to be written
 * @return: None
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/**
 * @brief This Service reads a subset of the adjoining bits of a port
 * @param ChannelGroupIdPtr: Pointer to ChannelGroup
 * @return Dio_PortLevelType: Level of a subset of the adjoining bits of a port
 */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

/**
 * @brief Service to set a subset of the adjoining bits of a port to a specified level
 * @param ChannelGroupIdPtr: Pointer to ChannelGroup
 * @param Level: Value to be written
 * @return None
 */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

/**
 * @brief Returns the level of all channels of that port
 * @param PortId: ID of DIO Port
 * @return Dio_PortLevelType: Level of all channels of that port
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/**
 * @brief Service to set a value of the port
 * @param PortId: ID of DIO Port
 * @param Level: Value to be written
 * @return None
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);


/**
 * @brief Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and
 * 			return the level of the channel after flip
 * @param ChannelId: ID of DIO channel
 * @return Dio_LevelType:
 * 					- STD_HIGH
 * 					- STD_LOW
 */
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif



/**
 * @brief Service to get the version information of this module
 * @param VersionInfo: Pointer to where to store the version information of this modul
 * @return None
 */
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);
#endif



#endif /* DIO_H_ */
