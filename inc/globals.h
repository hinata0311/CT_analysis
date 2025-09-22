#ifndef GLOBALS_h
#define GLOBALS_h

//#define _INCLUDE_EUDAQ_CONTROL  // -- specifies the operation mode:  coment this line for standalone compilation (when eudaq framework is not needed)

// DAQ setting
#define DAC_BOARD_ADC_MAX_COUNTS  65536
#define RAW_DATA_BUFFER_SIZE		 2304 	// chars
#define HEADER_SIZE				 12 		// chars

#define CE65_D_MX_SIZE			 1152 	// pixels -> for now this is aliasing V2
#define CE65_V2_MX_SIZE			 1152 	// pixels

#define ENABLE_EXT_TRIGG_MODE		0
#define X_MX_SIZE  48
#define Y_MX_SIZE  24

#define READY_EVENTS_QUE_SIZE	100000
#define TEMP_PACKAGE_QUE_SIZE	100000
#define ENABLE_EUDAC_COMMUNICATION 1
#define EUDAC_ADDRES_AND_PORT  "tcp://rpi-its3-6:44000"

#define DEFAULT_RUN_NAME_PREFIX  "TB_run_"

const int VERBOSITY_LEVEL = 2; //(0-ERR, 1-WARN, 2-INFO, 3-CNTR, 4 -DEB)

const int DAC_PROTO_MAX_CODE = 256; 
const int N_DAC_SAMPLES = 200; 
const int TIME_BETWEEN_SUBSEQUENT_DAC_SAMPLES = 5; //us
const int DAC_MONITOR_PERIOD = 5; //s
const int DAC_SCAN_PERIOD = 60; //s*DAC_MONITOR_PERIOD

#endif