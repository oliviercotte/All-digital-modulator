#ifndef __c2_DSM_MOD8_HDL_h__
#define __c2_DSM_MOD8_HDL_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_DSM_MOD8_HDLInstanceStruct
#define typedef_SFc2_DSM_MOD8_HDLInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_DSM_MOD8_HDL;
} SFc2_DSM_MOD8_HDLInstanceStruct;

#endif                                 /*typedef_SFc2_DSM_MOD8_HDLInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_DSM_MOD8_HDL_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_DSM_MOD8_HDL_get_check_sum(mxArray *plhs[]);
extern void c2_DSM_MOD8_HDL_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
