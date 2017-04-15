// This is automatically generated file, do not edit

#if !defined(BOARD_SAM3S_EK) && !defined(BOARD_CUSTOM_3) && !defined(BOARD_SAM7X_EK) && !defined(BOARD_RCB) && !defined(BOARD_SIMULATOR) && !defined(BOARD_REB_CBB) && !defined(BOARD_RAVEN) && !defined(BOARD_AVR32_EVK1105) && !defined(BOARD_XPLAIN) && !defined(BOARD_STK600) && !defined(BOARD_PC) && !defined(BOARD_MESHBEAN) && !defined(BOARD_USB_DONGLE)
#  error invalid BOARD
#endif
#ifdef BOARD_SAM3S_EK
#  if !defined(AT91SAM3S4C)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_CUSTOM_3
#  if !defined(AT91SAM3S4C)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_SAM7X_EK
#  if !defined(AT91SAM7X256)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_RCB
#  if !defined(ATMEGA128RFA1) && !defined(ATMEGA256RFR2) && !defined(ATMEGA2564RFR2) && !defined(ATMEGA1281)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_SIMULATOR
#  if !defined(SIMULATOR)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_REB_CBB
#  if !defined(ATXMEGA256A3)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_RAVEN
#  if !defined(ATMEGA1284)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_AVR32_EVK1105
#  if !defined(AT32UC3A0512)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_XPLAIN
#  if !defined(ATXMEGA128A1) && !defined(ATXMEGA128B1)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_STK600
#  if !defined(ATXMEGA256A3) && !defined(ATXMEGA128A1) && !defined(ATXMEGA256D3) && !defined(ATMEGA128RFA1) && !defined(ATMEGA256RFR2) && !defined(ATMEGA2564RFR2)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_PC
#  if !defined(WIN)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_MESHBEAN
#  if !defined(ATMEGA1281) && !defined(ATMEGA2561)
#    error invalid HAL
#  endif
#endif
#ifdef BOARD_USB_DONGLE
#  if !defined(AT90USB1287)
#    error invalid HAL
#  endif
#endif
#if !defined(LIB_TYPE_HALSE)
#  if !defined(STACK_TYPE_ALL) && !defined(STACK_TYPE_COORDINATOR) && !defined(STACK_TYPE_ROUTER) && !defined(STACK_TYPE_ENDDEVICE)
#    error invalid STACK_TYPE
#  endif
#  if !defined(STANDARD_SECURITY_MODE) && !defined(DUMMY_ECC_SECURITY_MODE) && !defined(HIGH_SECURITY_MODE) && !defined(NO_SECURITY_MODE) && !defined(CERTICOM_SECURITY_MODE)
#    error invalid SECURITY_MODE
#  endif
#  ifdef BOARD_SAM3S_EK
#    if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_16MHz) && !defined(HAL_64MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_CUSTOM_3
#    if !defined(CUSTOMRF3)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_16MHz) && !defined(HAL_64MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_SAM7X_EK
#    if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_48MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_RCB
#    if !defined(ATMEGA128RFA1) && !defined(ATMEGA256RFR2) && !defined(ATMEGA2564RFR2) && !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_16MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_SIMULATOR
#    if !defined(AT86RF231)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_0MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_REB_CBB
#    if !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF233) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_RAVEN
#    if !defined(AT86RF230B)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_AVR32_EVK1105
#    if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_48MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_XPLAIN
#    if !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF233) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_STK600
#    if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212) && !defined(ATMEGA128RFA1) && !defined(ATMEGA256RFR2) && !defined(ATMEGA2564RFR2)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_PC
#  endif
#  ifdef BOARD_MESHBEAN
#    if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_4MHz) && !defined(HAL_8MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#  ifdef BOARD_USB_DONGLE
#    if !defined(AT86RF230B)
#      error invalid RFCHIP
#    endif
#    if !defined(HAL_8MHz)
#      error invalid HAL_FREQUENCY
#    endif
#  endif
#endif

#if defined(__GNUC__)
#  if defined(LIB_TYPE_ZCL)
#    ifdef STACK_TYPE_ALL
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2563RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2#      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ALL
#    ifdef STACK_TYPE_COORDINATOR
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_COORDINATOR
#    ifdef STACK_TYPE_ROUTER
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2#      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ROUTER
#    ifdef STACK_TYPE_ENDDEVICE
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2#      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ENDDEVICE
#  elif defined(LIB_TYPE_HALSE)
#    ifdef AT91SAM3S4C
#      include <MakerulesHalSe_At91sam3s4c_Gcc.h>
#    endif
#    ifdef ATXMEGA256A3
#      include <MakerulesHalSe_Atxmega256a3_Gcc.h>
#    endif
#    ifdef ATMEGA128RFA1
#      include <MakerulesHalSe_Atmega128rfa1_Gcc.h>
#    endif
#    ifdef ATXMEGA128A1
#      include <MakerulesHalSe_Atxmega128a1_Gcc.h>
#    endif
#    ifdef ATMEGA2561
#      include <MakerulesHalSe_Atmega2561_Gcc.h>
#    endif
#    ifdef AT32UC3A0512
#      include <MakerulesHalSe_At32uc3a0512_Gcc.h>
#    endif
#    ifdef SIMULATOR
#      include <MakerulesHalSe_Sim_Gcc.h>
#    endif
#    ifdef AT91SAM7X256
#      include <MakerulesHalSe_At91sam7x256_Gcc.h>
#    endif
#    ifdef ATXMEGA256D3
#      include <MakerulesHalSe_Atxmega256d3_Gcc.h>
#    endif
#    ifdef ATMEGA1284
#      include <MakerulesHalSe_Atmega1284_Gcc.h>
#    endif
#    ifdef AT90USB1287
#      include <MakerulesHalSe_At90usb1287_Gcc.h>
#    endif
#    ifdef ATMEGA1281
#      include <MakerulesHalSe_Atmega1281_Gcc.h>
#    endif
#    ifdef ATMEGA256RFR2
#      include <MakerulesHalSe_Atmega256rfr2_Gcc.h>
#    endif
#  else // LIB_TYPE_BITCLOUD
#    ifdef STACK_TYPE_ALL
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ALL
#    ifdef STACK_TYPE_COORDINATOR
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_COORDINATOR
#    ifdef STACK_TYPE_ROUTER
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ROUTER
#    ifdef STACK_TYPE_ENDDEVICE
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_Sec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_Sec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_HighSec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_HighSec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Gcc.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Gcc.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Sim_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf212_Gcc.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Gcc.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Gcc.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf212_Gcc.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Gcc.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Gcc.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf233_Gcc.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Gcc.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_CustomRf3_Gcc.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Gcc.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Gcc.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Gcc.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ENDDEVICE
#  endif
#endif // GCC
#if defined(__ICCAVR__) || defined(__ICCARM__) || defined(__ICCAVR32__)
#  if defined(LIB_TYPE_ZCL)
#    ifdef STACK_TYPE_ALL
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_All_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_All_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_All_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ALL
#    ifdef STACK_TYPE_COORDINATOR
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_COORDINATOR
#    ifdef STACK_TYPE_ROUTER
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_Router_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_Router_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_Router_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ROUTER
#    ifdef STACK_TYPE_ENDDEVICE
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesZcl_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesZcl_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesZcl_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ENDDEVICE
#  elif defined(LIB_TYPE_HALSE)
#    ifdef AT91SAM3S4C
#      include <MakerulesHalSe_At91sam3s4c_Iar.h>
#    endif
#    ifdef ATXMEGA256A3
#      include <MakerulesHalSe_Atxmega256a3_Iar.h>
#    endif
#    ifdef ATMEGA128RFA1
#      include <MakerulesHalSe_Atmega128rfa1_Iar.h>
#    endif
#    ifdef ATXMEGA128A1
#      include <MakerulesHalSe_Atxmega128a1_Iar.h>
#    endif
#    ifdef ATMEGA2561
#      include <MakerulesHalSe_Atmega2561_Iar.h>
#    endif
#    ifdef AT32UC3A0512
#      include <MakerulesHalSe_At32uc3a0512_Iar.h>
#    endif
#    ifdef SIMULATOR
#      include <MakerulesHalSe_Sim_Iar.h>
#    endif
#    ifdef AT91SAM7X256
#      include <MakerulesHalSe_At91sam7x256_Iar.h>
#    endif
#    ifdef ATXMEGA256D3
#      include <MakerulesHalSe_Atxmega256d3_Iar.h>
#    endif
#    ifdef ATMEGA1284
#      include <MakerulesHalSe_Atmega1284_Iar.h>
#    endif
#    ifdef AT90USB1287
#      include <MakerulesHalSe_At90usb1287_Iar.h>
#    endif
#    ifdef ATMEGA1281
#      include <MakerulesHalSe_Atmega1281_Iar.h>
#    endif
#    ifdef ATMEGA256RFR2
#      include <MakerulesHalSe_Atmega256rfr2_Iar.h>
#    endif
#  else // LIB_TYPE_BITCLOUD
#    ifdef STACK_TYPE_ALL
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_All_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_All_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_All_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_All_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_All_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_All_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ALL
#    ifdef STACK_TYPE_COORDINATOR
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Coordinator_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_COORDINATOR
#    ifdef STACK_TYPE_ROUTER
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_Router_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_Router_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_Router_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ROUTER
#    ifdef STACK_TYPE_ENDDEVICE
#      ifdef STANDARD_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_Sec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_Sec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // STANDARD_SECURITY_MODE
#      ifdef DUMMY_ECC_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // DUMMY_ECC_SECURITY_MODE
#      ifdef HIGH_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_HighSec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_HighSec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // HIGH_SECURITY_MODE
#      ifdef NO_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // NO_SECURITY_MODE
#      ifdef CERTICOM_SECURITY_MODE
#        ifdef AT91SAM3S4C
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#          endif
#        endif // AT91SAM3S4C
#        ifdef ATXMEGA256A3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256A3
#        ifdef ATMEGA128RFA1
#          ifdef ATMEGA128RFA1
#            include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#          endif
#        endif // ATMEGA128RFA1
#        ifdef ATXMEGA128A1
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA128A1
#        ifdef ATMEGA2561
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#          endif
#        endif // ATMEGA2561
#        ifdef AT32UC3A0512
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#          endif
#        endif // AT32UC3A0512
#        ifdef SIMULATOR
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Sim_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Sim_Rf212_Iar.h>
#          endif
#        endif // SIMULATOR
#        ifdef AT91SAM7X256
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#          endif
#        endif // AT91SAM7X256
#        ifdef ATXMEGA256D3
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#          endif
#        endif // ATXMEGA256D3
#        ifdef ATMEGA1284
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1284
#        ifdef AT90USB1287
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf212_Iar.h>
#          endif
#        endif // AT90USB1287
#        ifdef ATMEGA1281
#          ifdef AT86RF231
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#          endif
#          ifdef AT86RF230
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#          endif
#          ifdef AT86RF233
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf233_Iar.h>
#          endif
#          ifdef AT86RF230B
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#          endif
#          ifdef CUSTOMRF3
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_CustomRf3_Iar.h>
#          endif
#          ifdef AT86RF212
#            include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#          endif
#        endif // ATMEGA1281
#        ifdef ATMEGA256RFR2
#          ifdef ATMEGA256RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega256rfr2_Atmega256rfr2_Iar.h>
#          endif
#        endif // ATMEGA256RFR2      
#        ifdef ATMEGA2564RFR2
#          ifdef ATMEGA2564RFR2
#            include <MakerulesBc_EndDevice_SESec_Atmega2564rfr2_Atmega2564rfr2_Iar.h>
#          endif
#        endif // ATMEGA2564RFR2
#      endif // CERTICOM_SECURITY_MODE
#    endif // STACK_TYPE_ENDDEVICE
#  endif
#endif // IAR
