#include "Det.h"


/**
 * @brief Used to report error by other modules
 * 
 * @param ModuleId is the ID of the module reporting the error
 * @param InstanceId is The identifier of the index based instance of a module, starting
 *        from 0, If the module is a single instance module it shall pass 0 as the InstanceId. 
 * @param ApiId is the ID of the API reporting the error
 * @param ErrorId is the ID of the error reported
 *
 */
void Det_ReportError( uint16 ModuleId,
                      uint8 InstanceId,
                      uint8 ApiId,
					  uint8 ErrorId )
{
	while(1)
	{

	}
}