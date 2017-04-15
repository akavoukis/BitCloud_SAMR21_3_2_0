/************************************************************************//**
  \file WSNZclManger.h

  \brief
    ZCL Manger interface declaration

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    19.04.10 A. Razinkov - Created.
******************************************************************************/

#ifndef WSNZCLMANAGER_H_
#define WSNZCLMANAGER_H_

#if APP_USE_OTAU == 1

/******************************************************************************
                    Includes section
******************************************************************************/

/******************************************************************************
                    Defines section
******************************************************************************/
#define APP_OTAU_CLUSTER_ENDPOINT 0x0B
#define APP_OTAU_SOFTWARE_VERSION    CCPU_TO_LE32(0x1CEDFACE);

/******************************************************************************
                    Global variables section
******************************************************************************/

/******************************************************************************
                    Functions prototypes section
******************************************************************************/

/*******************************************************************************
  Description: ZCL Manager initialization
  Parameters:  none
  Returns:     none
*******************************************************************************/
void appZclManagerInit(void);

/*******************************************************************************
  Description: Activates ZCL OTAU component
  Parameters:  none
  Returns:     none
*******************************************************************************/
void runOtauService(void);

#endif // APP_USE_OTAU == 1

#endif /* WSNZCLMANAGER_H_ */
// eof WSNZclManger.h
