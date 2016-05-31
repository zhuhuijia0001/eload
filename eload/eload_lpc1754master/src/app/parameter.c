#include <stdint.h>

#include "type.h"

#include "eeprom.h"
#include "parameter.h"

#include "dfs_posix.h"

static const char *PARAM_FILE_NAME = "param.dat";

/* default parameters */
static const uint32_t s_default_cv_mode_voltage_set = 5000ul;
	
static const uint32_t s_default_cc_mode_current_set = 300ul;

static const uint32_t s_default_cr_mode_resist_set = 100000ul;
	
static const SYNTH_TEST_SETTING s_default_synth_test_setting = 
{
	.empty_load_test_setting = 
	{
		.duration = 1000ul,

		.ac_limit = 100000ul,

		.voltage_from = 5000ul,

		.voltage_to   = 5500ul,
		
		.dp_dn_setting = 
		{
			.mode = VOLTAGE_DIVIDE_MODE,
			
			.on_off = OPTION_OFF,
			
			.divide_mode_setting = 
			{
				.dp_voltage_from = 5000ul,
				
				.dp_voltage_to = 5500ul,
				
				.dn_voltage_from = 5000ul,
				
				.dn_voltage_to = 5500ul
			},
			
			.short_mode_setting = 
			{
				.short_resist = 100000ul
			},
			
			.short_resist_mode_setting = 
			{
				.short_resist = 100000ul,
				
				.dp_resist = 100000ul,
				
				.dn_resist = 100000ul
			}
		}
	},

	.synth_normal_test_setting = 
	{
		[0] = 
		{
			.test_type = SYNTH_TEST_CV,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		},
				
		[1] = 
		{
			.test_type = SYNTH_TEST_CC,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		},

		[2] = 
		{
			.test_type = SYNTH_TEST_CR,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		},

		[3] = 
		{
			.test_type = SYNTH_TEST_CR,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		},

		[4] = 
		{
			.test_type = SYNTH_TEST_CR,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		},

		[5] = 
		{
			.test_type = SYNTH_TEST_CR,

			.on_off = OPTION_ON,

			.cv_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cv_val = 5000ul,

				.current_from = 100ul,

				.current_to = 1000ul
			},

			.cc_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cc_val = 100ul,

				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.cr_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.cr_val = 100000ul,

				.current_from = 100ul,

				.current_to = 1000ul,
							
				.voltage_from = 5000ul,

				.voltage_to = 5500ul
			},

			.over_current_test_setting = 
			{
				.interval = 100ul,

				.ac_limit = 100000ul,

				.current_limit = 1000ul
			},

			.short_test_setting = 
			{
				.duration = 1000ul,

				.ac_limit = 100000ul,

				.short_limit = 2000ul
			}
		}
	},

	.discharge_test_setting = 
	{
		.on_off  = OPTION_ON,
		
		.discharge_current = 1000ul,

		.discharge_duration = 1000ul,

		.indicate_delay = 2000ul
	}
};

/* QC 2.0 setting */
static const QC_20_TEST_SETTING s_default_qc_20_test_setting = 
{
	.empty_load_test_setting = 
	{
		.duration = 1000ul,

		.ac_limit = 100000ul,

		.voltage_from = 5000ul,

		.voltage_to   = 5500ul,
		
		.dp_dn_setting = 
		{
			.mode = VOLTAGE_DIVIDE_MODE,
			
			.on_off = OPTION_OFF,
			
			.divide_mode_setting = 
			{
				.dp_voltage_from = 5000ul,
				
				.dp_voltage_to = 5500ul,
				
				.dn_voltage_from = 5000ul,
				
				.dn_voltage_to = 5500ul
			},
			
			.short_mode_setting = 
			{
				.short_resist = 100000ul
			},
			
			.short_resist_mode_setting = 
			{
				.short_resist = 100000ul,
				
				.dp_resist = 100000ul,
				
				.dn_resist = 100000ul
			}
		}
	},

	.qc_20_normal_test_setting[0] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.qc_20_normal_test_setting[1] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.qc_20_normal_test_setting[2] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.qc_20_normal_test_setting[3] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.qc_20_normal_test_setting[4] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.qc_20_normal_test_setting[5] = 
	{
		.test_type = QC_20_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},
	
	.discharge_test_setting = 
	{
		.on_off  = OPTION_ON,
		
		.discharge_current = 1000ul,
		
		.discharge_duration = 1000ul,

		.indicate_delay = 2000ul
	}
};


/* MTK setting */
static const MTK_TEST_SETTING s_default_mtk_test_setting = 
{
	.empty_load_test_setting = 
	{
		.duration = 1000ul,

		.ac_limit = 100000ul,

		.voltage_from = 5000ul,

		.voltage_to   = 5500ul,
		
		.dp_dn_setting = 
		{
			.mode = VOLTAGE_DIVIDE_MODE,
			
			.on_off = OPTION_OFF,
			
			.divide_mode_setting = 
			{
				.dp_voltage_from = 5000ul,
				
				.dp_voltage_to = 5500ul,
				
				.dn_voltage_from = 5000ul,
				
				.dn_voltage_to = 5500ul
			},
			
			.short_mode_setting = 
			{
				.short_resist = 100000ul
			},
			
			.short_resist_mode_setting = 
			{
				.short_resist = 100000ul,
				
				.dp_resist = 100000ul,
				
				.dn_resist = 100000ul
			}
		}
	},

	.mtk_normal_test_setting[0] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.mtk_normal_test_setting[1] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.mtk_normal_test_setting[2] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.mtk_normal_test_setting[3] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.mtk_normal_test_setting[4] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},

	.mtk_normal_test_setting[5] = 
	{
		.test_type = MTK_5V_TEST_CV,
	
		.on_off = OPTION_ON,

		._5v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._5v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._5v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._5v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._5v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._9v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._9v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._9v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._9v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._9v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._12v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._12v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._12v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._12v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._12v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},

		._20v_cv_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cv_val = 5000ul,

			.current_from = 100ul,

			.current_to = 1000ul
		},

		._20v_cc_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cc_val = 100ul,

			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},
			
		._20v_cr_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.cr_val = 100000ul,

			.current_from = 100ul,

			.current_to = 1000ul,
							
			.voltage_from = 5000ul,

			.voltage_to = 5500ul
		},

		._20v_over_current_test_setting = 
		{
			.interval = 100ul,

			.ac_limit = 100000ul,

			.current_limit = 1000ul
		},

		._20v_short_test_setting = 
		{
			.duration = 1000ul,

			.ac_limit = 100000ul,

			.short_limit = 2000ul
		},
	},
	
	.discharge_test_setting = 
	{
		.on_off  = OPTION_ON,
		
		.discharge_current = 1000ul,
		
		.discharge_duration = 1000ul,

		.indicate_delay = 2000ul
	}
};

static const OPTION_ON_OFF s_default_channel_set[CHANNEL_COUNT] = 
{
	[0] = OPTION_ON,

	[1] = OPTION_ON,

	[2] = OPTION_ON,

	[3] = OPTION_ON,

	[4] = OPTION_ON,

	[5] = OPTION_ON,

	[6] = OPTION_ON,

	[7] = OPTION_ON
};

static const ADJUST_SETTING  s_default_adjust_setting[CHANNEL_COUNT] = 
{
	[0] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},
	
	[1] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},
	
	[2] = 
	{
		.actual_voltage = 5000ul,
			
		.actual_current = 1000ul
	},

	[3] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},

	[4] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},

	[5] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},

	[6] = 
	{
		.actual_voltage = 5000ul,

		.actual_current = 1000ul
	},

	[7] = 
	{
		.actual_voltage = 5000ul,
			
		.actual_current = 1000ul
	},	
};

static const DEVICE_PRIVILEGE s_default_device_privilege = 
{
	.QC_20_test_on_off = OPTION_OFF,
	.MTK_test_on_off   = OPTION_OFF
};
	
static const LIFE_LIMIT s_default_life_limit = 
{
	.power_on_limit = 1000,

	.power_on_count = 0
};

static const PHONE_NUMBER_SETTING s_default_phone_number_setting = 
{
	.default_phone_number = 
	{
		.phone_number = { '1', '3', '8', '8', '8', '8', '8', '8', '8', '8', '8' }
	},
		
	.customer_phone_number = 
	{
		.phone_number = { '1', '3', '7', '7', '7', '7', '7', '7', '7', '7', '7' }
	},	

	.customer_phone_number_power_on_limit = 1000,
		
	.customer_phone_number_power_on_count = 0
};

bool parameter_file_exist(void)
{
	int fd;
	uint32_t head;
	uint32_t size;
	
	fd = open(PARAM_FILE_NAME, O_RDONLY, 0);
    if (fd < 0)
    {
    	return false;
    }
    
    read(fd, &head, sizeof(head));
    if (head != PARAM_FILE_HEADER)
    {
    	close(fd);
    	
    	return false;
    }

	read(fd, &size, sizeof(size));
	if (size != sizeof(PARAMETER))
	{
		close(fd);

		return false;
	}
	
	close(fd);
	
    return true;
}

bool save_default_parameters(void)
{
	int fd;
	uint32_t head = PARAM_FILE_HEADER;

	uint32_t size = sizeof(PARAMETER);

	uint32_t group = 0;
	
	int i;
	
	int ret;

	/* 只写 & 创建 打开 */
	fd = open(PARAM_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0);
	RT_ASSERT(fd >= 0);

	/* 写入数据 */
	lseek(fd, 0, SEEK_SET);

	ret = write(fd, &head, sizeof(head));
	if (ret != sizeof(head))
	{
		goto FAILED;
	}

	ret = write(fd, &size, sizeof(size));
	if (ret != sizeof(size))
	{
		goto FAILED;
	}

	/* cv mode */
	ret = write(fd, &s_default_cv_mode_voltage_set, sizeof(s_default_cv_mode_voltage_set));
	if (ret != sizeof(s_default_cv_mode_voltage_set))
	{
		goto FAILED;
	}

	/* cc mode */
	ret = write(fd, &s_default_cc_mode_current_set, sizeof(s_default_cc_mode_current_set));
	if (ret != sizeof(s_default_cc_mode_current_set))
	{
		goto FAILED;
	}

	/* cr mode */
	ret = write(fd, &s_default_cr_mode_resist_set, sizeof(s_default_cr_mode_resist_set));
	if (ret != sizeof(s_default_cr_mode_resist_set))
	{
		goto FAILED;
	}

	/* synth test gorup */
	ret = write(fd, &group, sizeof(group));
	if (ret != sizeof(group))
	{
		goto FAILED;
	}	
	
	/* synth test setting */
	for (i = 0; i < SYNTH_TEST_GROUP_COUNT; i++)
	{
		ret = write(fd, &s_default_synth_test_setting, sizeof(s_default_synth_test_setting));
		if (ret != sizeof(s_default_synth_test_setting))
		{
			goto FAILED;
		}
	}

	/* qc2.0 test gorup */
	ret = write(fd, &group, sizeof(group));
	if (ret != sizeof(group))
	{
		goto FAILED;
	}	
	
	/* qc2.0 test setting */
	for (i = 0; i < QC_20_TEST_GROUP_COUNT; i++)
	{
		ret = write(fd, &s_default_qc_20_test_setting, sizeof(s_default_qc_20_test_setting));
		if (ret != sizeof(s_default_qc_20_test_setting))
		{
			goto FAILED;
		}
	}

	/* mtk test gorup */
	ret = write(fd, &group, sizeof(group));
	if (ret != sizeof(group))
	{
		goto FAILED;
	}	
	
	/* mtk test setting */
	for (i = 0; i < MTK_TEST_GROUP_COUNT; i++)
	{
		ret = write(fd, &s_default_mtk_test_setting, sizeof(s_default_mtk_test_setting));
		if (ret != sizeof(s_default_mtk_test_setting))
		{
			goto FAILED;
		}
	}
	
	/* channel set */
	ret = write(fd, &s_default_channel_set, sizeof(s_default_channel_set));
	if (ret != sizeof(s_default_channel_set))
	{
		goto FAILED;
	}

	/* adjust set */
	ret = write(fd, &s_default_adjust_setting, sizeof(s_default_adjust_setting));
	if (ret != sizeof(s_default_adjust_setting))
	{
		goto FAILED;
	}

	/* device privilege */
	ret = write(fd, &s_default_device_privilege, sizeof(s_default_device_privilege));
	if (ret != sizeof(s_default_device_privilege))
	{
		goto FAILED;
	}

	/* lift limit */
	ret = write(fd, &s_default_life_limit, sizeof(s_default_life_limit));
	if (ret != sizeof(s_default_life_limit))
	{
		goto FAILED;
	}

	/* phone number */
	ret = write(fd, &s_default_phone_number_setting, sizeof(s_default_phone_number_setting));
	if (ret != sizeof(s_default_phone_number_setting))
	{
		goto FAILED;
	}
	
	close(fd);

	return true;
	
FAILED:	
	/* 关闭文件 */
	close(fd);

	return false;

}

bool load_parameter(int offset, void *buffer, int len)
{
	int fd;

	int ret;

	/* read only */
	fd = open(PARAM_FILE_NAME, O_RDONLY, 0);
	RT_ASSERT(fd >= 0);
	
	/* read */
	lseek(fd, STRUCT_OFFSET(PARAMETER_FILE_STRUCT, param) + offset, SEEK_SET);

	ret = read(fd, buffer, len);
	if (ret != len)
	{
		close(fd);

		return false;
	}

	close(fd);

	return true;
}

bool save_parameter(int offset, const void *buffer, int len)
{
	int fd;

	int ret;

	/* write only */
	fd = open(PARAM_FILE_NAME, O_WRONLY, 0);
	RT_ASSERT(fd >= 0);

	/* write */
	lseek(fd, STRUCT_OFFSET(PARAMETER_FILE_STRUCT, param) + offset, SEEK_SET);

	ret = write(fd, buffer, len);
	if (ret != len)
	{
		close(fd);

		return false;
	}

	close(fd);

	return true;
}

