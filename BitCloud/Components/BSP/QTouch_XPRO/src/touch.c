/**************************************************************************//**
\file  touch.c

\brief Implementation of Touch module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
   14.08.14 Kanchana - Created.
*******************************************************************************/

/*----------------------------------------------------------------------------
*                               include files
*  ----------------------------------------------------------------------------*/
#ifdef BOARD_QTOUCH_XPRO
/**
 * Includes for Touch Library.
 */
#include "touch_api_ptc.h"
#include "atsamr21.h"

/*----------------------------------------------------------------------------
*                           manifest constants
*  ----------------------------------------------------------------------------*/
#define   DEF_MUTLCAP_CAL_SEQ1_COUNT            8
#define   DEF_MUTLCAP_CAL_SEQ2_COUNT            4
#define   DEF_MUTLCAP_CC_CAL_CLK_PRESCALE       PRSC_DIV_SEL_1
#define   DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR     RSEL_VAL_0
#define   DEF_MUTLCAP_QUICK_REBURST_ENABLE      1u
   /*
#define   DEF_SELFCAP_CAL_SEQ1_COUNT	8
#define   DEF_SELFCAP_CAL_SEQ2_COUNT	4
#define   DEF_SELFCAP_CC_CAL_CLK_PRESCALE PRSC_DIV_SEL_8
#define   DEF_SELFCAP_CC_CAL_SENSE_RESISTOR RSEL_VAL_100
#define DEF_SELFCAP_QUICK_REBURST_ENABLE 1u
   */

/*----------------------------------------------------------------------------
*                                   macros
*  ----------------------------------------------------------------------------*/

#define PTC_GCLK_ID 0x22
#define PTC_APBC_BITMASK (1u << 19u)

/*----------------------------------------------------------------------------
*                           type definitions
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                           Structure Declarations
*  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
*                               global variables
*  ----------------------------------------------------------------------------*/
/* ! QTouch Library Timing info. */
touch_time_t touch_time;

/**
 * Mutual Cap sensors measured data pointer.
 * Note: This pointer is initialized by the QTouch library once the
 * touch_mutlcap_sensors_init API is called. */
touch_measure_data_t *p_mutlcap_measure_data = NULL;

/**
 * Self Cap sensors measured data pointer.
 * Note: This pointer is initialized by the QTouch library once the
 * touch_selfcap_sensors_init API is called. */
touch_measure_data_t *p_selfcap_measure_data = NULL;

/*----------------------------------------------------------------------------
*                               static variables
*  ----------------------------------------------------------------------------*/

/**
 * Mutual Cap Data block provided as input to Touch library.
 */
static uint8_t mutlcap_data_blk[PRIV_MUTLCAP_DATA_BLK_SIZE];

/**
 * Mutual Cap Sensor Pins Info.
 */

uint16_t mutlcap_xy_nodes[DEF_MUTLCAP_NUM_CHANNELS * 2] = {DEF_MUTLCAP_NODES};

gain_t mutlcap_gain_per_node[DEF_MUTLCAP_NUM_CHANNELS] = {DEF_MUTLCAP_GAIN_PER_NODE};

rsel_val_t mutlcap_resistor_per_node[DEF_MUTLCAP_NUM_CHANNELS] = 
{
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
   DEF_MUTLCAP_SENSE_RESISTOR,  
  DEF_MUTLCAP_SENSE_RESISTOR,

#if DEF_MUTLCAP_NUM_CHANNELS > 8  
 DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,  
  DEF_MUTLCAP_SENSE_RESISTOR,  
#endif
#if DEF_MUTLCAP_NUM_CHANNELS >= 16  
 DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,
  DEF_MUTLCAP_SENSE_RESISTOR,  
  DEF_MUTLCAP_SENSE_RESISTOR,  
#endif
};

prsc_div_sel_t mutlcap_prsc_per_node[DEF_MUTLCAP_NUM_CHANNELS] = 
{
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
 DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
   DEF_MUTLCAP_CLK_PRESCALE,  
  DEF_MUTLCAP_CLK_PRESCALE,

#if DEF_MUTLCAP_NUM_CHANNELS > 8  
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,  
  DEF_MUTLCAP_CLK_PRESCALE,  
#endif
#if DEF_MUTLCAP_NUM_CHANNELS >= 16  
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,
  DEF_MUTLCAP_CLK_PRESCALE,  
  DEF_MUTLCAP_CLK_PRESCALE,  
#endif
};

prsc_div_sel_t mutlcap_boot_prsc_per_node[DEF_MUTLCAP_NUM_CHANNELS] = 
{
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
 DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
 DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
   DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,  
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,

#if DEF_MUTLCAP_NUM_CHANNELS > 8  
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,  
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE, 
#endif
#if DEF_MUTLCAP_NUM_CHANNELS >= 16  
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE,  
  DEF_MUTLCAP_CC_CAL_CLK_PRESCALE, 
#endif
};

rsel_val_t mutlcap_boot_resistor_per_node[DEF_MUTLCAP_NUM_CHANNELS] = 
{ 
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
   DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,  
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,

#if DEF_MUTLCAP_NUM_CHANNELS > 8  
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,  
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
#endif
#if DEF_MUTLCAP_NUM_CHANNELS >= 16  
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,  
  DEF_MUTLCAP_CC_CAL_SENSE_RESISTOR,
#endif
  
};
freq_hop_sel_t mutlcap_freq_hops[3u] = {DEF_MUTLCAP_HOP_FREQS};

/**
 * Mutual Cap Configuration structure provided as input to Touch Library.
 *
 * Note: Use the touch.h configuration header file to fill in
 * the elements of this structure.  DO NOT modify any of the input values
 * directly in this structure.
 */
static touch_mutlcap_config_t mutlcap_config = {
	DEF_MUTLCAP_NUM_CHANNELS,       /* Mutual Cap number of channels. */
	DEF_MUTLCAP_NUM_SENSORS,        /* Mutual Cap number of sensors. */
	DEF_MUTLCAP_NUM_ROTORS_SLIDERS, /* Mutual Cap number of rotors and
	                                 * sliders. */

	/* Mutual Cap GLOBAL SENSOR CONFIGURATION INFO. */
	{
		DEF_MUTLCAP_DI,         /* uint8_t  di; Sensor detect
		                         * integration (DI) limit. */

		/* Interchanging Negative and Positive Drift rate, since Signal
		 * increases on Touch. */
		DEF_MUTLCAP_ATCH_DRIFT_RATE, /* uint8_t  neg_drift_rate; Sensor
		                              * negative drift rate. */
		DEF_MUTLCAP_TCH_DRIFT_RATE, /* uint8_t  pos_drift_rate; Sensor
		                             * positive drift rate. */
		DEF_MUTLCAP_MAX_ON_DURATION, /* uint8_t  max_on_duration; Sensor
		                              * maximum on duration. */
		DEF_MUTLCAP_DRIFT_HOLD_TIME, /* uint8_t  drift_hold_time; Sensor
		                              * drift hold time. */
		DEF_MUTLCAP_ATCH_RECAL_DELAY,   /* uint8_t  pos_recal_delay;
		                                 * Sensor positive recalibration
		                                 * delay. */
		DEF_MUTLCAP_CAL_SEQ1_COUNT,
		DEF_MUTLCAP_CAL_SEQ2_COUNT,
		DEF_MUTLCAP_ATCH_RECAL_THRESHOLD, /* recal_threshold_t
		                                   * recal_threshold; Sensor
		                                   * recalibration threshold. */
		DEF_MUTLCAP_TOUCH_POSTPROCESS_MODE,
		DEF_MUTLCAP_FREQ_AUTO_TUNE_SIGNAL_STABILITY_LIMIT,
		DEF_MUTLCAP_FREQ_AUTO_TUNE_IN_CNT,
		DEF_MUTLCAP_NOISE_MEAS_SIGNAL_STABILITY_LIMIT, /* signal
		                                                *stability */
		DEF_MUTLCAP_NOISE_LIMIT,
		DEF_MUTLCAP_LOCKOUT_SEL,
		DEF_MUTLCAP_LOCKOUT_CNTDOWN,
	},
	{
		mutlcap_gain_per_node,  /* Mutual Cap channel gain setting. */
		DEF_MUTLCAP_FREQ_MODE, /* Mutual Cap noise counter measure
		                        * enable/disable. */
		mutlcap_prsc_per_node,
		mutlcap_resistor_per_node,
		mutlcap_boot_prsc_per_node,
		mutlcap_boot_resistor_per_node,
		mutlcap_freq_hops,
		DEF_MUTLCAP_FILTER_LEVEL, /* Mutual Cap filter level setting. */
		DEF_MUTLCAP_AUTO_OS,    /* Mutual Cap auto oversamples setting.
		                        **/
	},
	mutlcap_data_blk,               /* Mutual Cap data block index. */
	PRIV_MUTLCAP_DATA_BLK_SIZE, /* Mutual Cap data block size. */
	mutlcap_xy_nodes,                       /* Mutual Cap channel nodes. */
	DEF_MUTLCAP_QUICK_REBURST_ENABLE,
	DEF_MUTLCAP_FILTER_CALLBACK,     /* Mutual Cap filter callback function
	                                 * pointer. */
	DEF_MUTLCAP_FREQ_AUTO_TUNE_ENABLE,
	DEF_MUTLCAP_NOISE_MEAS_ENABLE,
	DEF_MUTLCAP_NOISE_MEAS_BUFFER_CNT
};

/**
 * Touch Library input configuration structure.
 */
touch_config_t touch_config = {
	&mutlcap_config,                /* Pointer to Mutual Cap configuration
	                                 * structure. */
	NULL,

	DEF_TOUCH_PTC_ISR_LVL,          /* PTC interrupt level. */
};
/*----------------------------------------------------------------------------
*                               prototypes
*  ----------------------------------------------------------------------------*/

/*! \brief configure keys, rotors and sliders.
 */
static touch_ret_t touch_sensors_config(void);

/*! \brief Mutual Cap measure complete callback function example prototype.
 */
void touch_mutlcap_measure_complete_callback( void );

/*! \brief Initialize and enable PTC clock.
 */
void touch_configure_ptc_clock(void);
/*----------------------------------------------------------------------------
*  static functions
*  ----------------------------------------------------------------------------*/

void touch_configure_ptc_clock(void)
{
  PM_APBCMASK_s.ptc = 1;
  
  GCLK_CLKCTRL_s.id = 0x22;  // enabling clock for PTC
  GCLK_CLKCTRL_s.gen = 3;
  GCLK_CLKCTRL_s.clken = 1;
}

/* ! [setup] */

/*! \brief Example application entry function.
 */
touch_ret_t touch_sensors_init(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;

	/* Setup and enable generic clock source for PTC module. */
	touch_configure_ptc_clock();

	touch_time.measurement_period_ms = DEF_TOUCH_MEASUREMENT_PERIOD_MS;

	/* Initialize touch library for Self Cap operation. */
	touch_ret = touch_mutlcap_sensors_init(&touch_config);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1u) {    /* Check API Error return code. */
		}
	}

#if 0//DEF_TOUCH_QDEBUG_ENABLE == 1
	QDebug_Init();
#endif

	/* configure the touch library sensors. */
	touch_ret = touch_sensors_config();
	if (touch_ret != TOUCH_SUCCESS) {
		while (1u) {    /* Check API Error return code. */
		}
	}

	/* Auto Tuning setting for calibration.
	 *
	 * AUTO_TUNE_PRSC: When Auto tuning of pre-scaler is selected
	 * the PTC uses the user defined internal series resistor setting
	 * (DEF_MUTLCAP_SENSE_RESISTOR) and the pre-scaler is adjusted
	 * to slow down the PTC operation to ensure full charge transfer.
	 *
	 * AUTO_TUNE_RSEL: When Auto tuning of the series resistor is
	 * selected the PTC runs at user defined pre-scaler setting speed
	 * (DEF_MUTLCAP_CLK_PRESCALE) and the internal series resistor is
	 * tuned automatically to the optimum value to allow for full
	 * charge transfer.
	 *
	 * AUTO_TUNE_NONE: When manual tuning option is selected (AUTO_TUNE_NONE),
	 * the user defined values of PTC pre-scaler and series resistor is used
	 * for PTC operation as given in DEF_MUTLCAP_CLK_PRESCALE and
	 * DEF_MUTLCAP_SENSE_RESISTOR
	 *
	 */
	touch_ret = touch_mutlcap_sensors_calibrate(AUTO_TUNE_NONE);
	if (touch_ret != TOUCH_SUCCESS) {
		while (1u) {    /* Check API Error return code. */
		}
	}
        
        //GPIO for acq time measurement
        PORT->Group[0].DIRSET.reg = PORTA_DIRSET_P15;
        PORT->Group[0].OUTCLR.reg = PORTA_OUTCLR_P15;

	return (touch_ret);
}

touch_ret_t touch_sensors_measure(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;

	if (touch_time.time_to_measure_touch == 1u) {
          PORT->Group[0].OUTSET.reg = PORTA_OUTSET_P15;
		touch_ret = touch_mutlcap_sensors_measure(
				touch_time.current_time_ms,
				NORMAL_ACQ_MODE,
				touch_mutlcap_measure_complete_callback);

		if ((touch_ret != TOUCH_ACQ_INCOMPLETE) &&
				(touch_ret == TOUCH_SUCCESS)) {
			touch_time.time_to_measure_touch = 0u;
		} else if ((touch_ret != TOUCH_SUCCESS) &&
				(touch_ret != TOUCH_ACQ_INCOMPLETE)) {
			while (1) {
			}

			/* Reaching this point can be due to -
			 *     1. The api has retured an error due to a invalid
			 * input parameter.
			 *     2. The api has been called during a invalid Touch
			 * Library state. */
		}
	}

	return (touch_ret);
}

/*! \brief Example configuration for touch keys, rotors and sliders.
 *
 * \retval TOUCH_SUCCESS   Configuration setting successful.
 * \retval TOUCH_INVALID_xx   Invalid input configuration setting.
 */
touch_ret_t touch_sensors_config(void)
{
	touch_ret_t touch_ret = TOUCH_SUCCESS;
	sensor_id_t sensor_id;

	touch_ret = touch_mutlcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_0,CHANNEL_0, NO_AKS_GROUP, 30u, HYST_25,RES_8_BIT, 0u, &sensor_id);
	if (touch_ret != TOUCH_SUCCESS)
	{
		while (1) ;
	}

	touch_ret = touch_mutlcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_1,CHANNEL_1, NO_AKS_GROUP, 30u, HYST_25,RES_8_BIT, 0u, &sensor_id);
	if (touch_ret != TOUCH_SUCCESS)
	{
		while (1) ;
	}

	touch_ret = touch_mutlcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_2,CHANNEL_2, NO_AKS_GROUP, 30u, HYST_25,RES_8_BIT, 0u, &sensor_id);
	if (touch_ret != TOUCH_SUCCESS)
	{
		while (1) ;
	}

	touch_ret = touch_mutlcap_sensor_config(SENSOR_TYPE_KEY, CHANNEL_3,CHANNEL_3, NO_AKS_GROUP, 30u, HYST_25,RES_8_BIT, 0u, &sensor_id);
	if (touch_ret != TOUCH_SUCCESS)
	{
		while (1) ;
	}
        
        touch_ret = touch_mutlcap_sensor_config(SENSOR_TYPE_SLIDER, CHANNEL_4,CHANNEL_7, NO_AKS_GROUP, 30u, HYST_25,RES_8_BIT, 0u, &sensor_id);
	if (touch_ret != TOUCH_SUCCESS)
	{
		while (1) ;
	} 
        
	return (touch_ret);
}

/*! \brief Mutual Cap measure complete callback function.
 *
 * This function is called by the library when the touch measurement
 * process for Mutual Cap sensors is completed.
 *
 * \param p_measure_data   Base address of touch_measure_data_t instance.
 * \note A touch_mutlcap_measure_complete_callback() call signifies that fresh
 * values of touch status, rotor/slider position, measured signals,
 * references and Sensor data is available.
 * The Mutual Cap measured data can be accessed using the p_measure_data
 * pointer.
 */
void touch_mutlcap_measure_complete_callback( void )
{
#if 0//DEF_TOUCH_QDEBUG_ENABLE == 1

	/* Send out the Touch debug information data each time when Touch
	 *   measurement process is completed .
	 *   The Touch Signal and Touch Delta values are always sent.
	 *   Touch Status change, Rotor-Slider Position change and Sensor
	 * Reference
	 *   values can be optionally sent using the masks below.
	 */
	QDebug_SendData( TOUCH_CHANNEL_REF_CHANGE |
			TOUCH_ROTOR_SLIDER_POS_CHANGE |
			TOUCH_STATUS_CHANGE );
	/* QT600 two-way QDebug communication application Example. */
	/* Process any commands received from QTouch Studio. */
	QDebug_ProcessCommands();
#endif


	if (!(p_mutlcap_measure_data->acq_status & TOUCH_BURST_AGAIN)) {
		/* Set the Mutual Cap measurement done flag. */
		p_mutlcap_measure_data->measurement_done_touch = 1u;
		
		PORT->Group[0].OUTCLR.reg = PORTA_OUTCLR_P15;
	}
}
#endif