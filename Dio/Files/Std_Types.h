/********************************************************************************
**  FILENAME     : Std_Types.h                                                **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-04-22                                                 **
**                                                                            **
**  PLATFORM     :  AVR                                                       **
**                                                                            **
**  AUTHOR       : Nada Mohamed                                               **
**                                                                            **                                                                           **
**  DESCRIPTION  : Dio standard type  header file                             **
**                                                                            **
**  SPECIFICATION(S) : Standard types , AUTOSAR Release 4.3.1                 **
*******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Platform_Types.h"
#include "Compiler.h"

typedef uint8 Std_ReturnType ;
/*  request the version of a BSW module */
typedef struct
{
    uint16 vendorID        ;
    uint16 moduleID        ;
    uint8 sw_major_version ;
    uint8 sw_minor_version ;
    uint8 sw_patch_version ;

}Std_VersionInfoType;

/*********************************************************************************************
 * Description  :- These are the possible levels a DIO channel can have (input or output)
 * Requirment   :- SWS_Dio_00185
 *********************************************************************************************/
#define STD_HIGH      0x01U /* Physical state 5V or 3.3V */
#define STD_LOW       0x00U /* Physical state 0V */


#define E_OK          (Std_ReturnType)0x00U
#define E_NOT_OK      (Std_ReturnType)0x01U

#define STD_ON        0x01U
#define STD_OFF       0x00U

#define STD_ACTIVE    0x01U
#define STD_IDLE      0x00U

#endif /*STD_TYPES_H_ */
