/*********************************************************************************************//**
\file N_Hac_Bindings.h

\brief Binds actual N_Hac functions with its implementation 

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
***************************************************************************************************/
#ifndef N_HAC_BINDINGS_H
#define N_HAC_BINDINGS_H

// N_Hac
#define N_Hac_RegisterEndpoint N_Hac_RegisterEndpoint_Impl

// N_PacketDistributor
#define N_PacketDistributor_RegisterEndpoint N_PacketDistributor_RegisterEndpoint_Impl

#endif //N_HAC_BINDINGS_H
