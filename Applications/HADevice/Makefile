APP_NAME = HADevice
PROJECT_NAME = ZAPPSI
CONFIG_NAME = All_StdlinkSec_Sam3sEk_At91sam3s4c_Rf231_64Mhz_Iar

#PROJECT_NAME = PC_PS_ZAppSIHost
#CONFIG_NAME = All_StdlinkSec_PC_Win_Gcc

all:
	make -C makefiles/$(PROJECT_NAME) -f Makefile_$(CONFIG_NAME) all APP_NAME=$(APP_NAME)

clean:
	make -C makefiles/$(PROJECT_NAME) -f Makefile_$(CONFIG_NAME) clean APP_NAME=$(APP_NAME)
