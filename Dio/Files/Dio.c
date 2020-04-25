#include "Dio.h"
#include "Dio_MemMap.h"
#include "Det.h"
#include "SchM_Dio.h"



/************************** Macros **************************/

/**
 * @brief A macro used to validate channel group id
 *
 */
#define DIO_IS_CHANNEL_GROUP_VALID(group) 	(                  \
											(group == 0x01) || \
											(group == 0x03) || \
											(group == 0x07) || \
											(group == 0x0F) || \
											(group == 0x1F) || \
											(group == 0x3F) || \
											(group == 0x7F) || \
											(group == 0xFF)    \
											)




/************************** Team 3 **************************/
/*Author :
			1)Ahmed Zoher 
			2)Bassem Ezzat 
			3)Mahmoud Gamal 
			4)Mohamed Ibrahem 
			5)Mostafa Said 

Version : 1.0.0
Date:4/24/2020
*/


/*    this needed defines for functions 					*/
/*      1) Dio_Readchannel 								*/
/*      2) Dio_WritePort 									*/
/*      3) Dio_GetVersionInfo 								*/
/*********************** TOBEREMOVED************************* */
/*
#define PORT_A			0
#define PORT_B			1
#define PORT_C			2
#define PORT_D			3

#define STD_LOW			0
#define STD_HIGH		1
*/
/* Port A -> channel from 0-> 7*/
/* Port B -> channel from 8-> 15*/
/* Port C -> channel from 16-> 23*/
/* Port D -> channel from 24-> 31*/



/**						DON'T REMOVE The below 							*/



#define DIO_READ_CHANNEL_SID 			 0x00
#define DIO_WRITE_PORT_SID	 			 0x03
#define DIO_GET_VERSION_INFO_PORT_SID	 0x12

#define DIO_INSTANCE_ID    0



/* Configuration for Dio_GetVersionInfo function  */


/* The max numbers of pins */
#define MAX_NUM_PINS	32
#define MAX_NUM_PORTS	4


#define VENDOR_ID_AVR		3


#define VENDOR_ID	              VENDOR_ID_AVR
#define DIO_MODULE_ID             2
#define DIO_SW_MAJOR_VERSION      1
#define DIO_SW_MINOR_VERSION      0
#define DIO_SW_PATCH_VERSION      0








/* This global array that contains the ports values */
u8 Global_Port[MAX_NUM_PORTS];

/*                     function implementation 			                         */

/* Description : This function shall resd the value of specific channel           */
/*Inputs:																  */
/*		Dio_ChannelType 													  */
/*                        Numeric value from 0 upto 31                            */
/*                                                                                */
/*Outputs: 																  */
/*		Dio_LevelType														  */
/*					STD_LOW												  */
/*                    STD_HIGH                                                    */

/*[SRS_Dio_12008]:The Dio SWS shall define synchronous read/write services        */
/*[SWS_Dio_00026] The configuration process for Dio module shall provide symbolic names for
each configured DIO channel, port and group*/
/*[SWS_Dio_00133] :Returns the value of the specified DIO channel.                */
/*[SWS_Dio_00027] that get the value of the specific channel */
Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId )
{
	/*[SWS_Dio_00118] Dio module’s read functions shall return with the value '0' */
	/* Deafult value of the pin */
	Dio_LevelType DIO_Value = STD_LOW;
	uint8 Pin,Port;
	Std_ReturnType LocalError = E_OK;
	/*[SRS_BSW_00074]  ---->  Inavlid channel ID */
	#if DioDevErrorDetect == DET_ON 
	/* Check the input arguments */
	if ( ChannelId > MAX_NUM_PINS )
	{
		/*Call the *****Det****  Invalid input arguments */
		/* Set the local error to NOK */
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		LocalError = E_NOT_OK;
	}
	if ( Dio_Status == Dio_NOT_INIT)
	{
		/*Call the *****Det****  Dio is not initialized  */
		/* Set the local error to NOK */
		LocalError = E_NOT_OK;
	}
	#endif 
	if ( LocalError == E_OK  )
	{
		/* Get the Port value */
		Port = (uint8 )(ChannelId / 8) ;
		/* Read the pin value */
		Pin  = ChannelId % 8 ;
		/* Get the Value of the channel */
		switch (Port)
		{
			/*[SWS_Dio_00084]:the Dio module’s read functions shall provide the value of the output register, 
			when they are used on a channel which is configured as an output channel*/
			case PORT_A :
				if (GET_BIT(DDRA,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[PORT_A],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINA,Pin);
				}
			break;
			case PORT_B :
				if (GET_BIT(DDRB,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[PORT_B],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINB,Pin);
				}
			break;
			case PORT_C :
				if (GET_BIT(DDRC,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[PORT_C],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINC,Pin);
				}
			break;
			case PORT_D :
				if (GET_BIT(DDRD,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[PORT_D],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PIND,Pin);
				}
			break;
		}		/* End of the switch */
	}
	/* return the value of the channel or return the default value of the channel if there is an error */
/*[SWS_Dio_00027] :Returns the value of the specified DIO channel.                */
	return DIO_Value ;
}


/* Description : This function shall Write the value of specific port               */
/*Inputs:																    */
/*		PortId 													 		    */
/*              PORT_A                                                             */
/*              PORT_B                                                             */
/*              PORT_C                                                             */
/*              PORT_D                                                             */
/*		Level			   												   */
/*				Any numeric values from 0x00 upto 0xFF						   */
/*Outputs: 																   */
/*                   void                                                         */

/*[SWS_Dio_00136] function shall set the specified value for the specified port*/
/* [SWS_Dio_00035]When writing a port which is smaller than 
the Dio_PortLevelType using the Dio_WritePort function  the function shall ignore the MSB
when the argument  is passed, it is already casted to Dio_PortLevelType
*/
void Dio_WritePort ( Dio_PortType PortId , Dio_PortLevelType Level )
{
	Std_ReturnType LocalError =E_OK;
	uint8 sreg;
	u8 * Port;
	u8 * Ddr;
	/* [SWS_Dio_00075] --- > invalid port ID */
	/* Check DET enabled or not */
#if DioDevErrorDetect == DET_ON
	/* Check the input arguments */
	if ( PortId > PORT_D )
	{
		/*Call the *****Det****  Invalid input arguments */
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,
				DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
		/* Set the local error to NOK */
		LocalError = E_NOT_OK;
	}
	if ( Dio_Status == Dio_NOT_INIT)
	{
		/*Call the *****Det****  Dio is not initialized  */
		/* Set the local error to NOK */
		LocalError = E_NOT_OK;
	}
#endif 

	if( LocalError == E_OK )
	{
	/*[SWS_DIO_034] function shall set the specified value for the specified port.*/
		switch (PortId)
		{
			case PORT_A:
				Port = &PORTA:
				Ddr  = &DDRA ;
			break;
			case PORT_B:
				Port = &PORTB:
				Ddr  = &DDRB;
			break;
			case PORT_C:
				Port=&PORTC:
				Ddr  = &DDRC;
			break;
			case PORT_D:
				Port=&PORTD:
				Ddr  = &DDRD;
		}
		/* [SWS_Dio_00005] (Interruptible read-modify-write sequences are not allowed)*/
		/* Save global interrupt flag */
		sreg = SREG;
		/* Disable interrupts */
		_CLI();
/*[SWS_Dio_00108] ⌈The Dio_WritePort function shall have no effect on channels 
within this port which are configured as input channels.*/
		/* Set the values to the port */
		*Port = (u8)(*Ddr) & Level               ;
		Global_Port[PortId] =(u8)(*Ddr) & Level ;
		/* Restore global interrupt flag */
		SREG = sreg;
	}
}

/* [SWS_Dio_00139] Service to get the version information of this module.*/
void Dio_GetVersionInfo ( Std_VersionInfoType* VersionInfo )
{
	Std_ReturnType LocalError =E_OK;
	/* Check DET enabled or not */
#if DioDevErrorDetect == DET_ON
	/* Check the input arguments */
	if ( VersionInfo == NULL )
	{
		/*[SWS_Dio_00114] ----> check the input arguments is NUll Pointer */
		/*Call the *****Det****  NULL pointer  */
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,
				DIO_WRITE_PORT_SID, DIO_E_PARAM_POINTER);
		/* Set the local error to NOK */
		LocalError = E_NOT_OK;
	}
#endif 
if (LocalError == E_OK )
	{
		VersionInfo->vendorID         = VENDOR_ID	           ;
		VersionInfo->moduleID         = DIO_MODULE_ID          ;
		VersionInfo->sw_major_version = DIO_SW_MAJOR_VERSION   ;
		VersionInfo->sw_minor_version = DIO_SW_MINOR_VERSION   ;
		VersionInfo->sw_patch_version = DIO_SW_PATCH_VERSION   ;
	DIO_INSTANCE_ID
	}
	else 
	{
		/* Nothing */
	}
}



/************************** Team 5 **************************/
/*Authors :
			1)Ali Samir 
			2)Amr El-Noby
			3)Hazem Mekawy
			4)Mira Zekry
			5)Mariam El-Shakafi

Version : 1.0.0
Date:4/26/2020
*/


/*    this needed defines for functions 					*/
/*      1) Dio_ReadChannelGroup 								*/
/*      2) Dio_WriteChannelGroup 									*/


/**
 * @brief Reads the value of a specified channel group
 * 
 * @param ChannelGroupIdPtr is a pointer to struct containing group info (Port, mask, offset)
 * @return Dio_PortLevelType is the value of the group (a range from 0 to 255)
 *
 */

Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	/* Used to store SREG value before entering critical section */
	uint8 sreg;
	Dio_PortLevelType groupLevel;
	
	#if DioDevErrorDetect == DET_ON
	if ( NULL == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
	}
	if (!DIO_IS_CHANNEL_GROUP_VALID((ChannelGroupIdPtr->mask >> ChannelGroupIdPtr->offset))
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
	}
	#endif

	sereg = SREG;
	_CLI();
	groupLevel = (((*(ChannelGroupIdPtr->port))&(ChannelGroupIdPtr->mask)) >> (ChannelGroupIdPtr->offset));
	SREG = sreg;
	
	return groupLevel;

}


/**
 * @brief Writes values to a specified channel group
 * 
 * @param ChannelGroupIdPtr is a pointer to struct containing group info (Port, mask, offset)
 * @param Level contains the values to be written on the group
 *
 */
 
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level )
{
	/* Used to store SREG value before entering critical section */
	uint8 sreg;
	Dio_PortLevelType groupLevel;
	
	#if DioDevErrorDetect == DET_ON
	if ( NULL == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
	}
	if (!DIO_IS_CHANNEL_GROUP_VALID((ChannelGroupIdPtr->mask >> ChannelGroupIdPtr->offset))
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
	}
	#endif

	sereg = SREG;
	_CLI();
	*(ChannelGroupIdPtr->port) |= (Level<<(ChannelGroupIdPtr->offset))&(ChannelGroupIdPtr->mask);
	SREG = sreg;

}

