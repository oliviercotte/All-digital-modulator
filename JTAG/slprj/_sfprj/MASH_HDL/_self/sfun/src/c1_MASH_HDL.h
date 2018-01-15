#ifndef __c1_MASH_HDL_h__
#define __c1_MASH_HDL_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_MASH_HDLInstanceStruct
#define typedef_SFc1_MASH_HDLInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_MASH_HDL;
} SFc1_MASH_HDLInstanceStruct;

#endif                                 /*typedef_SFc1_MASH_HDLInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_MASH_HDL_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_MASH_HDL_get_check_sum(mxArray *plhs[]);
extern void c1_MASH_HDL_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
