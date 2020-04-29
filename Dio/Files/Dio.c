#include "Dio.h"
#include "Dio_MemMap.h"
#include "Det.h"
#include "SchM_Dio.h"

/************************** Macros **************************/

#define CLEAR_BIT(reg, n)        ((reg) &= ~(1 << (n)))
#define SET_BIT(reg, n)          ((reg) |= 1 << (n))
#define GET_BIT(reg, n)          (((reg) >> (n)) & 1)

//#define CLEAR_BIT(reg, n)        (__asm__("Cbi reg, n"))
//#define SET_BIT(reg, n)          (__asm__("Sbi reg, n"))
//#define GET_BIT(reg, n)          (((reg) >> (n)) & 1)

/* This global array that contains the ports values */
u8 Global_Port[MAX_NUM_PORTS];

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
	
	#if DioDevErrorDetect == STD_ON
	if ( NULL == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
	}
	if (!DIO_IS_CHANNEL_GROUP_VALID((ChannelGroupIdPtr->mask >> ChannelGroupIdPtr->offset))
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
	}
	#endif

	sreg = SREG;
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
	
	#if DioDevErrorDetect == STD_ON
	if ( NULL == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
	}
	if (!DIO_IS_CHANNEL_GROUP_VALID((ChannelGroupIdPtr->mask >> ChannelGroupIdPtr->offset))
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP);
	}
	#endif

	sreg = SREG;
	_CLI();
	*(ChannelGroupIdPtr->port) |= (Level<<(ChannelGroupIdPtr->offset))&(ChannelGroupIdPtr->mask);
	SREG = sreg;

}

/************************ Team 4 ****************************/
/*Authors :
			1) Mina Helmi
			2) Kariman Zakzouk
			3) Mahmoud Hamdy
			4) Sara Abdallah
			5) Mohamed Nafea
			6) Hesham El Sherbini
			7) Muhammed Farag
Version : 1.0.0
Date    : 4/28/2020
*/

/************************************************************************************
 * Service Name: Dio_ReadPort
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortId - ID of DIO Port
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: Function to Return the level of all channels of that port
 ************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
  Dio_PortLevelType PortLevel;
  Std_ReturnType PortError = E_OK;
  uint8 sreg;
  
  /* Checking if Dio Develeopment Error Detection is Enabled */
  /* [SWS_Dio_00118] If development errors are enabled and an error ocurred 
  the Dio module’s read functions shall return with the value '0'. */
#if DioDevErrorDetect == STD_ON
  /* Validate Passed Port ID */
  if( PortId >= MAX_NUM_PORTS )
  {
    /* 
     * Invalid Port Requested
     * Reporting DIO_E_PARAM_INVALID_PORT_ID to DET 
     * Det_ReportError(DIO_E_PARAM_INVALID_PORT_ID)
     */
     Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
     
     /* Assing 'E_NOT_OK' to 'PortError' indicating the occurance of Port Error */
     PortError = E_NOT_OK;
  }
  else
  {
    /* Do Nothing */
  }
#endif

  if( E_OK == PortError )
  {
    /* [SWS_Dio_00005] The Dio module's read and write services shall ensure for all services,
     * that the data is consistent (Interruptible read-modify-write sequences are not allowed) */
   
    /* Save global interrupt flag */
    sreg = SREG;
    /* Disable interrupts */
    _CLI();

    /* Checking Port Is needed to be Read */
    switch (PortId) 
    {
      /* Assign the Value of the corresponding PIN Register to 'PortLevel' */
      case DIO_PORT_A:
         PortLevel = PINA;
      break;
      case DIO_PORT_B:
         PortLevel = PINB;
      break;
      case DIO_PORT_C:
         PortLevel = PINC;
      break;
      case DIO_PORT_D:
         PortLevel = PIND;
      break;
    }
    
    /* Restore global interrupt flag */
    SREG = sreg;
  }
  else
  {
     /* [SWS_Dio_00118] If development errors are enabled and an error ocurred the Dio
     *  module's read functions shall return with the value '0'. */
     return PortLevel = 0;
  }
  
  return PortLevel;
}


/************************************************************************************
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - A numeric value from 0 to 31 corresponding to the required pin.
 *                  Level - Value of the pin:
 *                          STD_LOW: Low level signal,
 *                          STD_HIGH: High level signal
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 ************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	Std_ReturnType LocalError = E_OK;
	uint8 Pin, PortId;
	uint8* Ddr, *Port;
	uint8 sreg;

#if DioDevErrorDetect == STD_ON
	if ( MAX_NUM_PINS <= ChannelId )
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		LocalError = E_NOT_OK;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if( LocalError == E_OK )
	{
		/* Get the Port value */
		PortId = (uint8 )(ChannelId / 8) ;
		/* Read the pin value */
		Pin  = ChannelId % 8 ;

		switch (PortId)
		{
		case DIO_PORT_A:
			Port = &PORTA:
			Ddr  = &DDRA ;
		break;

		case DIO_PORT_B:
			Port = &PORTB:
			Ddr  = &DDRB;
		break;

		case DIO_PORT_C:
			Port = &PORTC:
			Ddr  = &DDRC;
		break;

		case DIO_PORT_D:
			Port = &PORTD:
			Ddr  = &DDRD;
		break;
		}

		/* [SWS_Dio_00028] check if the specified channel is configured as an output channel,
		 * the Dio_WriteChannel function shall set the specified Level for the specified channel */
		if( GET_BIT(Ddr, Pin) == OUTPUT )
		{
			/* [SWS_Dio_00005] The Dio module’s read and write services shall ensure for all services,
			that the data is consistent (Interruptible read-modify-write sequences are not allowed) */

			/* Save global interrupt flag */
			sreg = SREG;
			/* Disable interrupts */
			_CLI();

			if( Level == STD_HIGH )
			{
				SET_BIT(Port, Pin );
			}
			else if ( Level == STD_LOW )
			{
				CLEAR_BIT(Port, Pin );
			}
			else
			{
				/* No Action Required */
			}
			/* Restore global interrupt flag */
			SREG = sreg;
		}
		else
		{
			/* [SWS_Dio_00029] If the specified channel is configured as an input channel, the
			 * Dio_WriteChannel function shall have no influence on the physical output.
			 *
			 * [SWS_Dio_00079] check if the specified channel is configured as an input channel, the
			 * Dio_WriteChannel function shall have no influence on the result of the next Read-Service */
		}
	}
	else
	{
		/* [SWS_Dio_00119] If development errors are enabled and an error ocurred,
		 * the Dio module write function shall NOT process the write command */
	}
}


/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - A numeric value from 0 to 31 corresponding to the required pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: Function to Return the level of all channels of that port
 *
 * Return value: Dio_LevelType:
 *               STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
 *               STD_LOW: The physical level of the corresponding Pin is STD_LOW.
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel
 *              and return the level of the channel after flip.
 ************************************************************************************/
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId)
{
	/*This Local Variable will hold the return value*/
	Dio_LevelType Local_LevelType;
	/*This local variable will hold error status, if an error is found, the function will not resume*/
	Std_ReturnType localError = E_OK;
	
	/*As per the standard, if the DioDevErrorDetect parameter is enabled in the configuration
	then check that the channelID parameter is valid
	the “ChannelId” parameter is invalid, the functions shall report the error code DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.*/
#if DioDevErrorDetect == STD_ON
	/*If channel ID is greater than the highest pin number, report error and set local error variable to false so that function won't resume*/
	if ( MAX_NUM_PINS <= ChannelId )
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		localError = E_NOT_OK;
	}
#endif

	/*If local error is still reporting OK, then go on with the flip process as AUTOSAR
	standard stated here*/
	/*[SWS_Dio_00191] If the specified channel is configured as an output channel, the Dio_FlipChannel function shall read level of the channel (requirements [SWS_Dio_00083] & [SWS_Dio_00084] are applicable) and invert it, then write the inverted level to the channel. The return value shall be the inverted level of the specified channel.
		[SWS_Dio_00192] If the specified channel is configured as an input channel, the Dio_FlipChannel function shall have no influence on the physical output. The return value shall be the level of the specified channel.
		[SWS_Dio_00193] If the specified channel is configured as an input channel, the Dio_FlipChannel function shall have no influence on the result of the next Read-Service.*/
	if (LocalError == E_OK)
	{
		/*Get Reading of channel using the defined read channel method before*/
		Local_LevelType = Dio_ReadChannel(ChannelId);
		
		/*According to returned level type, do the desired action*/
		/*If pin is Output High, switch to Output low*/
		if (Local_LevelType == STD_HIGH)
		{
			/*Write output low value on the desired pin*/
			Dio_WriteChannel(ChannelId, STD_LOW);
			/*Store the written value in the level type that will be returned to show to the user*/
			Local_LevelType = Dio_ReadChannel(ChannelId);
		}
		/*If pin is output low, switch to output high*/
		else if (Local_LevelType == STD_LOW)
		{
			/*Write output High value on the desired pin*/
			Dio_WriteChannel(ChannelId, STD_HIGH);
			/*Store the written value in the level type that will be returned to show to the user*/
			Local_LevelType = Dio_ReadChannel(ChannelId);
		}
		/*Else if type is input, return its reading as it is, so we will do nothing*/
		else
		{
			/*Do nothing*/
		}
	}
   else
   {
      /* [SWS_Dio_00118] If development errors are enabled and an error ocurred the Dio
      *  module's read functions shall return with the value '0'. */
      Local_LevelType = 0;
   }
   
   /*Return level type*/
   return Local_LevelType;
}
/************************************************************/



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
	#if DIO_DevErrorDetect_API == STD_OFF 
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
			case DIO_DIO_PORT_A :
				if (GET_BIT(DDRA,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[DIO_DIO_PORT_B],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINA,Pin);
				}
			break;
			case DIO_DIO_PORT_B :
				if (GET_BIT(DDRB,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[DIO_DIO_PORT_B],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINB,Pin);
				}
			break;
			case DIO_DIO_PORT_C :
				if (GET_BIT(DDRC,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[DIO_DIO_PORT_C],Pin);
				}
				else 
				{
					DIO_Value = GET_BIT(PINC,Pin);
				}
			break;
			case DIO_DIO_PORT_D :
				if (GET_BIT(DDRD,Pin) == OUTPUT)
				{
					DIO_Value =GET_BIT(Global_Port[DIO_DIO_PORT_D],Pin);
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
/*              DIO_DIO_DIO_DIO_PORT_B                                                             */
/*              DIO_DIO_PORT_B                                                             */
/*              DIO_DIO_PORT_C                                                             */
/*              DIO_DIO_DIO_PORT_D                                                             */
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
	u8 PrevPortVal;
	/* [SWS_Dio_00075] --- > invalid port ID */
	/* Check DET enabled or not */
#if DIO_DevErrorDetect_API == STD_ON
	/* Check the input arguments */
	if ( PortId > DIO_DIO_PORT_D )
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
			case DIO_DIO_PORT_A:
				Port = &PORTA:
				Ddr  = &DDRA ;
			break;
			case DIO_DIO_PORT_B:
				Port = &PORTB:
				Ddr  = &DDRB;
			break;
			case DIO_DIO_PORT_C:
				Port = &PORTC:
				Ddr  = &DDRC;
			break;
			case DIO_DIO_PORT_D:
				Port = &PORTD:
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
		PrevPortVal = *Port                ;
		PrevPortVal &= ~(*Ddr)             ;
		PrevPortVal |= ((u8)(*Ddr) & Level);
		*PORT = PrevPortVal               ;
		Global_Port[PortId] = PrevPortVal ;
		/* Restore global interrupt flag */
		SREG = sreg;
	}
}

/* [SWS_Dio_00139] Service to get the version information of this module.*/
void Dio_GetVersionInfo ( Std_VersionInfoType* VersionInfo )
{
	Std_ReturnType LocalError =E_OK;
	/* Check DET enabled or not */
#if DIO_DevErrorDetect_API == STD_ON
	/* Check the input arguments */
	if ( VersionInfo == NULL )
	{
		/*[SWS_Dio_00114] ----> check the input arguments is NUll Pointer */
		/*Call the *****Det****  NULL pointer  */
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID, DIO_WRITE_PORT_SID, DIO_E_PARAM_POINTER);
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
