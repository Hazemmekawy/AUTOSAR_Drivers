/********************************************************************************************
 *
 * Module Name	:	Digital Input Output Configurations
 * File Name	:	Dio_Cfg.h
 * Version		:	1.0.0
 * Created on  	: 	25/04/2020
 * Author      	: 	Team_2
 * Description	:	Pre-Compile Configuration Header file for Dio Module.
 * 					This file contains the symbolic names which will create
 * 					in the configuration process
 *
 ********************************************************************************************/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_


/*
 *	Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION					(1U)
#define DIO_CFG_SW_MINOR_VERSION					(0U)
#define DIO_CFG_SW_PATCH_VERSION					(0U)


/*
 *	AUTOSAR version implemented by this file
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION			(4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION			(3U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION			(1U)






/* Pre-Compile option for version information API */
#define DIO_VERSION_INFO_API					(STD_ON)

/* Pre-Compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API					(STD_ON)

/* Pre-Compile option for development error detection API */
#define DIO_DevErrorDetect_API					(STD_OFF)



/* Number of the configured Dio Channel */
#define DIO_CONFIGURED_CHANNELS					(3U)

/* Number of the configured Dio Ports */
#define DIO_CONFIGURED_PORTS					(2U)

/* Number of the configured Dio Channel Group */
#define DIO_CONFIGURED_CHANNEL_GROUP			(1U)




/* Channel Index in the Array of configuration structure in Dio_Lcfg.c */
/* for inestance */
#define DioCfg_LED1_CHANNEL_ID_INDEX				((uint8) 0x00)
#define DioCfg_LED1_CHANNEL_NUM						((uint8) 0x01)
#define DioCfg_LED1_PORT_NUM						((Dio_PortType) 2)

#define DioCfg_LED2_CHANNEL_ID_INDEX				((uint8) 0x01)
#define DioCfg_LED2_CHANNEL_NUM						((uint8) 0x02)
#define DioCfg_LED2_PORT_NUM						((Dio_PortType) 2)


#define DioCfg_LED3_CHANNEL_ID_INDEX				((uint8) 0x02)
#define DioCfg_LED3_CHANNEL_NUM						((uint8) 0x04)
#define DioCfg_LED3_PORT_NUM						((Dio_PortType) 2)



/* DIO Configured Port Index*/
#define DioCfg_PORT1_ID_INDEX						((uint8) 0x00)
#define DioCfg_PORT1_NUM							((Dio_PortType) 2)

#define DioCfg_PORT2_ID_INDEX						((uint8) 0x01)
#define DioCfg_PORT2_NUM							((Dio_PortType) 3)


/* DIO Configured Channel Group */
#define DioCfg_SEVENSEG_CHANNEL_GROUP_INDEX			((uint8) 0x01)
#define DioCfg_SEVENSEG_CHANNEL_GROUP_MASK			((uint8) 0b11111110)
#define DioCfg_SEVENSEG_CHANNEL_GROUP_OFFSET		((uint8) 0x01)







#endif /* DIO_CFG_H_ */



























