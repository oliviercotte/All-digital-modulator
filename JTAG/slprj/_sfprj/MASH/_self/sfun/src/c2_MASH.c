/* Include files */

#include <stddef.h>
#include "blas.h"
#include "MASH_sfun.h"
#include "c2_MASH.h"
#include <math.h>
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MASH_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[8] = { "st", "n", "k", "nargin",
  "nargout", "quant_in", "nLev", "quant_out" };

static const mxArray *c2_eml_mx;
static const mxArray *c2_b_eml_mx;

/* Function Declarations */
static void initialize_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void initialize_params_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void enable_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void disable_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_MASH(SFc2_MASHInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_MASH(SFc2_MASHInstanceStruct
  *chartInstance);
static void set_sim_state_c2_MASH(SFc2_MASHInstanceStruct *chartInstance, const
  mxArray *c2_st);
static void finalize_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void sf_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void c2_chartstep_c2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void initSimStructsc2_MASH(SFc2_MASHInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static int64_T c2_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_b_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(uint32_T c2_u);
static void c2_b_info_helper(const mxArray **c2_info);
static void c2_eml_fi_checkforconst(SFc2_MASHInstanceStruct *chartInstance);
static int64_T c2_uminus(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_xfi);
static boolean_T c2_lt(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int64_T c2_b0);
static boolean_T c2_ge(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int64_T c2_b0);
static void c2_strcmpi(SFc2_MASHInstanceStruct *chartInstance);
static void c2_eml_scalar_eg(SFc2_MASHInstanceStruct *chartInstance);
static int128m_T c2_mtimes(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_b0);
static int128m_T c2_plus(SFc2_MASHInstanceStruct *chartInstance, real_T c2_a0,
  int128m_T c2_b0);
static boolean_T c2_b_ge(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int128m_T c2_b0);
static int64_T c2_b_plus(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  real_T c2_b0);
static int128m_T c2_b_mtimes(SFc2_MASHInstanceStruct *chartInstance, int64_T
  c2_b0);
static int128m_T c2_c_plus(SFc2_MASHInstanceStruct *chartInstance, real_T c2_a0,
  int128m_T c2_b0);
static int128m_T c2_minus(SFc2_MASHInstanceStruct *chartInstance, int128m_T
  c2_a0, real_T c2_b0);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_c_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int64_T c2_d_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_quant_out, const char_T *c2_identifier);
static int64_T c2_e_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_f_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_MASH, const char_T *c2_identifier);
static uint8_T c2_g_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static boolean_T c2_sMultiWordLt(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n);
static int32_T c2_sMultiWordCmp(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n);
static void c2_MultiWordSignedWrap(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[]);
static void c2_sMultiWordShl(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n);
static void c2_sLong2MultiWord(SFc2_MASHInstanceStruct *chartInstance, int64_T
  c2_u, uint64_T c2_y[], int32_T c2_n);
static void c2_Double2MultiWord(SFc2_MASHInstanceStruct *chartInstance, real_T
  c2_u1, uint64_T c2_y[], int32_T c2_n);
static void c2_sMultiWordShr(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n);
static void c2_sMultiWord2sMultiWordSat(SFc2_MASHInstanceStruct *chartInstance,
  const uint64_T c2_u1[], int32_T c2_n1, uint64_T c2_y[], int32_T c2_n);
static void c2_sMultiWord2MultiWord(SFc2_MASHInstanceStruct *chartInstance,
  const uint64_T c2_u1[], int32_T c2_n1, uint64_T c2_y[], int32_T c2_n);
static void c2_MultiWordSub(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], uint64_T c2_y[], int32_T c2_n);
static int64_T c2_MultiWord2sLong(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u[]);
static void c2_sMultiWordShrNear(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n);
static void c2_MultiWordAdd(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], uint64_T c2_y[], int32_T c2_n);
static boolean_T c2_sMultiWordGe(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n);
static void init_dsm_address_info(SFc2_MASHInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_MASH = 0U;
  sf_mex_assign(&c2_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 34.0, 15, "FractionLength", 6, 22.0, 15, "BinaryPoint", 6,
    22.0, 15, "Slope", 6, 2.384185791015625E-7, 15, "FixedExponent", 6, -22.0),
                TRUE);
  sf_mex_assign(&c2_eml_mx, sf_mex_call_debug("fimath", 1U, 42U, 15, "RoundMode",
    15, "nearest", 15, "RoundingMethod", 15, "Nearest", 15, "OverflowMode", 15,
    "saturate", 15, "OverflowAction", 15, "Saturate", 15, "ProductMode", 15,
    "FullPrecision", 15, "ProductWordLength", 6, 32.0, 15,
    "MaxProductWordLength", 6, 65535.0, 15, "ProductFractionLength", 6, 30.0, 15,
    "ProductFixedExponent", 6, -30.0, 15, "ProductSlope", 6,
    9.3132257461547852E-10, 15, "ProductSlopeAdjustmentFactor", 6, 1.0, 15,
    "ProductBias", 6, 0.0, 15, "SumMode", 15, "FullPrecision", 15,
    "SumWordLength", 6, 32.0, 15, "MaxSumWordLength", 6, 65535.0, 15,
    "SumFractionLength", 6, 30.0, 15, "SumFixedExponent", 6, -30.0, 15,
    "SumSlope", 6, 9.3132257461547852E-10, 15, "SumSlopeAdjustmentFactor", 6,
    1.0, 15, "SumBias", 6, 0.0, 15, "CastBeforeSum", 3, TRUE), TRUE);
}

static void initialize_params_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
}

static void enable_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_MASH(SFc2_MASHInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_MASH(SFc2_MASHInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int64_T c2_hoistedGlobal;
  int64_T c2_u;
  const mxArray *c2_b_y = NULL;
  int64_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  int64_T *c2_quant_out;
  c2_quant_out = (int64_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  c2_hoistedGlobal = *c2_quant_out;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  c2_b_u = c2_u;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 8, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_b_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
    "simulinkarray", 14, c2_c_y, 15, "fimathislocal", 3, TRUE), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_MASH;
  c2_c_u = c2_b_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_d_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_MASH(SFc2_MASHInstanceStruct *chartInstance, const
  mxArray *c2_st)
{
  const mxArray *c2_u;
  int64_T *c2_quant_out;
  c2_quant_out = (int64_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  *c2_quant_out = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 0)), "quant_out");
  chartInstance->c2_is_active_c2_MASH = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_MASH");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_MASH(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  sf_mex_destroy(&c2_eml_mx);
  sf_mex_destroy(&c2_b_eml_mx);
}

static void sf_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  int64_T *c2_quant_in;
  int64_T *c2_quant_out;
  real_T *c2_nLev;
  c2_nLev = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_quant_out = (int64_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_quant_in = (int64_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_quant_in, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_quant_out, 1U);
  _SFD_DATA_RANGE_CHECK(*c2_nLev, 2U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_MASH(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MASHMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
  int64_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  int64_T c2_quant_in;
  real_T c2_nLev;
  uint32_T c2_debug_family_var_map[8];
  int64_T c2_st;
  real_T c2_n;
  int64_T c2_k;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int64_T c2_quant_out;
  real_T c2_varargin_1;
  real_T c2_b_varargin_1;
  real_T c2_var1;
  real_T c2_u;
  real_T c2_v;
  real_T c2_d0;
  int64_T c2_i0;
  const mxArray *c2_errMsgStr = NULL;
  const mxArray *c2_errMsgID = NULL;
  const mxArray *c2_errMsgExtraArgs = NULL;
  const mxArray *c2_T = NULL;
  const mxArray *c2_F = NULL;
  const mxArray *c2_val = NULL;
  const mxArray *c2_isautoscaled = NULL;
  const mxArray *c2_pvpairsetdata = NULL;
  const mxArray *c2_isfimathlocal = NULL;
  real_T c2_c_varargin_1;
  real_T c2_d_varargin_1;
  real_T c2_b_var1;
  real_T c2_b_u;
  real_T c2_b_v;
  real_T c2_d1;
  int64_T c2_i1;
  const mxArray *c2_b_errMsgStr = NULL;
  const mxArray *c2_b_errMsgID = NULL;
  const mxArray *c2_b_errMsgExtraArgs = NULL;
  const mxArray *c2_b_T = NULL;
  const mxArray *c2_b_F = NULL;
  const mxArray *c2_b_val = NULL;
  const mxArray *c2_b_isautoscaled = NULL;
  const mxArray *c2_b_pvpairsetdata = NULL;
  const mxArray *c2_b_isfimathlocal = NULL;
  real_T c2_e_varargin_1;
  real_T c2_f_varargin_1;
  real_T c2_c_var1;
  real_T c2_c_u;
  real_T c2_c_v;
  real_T c2_d2;
  int64_T c2_i2;
  const mxArray *c2_c_errMsgStr = NULL;
  const mxArray *c2_c_errMsgID = NULL;
  const mxArray *c2_c_errMsgExtraArgs = NULL;
  const mxArray *c2_c_T = NULL;
  const mxArray *c2_c_F = NULL;
  const mxArray *c2_c_val = NULL;
  const mxArray *c2_c_isautoscaled = NULL;
  const mxArray *c2_c_pvpairsetdata = NULL;
  const mxArray *c2_c_isfimathlocal = NULL;
  real_T c2_d3;
  int32_T c2_i3;
  int32_T c2_b_n;
  real_T c2_g_varargin_1;
  real_T c2_h_varargin_1;
  real_T c2_d_var1;
  real_T c2_d_u;
  real_T c2_d_v;
  real_T c2_d4;
  int64_T c2_i4;
  const mxArray *c2_d_errMsgStr = NULL;
  const mxArray *c2_d_errMsgID = NULL;
  const mxArray *c2_d_errMsgExtraArgs = NULL;
  const mxArray *c2_d_T = NULL;
  const mxArray *c2_d_F = NULL;
  const mxArray *c2_d_val = NULL;
  const mxArray *c2_d_isautoscaled = NULL;
  const mxArray *c2_d_pvpairsetdata = NULL;
  const mxArray *c2_d_isfimathlocal = NULL;
  int64_T c2_a0;
  int128m_T c2_b;
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_a;
  int64_T c2_b_a0;
  int64_T c2_a1;
  int64_T c2_b_a1;
  int128m_T c2_r0;
  int128m_T c2_r1;
  int128m_T c2_r2;
  boolean_T c2_c;
  int128m_T c2_b_a;
  real_T c2_b0;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  real_T c2_e_u;
  real_T c2_e_v;
  real_T c2_d5;
  int128m_T c2_r3;
  static int128m_T c2_r4 = { { 0ULL, 18446744073709551600ULL } };

  static int128m_T c2_r5 = { { MAX_uint64_T, 15ULL } };

  static int128m_T c2_r6 = { { 0ULL, 0ULL } };

  int128m_T c2_b_b;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  const mxArray *c2_k_propVal = NULL;
  const mxArray *c2_k_errid = NULL;
  const mxArray *c2_l_propVal = NULL;
  const mxArray *c2_l_errid = NULL;
  const mxArray *c2_m_propVal = NULL;
  const mxArray *c2_m_errid = NULL;
  int128m_T c2_r7;
  int128m_T c2_r8;
  int128m_T c2_r9;
  int192m_T c2_r10;
  int192m_T c2_r11;
  int128m_T c2_b_c;
  const mxArray *c2_n_propVal = NULL;
  const mxArray *c2_n_errid = NULL;
  const mxArray *c2_o_propVal = NULL;
  const mxArray *c2_o_errid = NULL;
  int64_T c2_i5;
  const mxArray *c2_e_errMsgStr = NULL;
  const mxArray *c2_e_errMsgID = NULL;
  const mxArray *c2_e_errMsgExtraArgs = NULL;
  const mxArray *c2_e_T = NULL;
  const mxArray *c2_e_F = NULL;
  const mxArray *c2_e_val = NULL;
  const mxArray *c2_e_isautoscaled = NULL;
  const mxArray *c2_e_pvpairsetdata = NULL;
  const mxArray *c2_e_isfimathlocal = NULL;
  int64_T *c2_b_quant_out;
  int64_T *c2_b_quant_in;
  real_T *c2_b_nLev;
  boolean_T guard1 = FALSE;
  c2_b_nLev = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_quant_out = (int64_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_quant_in = (int64_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_quant_in;
  c2_b_hoistedGlobal = *c2_b_nLev;
  c2_quant_in = c2_hoistedGlobal;
  c2_nLev = c2_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_st, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_n, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_quant_in, 5U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_nLev, 6U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_quant_out, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  c2_varargin_1 = c2_nLev - 2.0;
  c2_b_varargin_1 = c2_varargin_1;
  c2_eml_fi_checkforconst(chartInstance);
  c2_var1 = c2_b_varargin_1;
  c2_u = c2_var1 * 4.194304E+6;
  c2_v = muDoubleScalarAbs(c2_u);
  if (c2_v < 4.503599627370496E+15) {
    if (c2_v >= 0.5) {
      c2_d0 = muDoubleScalarFloor(c2_u + 0.5);
    } else {
      c2_d0 = c2_u * 0.0;
    }
  } else {
    c2_d0 = c2_u;
  }

  if (c2_d0 < 8.589934592E+9) {
    if (CV_SATURATION_EVAL(4, 0, 5, 1, c2_d0 >= -8.589934592E+9)) {
      c2_i0 = (int64_T)c2_d0;
    } else {
      c2_i0 = -8589934592LL;
    }
  } else if (CV_SATURATION_EVAL(4, 0, 5, 0, c2_d0 >= 8.589934592E+9)) {
    c2_i0 = 8589934591LL;
  } else {
    c2_i0 = 0LL;
  }

  c2_st = c2_i0;
  sf_mex_destroy(&c2_errMsgStr);
  sf_mex_destroy(&c2_errMsgID);
  sf_mex_destroy(&c2_errMsgExtraArgs);
  sf_mex_destroy(&c2_T);
  sf_mex_destroy(&c2_F);
  sf_mex_destroy(&c2_val);
  sf_mex_destroy(&c2_isautoscaled);
  sf_mex_destroy(&c2_pvpairsetdata);
  sf_mex_destroy(&c2_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_quant_out = 0LL;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  if (CV_EML_IF(0, 1, 0, c2_lt(chartInstance, c2_quant_in, c2_uminus
        (chartInstance, c2_st)))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
    c2_c_varargin_1 = -c2_nLev + 1.0;
    c2_d_varargin_1 = c2_c_varargin_1;
    c2_eml_fi_checkforconst(chartInstance);
    c2_b_var1 = c2_d_varargin_1;
    c2_b_u = c2_b_var1 * 4.194304E+6;
    c2_b_v = muDoubleScalarAbs(c2_b_u);
    if (c2_b_v < 4.503599627370496E+15) {
      if (c2_b_v >= 0.5) {
        c2_d1 = muDoubleScalarFloor(c2_b_u + 0.5);
      } else {
        c2_d1 = c2_b_u * 0.0;
      }
    } else {
      c2_d1 = c2_b_u;
    }

    if (c2_d1 < 8.589934592E+9) {
      if (CV_SATURATION_EVAL(4, 0, 0, 1, c2_d1 >= -8.589934592E+9)) {
        c2_i1 = (int64_T)c2_d1;
      } else {
        c2_i1 = -8589934592LL;
      }
    } else if (CV_SATURATION_EVAL(4, 0, 0, 0, c2_d1 >= 8.589934592E+9)) {
      c2_i1 = 8589934591LL;
    } else {
      c2_i1 = 0LL;
    }

    c2_quant_out = c2_i1;
    sf_mex_destroy(&c2_b_errMsgStr);
    sf_mex_destroy(&c2_b_errMsgID);
    sf_mex_destroy(&c2_b_errMsgExtraArgs);
    sf_mex_destroy(&c2_b_T);
    sf_mex_destroy(&c2_b_F);
    sf_mex_destroy(&c2_b_val);
    sf_mex_destroy(&c2_b_isautoscaled);
    sf_mex_destroy(&c2_b_pvpairsetdata);
    sf_mex_destroy(&c2_b_isfimathlocal);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
    if (CV_EML_IF(0, 1, 1, c2_ge(chartInstance, c2_quant_in, c2_st))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
      c2_e_varargin_1 = c2_nLev - 1.0;
      c2_f_varargin_1 = c2_e_varargin_1;
      c2_eml_fi_checkforconst(chartInstance);
      c2_c_var1 = c2_f_varargin_1;
      c2_c_u = c2_c_var1 * 4.194304E+6;
      c2_c_v = muDoubleScalarAbs(c2_c_u);
      if (c2_c_v < 4.503599627370496E+15) {
        if (c2_c_v >= 0.5) {
          c2_d2 = muDoubleScalarFloor(c2_c_u + 0.5);
        } else {
          c2_d2 = c2_c_u * 0.0;
        }
      } else {
        c2_d2 = c2_c_u;
      }

      if (c2_d2 < 8.589934592E+9) {
        if (CV_SATURATION_EVAL(4, 0, 1, 1, c2_d2 >= -8.589934592E+9)) {
          c2_i2 = (int64_T)c2_d2;
        } else {
          c2_i2 = -8589934592LL;
        }
      } else if (CV_SATURATION_EVAL(4, 0, 1, 0, c2_d2 >= 8.589934592E+9)) {
        c2_i2 = 8589934591LL;
      } else {
        c2_i2 = 0LL;
      }

      c2_quant_out = c2_i2;
      sf_mex_destroy(&c2_c_errMsgStr);
      sf_mex_destroy(&c2_c_errMsgID);
      sf_mex_destroy(&c2_c_errMsgExtraArgs);
      sf_mex_destroy(&c2_c_T);
      sf_mex_destroy(&c2_c_F);
      sf_mex_destroy(&c2_c_val);
      sf_mex_destroy(&c2_c_isautoscaled);
      sf_mex_destroy(&c2_c_pvpairsetdata);
      sf_mex_destroy(&c2_c_isfimathlocal);
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
      c2_d3 = c2_nLev - 2.0;
      c2_i3 = (int32_T)c2_d3;
      _SFD_FOR_LOOP_VECTOR_CHECK(1.0, 1.0, c2_d3, mxDOUBLE_CLASS, c2_i3);
      c2_n = 1.0;
      c2_b_n = 0;
      while (c2_b_n <= c2_i3 - 1) {
        c2_n = 1.0 + (real_T)c2_b_n;
        CV_EML_FOR(0, 1, 0, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
        c2_g_varargin_1 = c2_n;
        c2_h_varargin_1 = c2_g_varargin_1;
        c2_eml_fi_checkforconst(chartInstance);
        c2_d_var1 = c2_h_varargin_1;
        c2_d_u = c2_d_var1 * 4.194304E+6;
        c2_d_v = muDoubleScalarAbs(c2_d_u);
        if (c2_d_v < 4.503599627370496E+15) {
          if (c2_d_v >= 0.5) {
            c2_d4 = muDoubleScalarFloor(c2_d_u + 0.5);
          } else {
            c2_d4 = c2_d_u * 0.0;
          }
        } else {
          c2_d4 = c2_d_u;
        }

        if (c2_d4 < 8.589934592E+9) {
          if (CV_SATURATION_EVAL(4, 0, 2, 1, c2_d4 >= -8.589934592E+9)) {
            c2_i4 = (int64_T)c2_d4;
          } else {
            c2_i4 = -8589934592LL;
          }
        } else if (CV_SATURATION_EVAL(4, 0, 2, 0, c2_d4 >= 8.589934592E+9)) {
          c2_i4 = 8589934591LL;
        } else {
          c2_i4 = 0LL;
        }

        c2_k = c2_i4;
        sf_mex_destroy(&c2_d_errMsgStr);
        sf_mex_destroy(&c2_d_errMsgID);
        sf_mex_destroy(&c2_d_errMsgExtraArgs);
        sf_mex_destroy(&c2_d_T);
        sf_mex_destroy(&c2_d_F);
        sf_mex_destroy(&c2_d_val);
        sf_mex_destroy(&c2_d_isautoscaled);
        sf_mex_destroy(&c2_d_pvpairsetdata);
        sf_mex_destroy(&c2_d_isfimathlocal);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
        guard1 = FALSE;
        if (CV_EML_COND(0, 1, 0, c2_b_ge(chartInstance, c2_quant_in, c2_plus
              (chartInstance, -c2_nLev, c2_mtimes(chartInstance, c2_k))))) {
          c2_a0 = c2_quant_in;
          c2_b = c2_c_plus(chartInstance, -c2_nLev, c2_b_mtimes(chartInstance,
            c2_b_plus(chartInstance, c2_k, 1.0)));
          sf_mex_destroy(&c2_propVal);
          sf_mex_destroy(&c2_errid);
          sf_mex_destroy(&c2_b_propVal);
          sf_mex_destroy(&c2_b_errid);
          sf_mex_destroy(&c2_c_propVal);
          sf_mex_destroy(&c2_c_errid);
          c2_a = c2_a0;
          c2_b_a0 = c2_a;
          c2_a1 = c2_b_a0;
          c2_b_a1 = c2_a1;
          c2_sLong2MultiWord(chartInstance, c2_b_a1, &c2_r0.chunks[0U], 2);
          c2_sMultiWordShl(chartInstance, &c2_r0.chunks[0U], 2, 32U,
                           &c2_r1.chunks[0U], 2);
          c2_MultiWordSignedWrap(chartInstance, &c2_r1.chunks[0U], 2, 32U,
            &c2_r2.chunks[0U]);
          c2_MultiWordSignedWrap(chartInstance, &c2_b.chunks[0U], 2, 32U,
            &c2_r1.chunks[0U]);
          c2_c = c2_sMultiWordLt(chartInstance, &c2_r2.chunks[0U],
            &c2_r1.chunks[0U], 2);
          if (CV_EML_COND(0, 1, 1, c2_c)) {
            CV_EML_MCDC(0, 1, 0, TRUE);
            CV_EML_IF(0, 1, 2, TRUE);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
            c2_b_a = c2_minus(chartInstance, c2_mtimes(chartInstance, c2_k), 1.0);
            c2_b0 = c2_nLev;
            sf_mex_destroy(&c2_d_propVal);
            sf_mex_destroy(&c2_d_errid);
            sf_mex_destroy(&c2_e_propVal);
            sf_mex_destroy(&c2_e_errid);
            c2_strcmpi(chartInstance);
            c2_e_u = c2_b0 * 9.007199254740992E+15;
            c2_e_v = muDoubleScalarAbs(c2_e_u);
            if (c2_e_v < 4.503599627370496E+15) {
              if (c2_e_v >= 0.5) {
                c2_d5 = muDoubleScalarFloor(c2_e_u + 0.5);
              } else {
                c2_d5 = c2_e_u * 0.0;
              }
            } else {
              c2_d5 = c2_e_u;
            }

            if (c2_d5 < 2.9514790517935283E+20) {
              if (CV_SATURATION_EVAL(4, 0, 4, 1, c2_d5 >=
                                     -2.9514790517935283E+20)) {
                c2_Double2MultiWord(chartInstance, c2_d5, &c2_r3.chunks[0U], 2);
              } else {
                c2_r3 = c2_r4;
              }
            } else if (CV_SATURATION_EVAL(4, 0, 4, 0, c2_d5 >=
                        2.9514790517935283E+20)) {
              c2_r3 = c2_r5;
            } else {
              c2_r3 = c2_r6;
            }

            c2_b_b = c2_r3;
            sf_mex_destroy(&c2_f_propVal);
            sf_mex_destroy(&c2_f_errid);
            sf_mex_destroy(&c2_g_propVal);
            sf_mex_destroy(&c2_g_errid);
            sf_mex_destroy(&c2_h_propVal);
            sf_mex_destroy(&c2_h_errid);
            sf_mex_destroy(&c2_i_propVal);
            sf_mex_destroy(&c2_i_errid);
            sf_mex_destroy(&c2_j_propVal);
            sf_mex_destroy(&c2_j_errid);
            sf_mex_destroy(&c2_k_propVal);
            sf_mex_destroy(&c2_k_errid);
            sf_mex_destroy(&c2_l_propVal);
            sf_mex_destroy(&c2_l_errid);
            sf_mex_destroy(&c2_m_propVal);
            sf_mex_destroy(&c2_m_errid);
            c2_MultiWordSignedWrap(chartInstance, &c2_b_a.chunks[0U], 2, 58U,
              &c2_r7.chunks[0U]);
            c2_MultiWordSignedWrap(chartInstance, &c2_b_b.chunks[0U], 2, 58U,
              &c2_r8.chunks[0U]);
            c2_MultiWordSub(chartInstance, &c2_r7.chunks[0U], &c2_r8.chunks[0U],
                            &c2_r9.chunks[0U], 2);
            c2_sMultiWord2MultiWord(chartInstance, &c2_r9.chunks[0U], 2,
              &c2_r10.chunks[0U], 3);
            c2_sMultiWordShl(chartInstance, &c2_r10.chunks[0U], 3, 58U,
                             &c2_r11.chunks[0U], 3);
            c2_sMultiWord2sMultiWordSat(chartInstance, &c2_r11.chunks[0U], 3,
              &c2_r0.chunks[0U], 2);
            c2_sMultiWordShr(chartInstance, &c2_r0.chunks[0U], 2, 58U,
                             &c2_b_c.chunks[0U], 2);
            c2_eml_fi_checkforconst(chartInstance);
            sf_mex_destroy(&c2_n_propVal);
            sf_mex_destroy(&c2_n_errid);
            sf_mex_destroy(&c2_o_propVal);
            sf_mex_destroy(&c2_o_errid);
            c2_sMultiWordShrNear(chartInstance, &c2_b_c.chunks[0U], 2, 31U,
                                 &c2_r0.chunks[0U], 2);
            c2_i5 = c2_MultiWord2sLong(chartInstance, &c2_r0.chunks[0U]);
            if (c2_i5 > 8589934591LL) {
              CV_SATURATION_EVAL(4, 0, 3, 0, 1);
              c2_i5 = 8589934591LL;
            } else {
              if (CV_SATURATION_EVAL(4, 0, 3, 0, c2_i5 < -8589934592LL)) {
                c2_i5 = -8589934592LL;
              }
            }

            c2_quant_out = c2_i5;
            sf_mex_destroy(&c2_e_errMsgStr);
            sf_mex_destroy(&c2_e_errMsgID);
            sf_mex_destroy(&c2_e_errMsgExtraArgs);
            sf_mex_destroy(&c2_e_T);
            sf_mex_destroy(&c2_e_F);
            sf_mex_destroy(&c2_e_val);
            sf_mex_destroy(&c2_e_isautoscaled);
            sf_mex_destroy(&c2_e_pvpairsetdata);
            sf_mex_destroy(&c2_e_isfimathlocal);
          } else {
            guard1 = TRUE;
          }
        } else {
          guard1 = TRUE;
        }

        if (guard1 == TRUE) {
          CV_EML_MCDC(0, 1, 0, FALSE);
          CV_EML_IF(0, 1, 2, FALSE);
        }

        c2_b_n++;
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 0, 0);
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -15);
  _SFD_SYMBOL_SCOPE_POP();
  *c2_b_quant_out = c2_quant_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_MASH(SFc2_MASHInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int64_T c2_u;
  const mxArray *c2_y = NULL;
  int64_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int64_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 8, 0U, 0U, 0U, 0), FALSE);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, FALSE), FALSE);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), FALSE);
  }

  return c2_mxArrayOutData;
}

static int64_T c2_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int64_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int64_T c2_i6;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_b_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), FALSE);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), FALSE);
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_i6, 1, 8, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_i6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_quant_out;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int64_T c2_y;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_quant_out = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_quant_out),
      &c2_thisId);
    sf_mex_destroy(&c2_quant_out);
    *(int64_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_b_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d6;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d6, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_MASH_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 112, 1),
                FALSE);
  c2_info_helper(&c2_nameCaptureInfo);
  c2_b_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  const mxArray *c2_rhs48 = NULL;
  const mxArray *c2_lhs48 = NULL;
  const mxArray *c2_rhs49 = NULL;
  const mxArray *c2_lhs49 = NULL;
  const mxArray *c2_rhs50 = NULL;
  const mxArray *c2_lhs50 = NULL;
  const mxArray *c2_rhs51 = NULL;
  const mxArray *c2_lhs51 = NULL;
  const mxArray *c2_rhs52 = NULL;
  const mxArray *c2_lhs52 = NULL;
  const mxArray *c2_rhs53 = NULL;
  const mxArray *c2_lhs53 = NULL;
  const mxArray *c2_rhs54 = NULL;
  const mxArray *c2_lhs54 = NULL;
  const mxArray *c2_rhs55 = NULL;
  const mxArray *c2_lhs55 = NULL;
  const mxArray *c2_rhs56 = NULL;
  const mxArray *c2_lhs56 = NULL;
  const mxArray *c2_rhs57 = NULL;
  const mxArray *c2_lhs57 = NULL;
  const mxArray *c2_rhs58 = NULL;
  const mxArray *c2_lhs58 = NULL;
  const mxArray *c2_rhs59 = NULL;
  const mxArray *c2_lhs59 = NULL;
  const mxArray *c2_rhs60 = NULL;
  const mxArray *c2_lhs60 = NULL;
  const mxArray *c2_rhs61 = NULL;
  const mxArray *c2_lhs61 = NULL;
  const mxArray *c2_rhs62 = NULL;
  const mxArray *c2_lhs62 = NULL;
  const mxArray *c2_rhs63 = NULL;
  const mxArray *c2_lhs63 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fi_impl"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1366183840U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303167806U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531952U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360303946U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("uminus"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531988U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "context", "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "context", "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfixed"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531978U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "context", "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1348213518U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303167806U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840358U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840386U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731858U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uminus.m"),
                  "context", "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isslopebiasscaled"), "name",
                  "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531960U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840358U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840386U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731858U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("lt"), "name", "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531982U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "context", "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_check_same_bias"), "name",
                  "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531968U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/lt.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289541246U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("ge"), "name", "name", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531976U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "context", "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_check_same_bias"), "name",
                  "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531968U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ge.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289541246U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mtimes"), "name", "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/mtimes.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531984U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/mtimes.m"),
                  "context", "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/mtimes.m"),
                  "context", "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/mtimes.m"),
                  "context", "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/mtimes.m"),
                  "context", "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("times"), "name", "name", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531986U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c2_rhs48, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs48, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531938U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c2_rhs49, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs49, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("strcmpi"), "name", "name", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c2_rhs50, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs50, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c2_rhs51, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs51, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m!inrange"),
                  "context", "context", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c2_rhs52, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs52, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"), "context",
                  "context", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c2_rhs53, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs53, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311276918U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c2_rhs54, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs54, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731870U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c2_rhs55, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs55, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c2_rhs56, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs56, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1358207740U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c2_rhs57, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs57, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323192178U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c2_rhs58, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs58, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c2_rhs59, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs59, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c2_rhs60, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs60, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c2_rhs61, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs61, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("lower"), "name", "name", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "resolved",
                  "resolved", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c2_rhs62, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs62, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "context",
                  "context", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_string_transform"), "name",
                  "name", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c2_rhs63, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs63, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
  sf_mex_destroy(&c2_rhs48);
  sf_mex_destroy(&c2_lhs48);
  sf_mex_destroy(&c2_rhs49);
  sf_mex_destroy(&c2_lhs49);
  sf_mex_destroy(&c2_rhs50);
  sf_mex_destroy(&c2_lhs50);
  sf_mex_destroy(&c2_rhs51);
  sf_mex_destroy(&c2_lhs51);
  sf_mex_destroy(&c2_rhs52);
  sf_mex_destroy(&c2_lhs52);
  sf_mex_destroy(&c2_rhs53);
  sf_mex_destroy(&c2_lhs53);
  sf_mex_destroy(&c2_rhs54);
  sf_mex_destroy(&c2_lhs54);
  sf_mex_destroy(&c2_rhs55);
  sf_mex_destroy(&c2_lhs55);
  sf_mex_destroy(&c2_rhs56);
  sf_mex_destroy(&c2_lhs56);
  sf_mex_destroy(&c2_rhs57);
  sf_mex_destroy(&c2_lhs57);
  sf_mex_destroy(&c2_rhs58);
  sf_mex_destroy(&c2_lhs58);
  sf_mex_destroy(&c2_rhs59);
  sf_mex_destroy(&c2_lhs59);
  sf_mex_destroy(&c2_rhs60);
  sf_mex_destroy(&c2_lhs60);
  sf_mex_destroy(&c2_rhs61);
  sf_mex_destroy(&c2_lhs61);
  sf_mex_destroy(&c2_rhs62);
  sf_mex_destroy(&c2_lhs62);
  sf_mex_destroy(&c2_rhs63);
  sf_mex_destroy(&c2_lhs63);
}

static const mxArray *c2_emlrt_marshallOut(char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), FALSE);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c2_y;
}

static void c2_b_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs64 = NULL;
  const mxArray *c2_lhs64 = NULL;
  const mxArray *c2_rhs65 = NULL;
  const mxArray *c2_lhs65 = NULL;
  const mxArray *c2_rhs66 = NULL;
  const mxArray *c2_lhs66 = NULL;
  const mxArray *c2_rhs67 = NULL;
  const mxArray *c2_lhs67 = NULL;
  const mxArray *c2_rhs68 = NULL;
  const mxArray *c2_lhs68 = NULL;
  const mxArray *c2_rhs69 = NULL;
  const mxArray *c2_lhs69 = NULL;
  const mxArray *c2_rhs70 = NULL;
  const mxArray *c2_lhs70 = NULL;
  const mxArray *c2_rhs71 = NULL;
  const mxArray *c2_lhs71 = NULL;
  const mxArray *c2_rhs72 = NULL;
  const mxArray *c2_lhs72 = NULL;
  const mxArray *c2_rhs73 = NULL;
  const mxArray *c2_lhs73 = NULL;
  const mxArray *c2_rhs74 = NULL;
  const mxArray *c2_lhs74 = NULL;
  const mxArray *c2_rhs75 = NULL;
  const mxArray *c2_lhs75 = NULL;
  const mxArray *c2_rhs76 = NULL;
  const mxArray *c2_lhs76 = NULL;
  const mxArray *c2_rhs77 = NULL;
  const mxArray *c2_lhs77 = NULL;
  const mxArray *c2_rhs78 = NULL;
  const mxArray *c2_lhs78 = NULL;
  const mxArray *c2_rhs79 = NULL;
  const mxArray *c2_lhs79 = NULL;
  const mxArray *c2_rhs80 = NULL;
  const mxArray *c2_lhs80 = NULL;
  const mxArray *c2_rhs81 = NULL;
  const mxArray *c2_lhs81 = NULL;
  const mxArray *c2_rhs82 = NULL;
  const mxArray *c2_lhs82 = NULL;
  const mxArray *c2_rhs83 = NULL;
  const mxArray *c2_lhs83 = NULL;
  const mxArray *c2_rhs84 = NULL;
  const mxArray *c2_lhs84 = NULL;
  const mxArray *c2_rhs85 = NULL;
  const mxArray *c2_lhs85 = NULL;
  const mxArray *c2_rhs86 = NULL;
  const mxArray *c2_lhs86 = NULL;
  const mxArray *c2_rhs87 = NULL;
  const mxArray *c2_lhs87 = NULL;
  const mxArray *c2_rhs88 = NULL;
  const mxArray *c2_lhs88 = NULL;
  const mxArray *c2_rhs89 = NULL;
  const mxArray *c2_lhs89 = NULL;
  const mxArray *c2_rhs90 = NULL;
  const mxArray *c2_lhs90 = NULL;
  const mxArray *c2_rhs91 = NULL;
  const mxArray *c2_lhs91 = NULL;
  const mxArray *c2_rhs92 = NULL;
  const mxArray *c2_lhs92 = NULL;
  const mxArray *c2_rhs93 = NULL;
  const mxArray *c2_lhs93 = NULL;
  const mxArray *c2_rhs94 = NULL;
  const mxArray *c2_lhs94 = NULL;
  const mxArray *c2_rhs95 = NULL;
  const mxArray *c2_lhs95 = NULL;
  const mxArray *c2_rhs96 = NULL;
  const mxArray *c2_lhs96 = NULL;
  const mxArray *c2_rhs97 = NULL;
  const mxArray *c2_lhs97 = NULL;
  const mxArray *c2_rhs98 = NULL;
  const mxArray *c2_lhs98 = NULL;
  const mxArray *c2_rhs99 = NULL;
  const mxArray *c2_lhs99 = NULL;
  const mxArray *c2_rhs100 = NULL;
  const mxArray *c2_lhs100 = NULL;
  const mxArray *c2_rhs101 = NULL;
  const mxArray *c2_lhs101 = NULL;
  const mxArray *c2_rhs102 = NULL;
  const mxArray *c2_lhs102 = NULL;
  const mxArray *c2_rhs103 = NULL;
  const mxArray *c2_lhs103 = NULL;
  const mxArray *c2_rhs104 = NULL;
  const mxArray *c2_lhs104 = NULL;
  const mxArray *c2_rhs105 = NULL;
  const mxArray *c2_lhs105 = NULL;
  const mxArray *c2_rhs106 = NULL;
  const mxArray *c2_lhs106 = NULL;
  const mxArray *c2_rhs107 = NULL;
  const mxArray *c2_lhs107 = NULL;
  const mxArray *c2_rhs108 = NULL;
  const mxArray *c2_lhs108 = NULL;
  const mxArray *c2_rhs109 = NULL;
  const mxArray *c2_lhs109 = NULL;
  const mxArray *c2_rhs110 = NULL;
  const mxArray *c2_lhs110 = NULL;
  const mxArray *c2_rhs111 = NULL;
  const mxArray *c2_lhs111 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c2_rhs64, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs64, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "context", "context", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c2_rhs65, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs65, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c2_rhs66, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs66, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1366183842U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c2_rhs67, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs67, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1366183842U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c2_rhs68, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs68, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c2_rhs69, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs69, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c2_rhs70, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs70, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363731854U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c2_rhs71, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs71, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363732556U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c2_rhs72, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs72, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840326U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c2_rhs73, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs73, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c2_rhs74, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs74, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c2_rhs75, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs75, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c2_rhs76, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs76, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c2_rhs77, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs77, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840384U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c2_rhs78, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs78, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323192180U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c2_rhs79, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs79, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323192178U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c2_rhs80, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs80, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c2_rhs81, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs81, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840384U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c2_rhs82, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs82, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840378U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c2_rhs83, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs83, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323192178U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c2_rhs84, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs84, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c2_rhs85, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs85, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362283482U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c2_rhs86, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs86, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "name", "name", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m"), "resolved",
                  "resolved", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1319751568U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c2_rhs87, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs87, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/times.m"),
                  "context", "context", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fixpt_times"), "name",
                  "name", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fixpt_times.m"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289541246U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c2_rhs88, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs88, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("plus"), "name", "name", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531984U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c2_rhs89, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs89, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c2_rhs90, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs90, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c2_rhs91, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs91, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c2_rhs92, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs92, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c2_rhs93, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs93, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531938U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c2_rhs94, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs94, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("strcmpi"), "name", "name", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c2_rhs95, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs95, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c2_rhs96, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs96, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("minus"), "name", "name", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531984U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c2_rhs97, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs97, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286840396U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c2_rhs98, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs98, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c2_rhs99, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs99, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531980U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c2_rhs100, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs100, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c2_rhs101, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs101, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531938U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c2_rhs102, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs102, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("strcmpi"), "name", "name", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327440710U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c2_rhs103, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs103, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c2_rhs104, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs104, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c2_rhs105, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs105, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfloat"), "name", "name", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531978U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c2_rhs106, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs106, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "context", "context", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531940U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c2_rhs107, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs107, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346531958U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c2_rhs108, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs108, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289541276U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c2_rhs109, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs109, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289541254U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c2_rhs110, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs110, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360303946U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c2_rhs111, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c2_lhs111, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs111), "lhs", "lhs",
                  111);
  sf_mex_destroy(&c2_rhs64);
  sf_mex_destroy(&c2_lhs64);
  sf_mex_destroy(&c2_rhs65);
  sf_mex_destroy(&c2_lhs65);
  sf_mex_destroy(&c2_rhs66);
  sf_mex_destroy(&c2_lhs66);
  sf_mex_destroy(&c2_rhs67);
  sf_mex_destroy(&c2_lhs67);
  sf_mex_destroy(&c2_rhs68);
  sf_mex_destroy(&c2_lhs68);
  sf_mex_destroy(&c2_rhs69);
  sf_mex_destroy(&c2_lhs69);
  sf_mex_destroy(&c2_rhs70);
  sf_mex_destroy(&c2_lhs70);
  sf_mex_destroy(&c2_rhs71);
  sf_mex_destroy(&c2_lhs71);
  sf_mex_destroy(&c2_rhs72);
  sf_mex_destroy(&c2_lhs72);
  sf_mex_destroy(&c2_rhs73);
  sf_mex_destroy(&c2_lhs73);
  sf_mex_destroy(&c2_rhs74);
  sf_mex_destroy(&c2_lhs74);
  sf_mex_destroy(&c2_rhs75);
  sf_mex_destroy(&c2_lhs75);
  sf_mex_destroy(&c2_rhs76);
  sf_mex_destroy(&c2_lhs76);
  sf_mex_destroy(&c2_rhs77);
  sf_mex_destroy(&c2_lhs77);
  sf_mex_destroy(&c2_rhs78);
  sf_mex_destroy(&c2_lhs78);
  sf_mex_destroy(&c2_rhs79);
  sf_mex_destroy(&c2_lhs79);
  sf_mex_destroy(&c2_rhs80);
  sf_mex_destroy(&c2_lhs80);
  sf_mex_destroy(&c2_rhs81);
  sf_mex_destroy(&c2_lhs81);
  sf_mex_destroy(&c2_rhs82);
  sf_mex_destroy(&c2_lhs82);
  sf_mex_destroy(&c2_rhs83);
  sf_mex_destroy(&c2_lhs83);
  sf_mex_destroy(&c2_rhs84);
  sf_mex_destroy(&c2_lhs84);
  sf_mex_destroy(&c2_rhs85);
  sf_mex_destroy(&c2_lhs85);
  sf_mex_destroy(&c2_rhs86);
  sf_mex_destroy(&c2_lhs86);
  sf_mex_destroy(&c2_rhs87);
  sf_mex_destroy(&c2_lhs87);
  sf_mex_destroy(&c2_rhs88);
  sf_mex_destroy(&c2_lhs88);
  sf_mex_destroy(&c2_rhs89);
  sf_mex_destroy(&c2_lhs89);
  sf_mex_destroy(&c2_rhs90);
  sf_mex_destroy(&c2_lhs90);
  sf_mex_destroy(&c2_rhs91);
  sf_mex_destroy(&c2_lhs91);
  sf_mex_destroy(&c2_rhs92);
  sf_mex_destroy(&c2_lhs92);
  sf_mex_destroy(&c2_rhs93);
  sf_mex_destroy(&c2_lhs93);
  sf_mex_destroy(&c2_rhs94);
  sf_mex_destroy(&c2_lhs94);
  sf_mex_destroy(&c2_rhs95);
  sf_mex_destroy(&c2_lhs95);
  sf_mex_destroy(&c2_rhs96);
  sf_mex_destroy(&c2_lhs96);
  sf_mex_destroy(&c2_rhs97);
  sf_mex_destroy(&c2_lhs97);
  sf_mex_destroy(&c2_rhs98);
  sf_mex_destroy(&c2_lhs98);
  sf_mex_destroy(&c2_rhs99);
  sf_mex_destroy(&c2_lhs99);
  sf_mex_destroy(&c2_rhs100);
  sf_mex_destroy(&c2_lhs100);
  sf_mex_destroy(&c2_rhs101);
  sf_mex_destroy(&c2_lhs101);
  sf_mex_destroy(&c2_rhs102);
  sf_mex_destroy(&c2_lhs102);
  sf_mex_destroy(&c2_rhs103);
  sf_mex_destroy(&c2_lhs103);
  sf_mex_destroy(&c2_rhs104);
  sf_mex_destroy(&c2_lhs104);
  sf_mex_destroy(&c2_rhs105);
  sf_mex_destroy(&c2_lhs105);
  sf_mex_destroy(&c2_rhs106);
  sf_mex_destroy(&c2_lhs106);
  sf_mex_destroy(&c2_rhs107);
  sf_mex_destroy(&c2_lhs107);
  sf_mex_destroy(&c2_rhs108);
  sf_mex_destroy(&c2_lhs108);
  sf_mex_destroy(&c2_rhs109);
  sf_mex_destroy(&c2_lhs109);
  sf_mex_destroy(&c2_rhs110);
  sf_mex_destroy(&c2_lhs110);
  sf_mex_destroy(&c2_rhs111);
  sf_mex_destroy(&c2_lhs111);
}

static void c2_eml_fi_checkforconst(SFc2_MASHInstanceStruct *chartInstance)
{
}

static int64_T c2_uminus(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_xfi)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  int64_T c2_i7;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  c2_i7 = -c2_xfi;
  if (c2_i7 > 8589934591LL) {
    c2_i7 = 8589934591LL;
  } else {
    if (c2_i7 < -8589934592LL) {
      c2_i7 = -8589934592LL;
    }
  }

  return c2_i7;
}

static boolean_T c2_lt(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int64_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_a;
  int64_T c2_b;
  int64_T c2_b_a0;
  int64_T c2_b_b0;
  int64_T c2_a1;
  int64_T c2_b1;
  int64_T c2_b_a1;
  int64_T c2_b_b1;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  c2_a = c2_a0;
  c2_b = c2_b0;
  c2_b_a0 = c2_a;
  c2_b_b0 = c2_b;
  c2_a1 = c2_b_a0;
  c2_b1 = c2_b_b0;
  c2_b_a1 = c2_a1;
  c2_b_b1 = c2_b1;
  return c2_b_a1 < c2_b_b1;
}

static boolean_T c2_ge(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int64_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_a;
  int64_T c2_b;
  int64_T c2_b_a0;
  int64_T c2_b_b0;
  int64_T c2_a1;
  int64_T c2_b1;
  int64_T c2_b_a1;
  int64_T c2_b_b1;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  c2_a = c2_a0;
  c2_b = c2_b0;
  c2_b_a0 = c2_a;
  c2_b_b0 = c2_b;
  c2_a1 = c2_b_a0;
  c2_b1 = c2_b_b0;
  c2_b_a1 = c2_a1;
  c2_b_b1 = c2_b1;
  return c2_b_a1 >= c2_b_b1;
}

static void c2_strcmpi(SFc2_MASHInstanceStruct *chartInstance)
{
  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
}

static void c2_eml_scalar_eg(SFc2_MASHInstanceStruct *chartInstance)
{
}

static int128m_T c2_mtimes(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  int64_T c2_b_b0;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_b;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int64_T c2_b_b;
  int128m_T c2_r12;
  int128m_T c2_r13;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_b_b0 = c2_b0;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  c2_b = c2_b_b0;
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  c2_strcmpi(chartInstance);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_b_b = c2_b;
  c2_sLong2MultiWord(chartInstance, c2_b_b, &c2_r12.chunks[0U], 2);
  c2_sMultiWordShl(chartInstance, &c2_r12.chunks[0U], 2, 32U, &c2_r13.chunks[0U],
                   2);
  c2_MultiWordSignedWrap(chartInstance, &c2_r13.chunks[0U], 2, 60U,
    &c2_r12.chunks[0U]);
  return c2_r12;
}

static int128m_T c2_plus(SFc2_MASHInstanceStruct *chartInstance, real_T c2_a0,
  int128m_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  real_T c2_u;
  real_T c2_v;
  real_T c2_d7;
  int128m_T c2_r14;
  static int128m_T c2_r15 = { { 0ULL, 18446744073709551608ULL } };

  static int128m_T c2_r16 = { { MAX_uint64_T, 7ULL } };

  static int128m_T c2_r17 = { { 0ULL, 0ULL } };

  int128m_T c2_a;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int128m_T c2_r18;
  int128m_T c2_r19;
  int128m_T c2_r20;
  int128m_T c2_r21;
  int192m_T c2_r22;
  int192m_T c2_r23;
  int128m_T c2_r24;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_strcmpi(chartInstance);
  c2_u = c2_a0 * 9.007199254740992E+15;
  c2_v = muDoubleScalarAbs(c2_u);
  if (c2_v < 4.503599627370496E+15) {
    if (c2_v >= 0.5) {
      c2_d7 = muDoubleScalarFloor(c2_u + 0.5);
    } else {
      c2_d7 = c2_u * 0.0;
    }
  } else {
    c2_d7 = c2_u;
  }

  if (c2_d7 < 1.4757395258967641E+20) {
    if (c2_d7 >= -1.4757395258967641E+20) {
      c2_Double2MultiWord(chartInstance, c2_d7, &c2_r14.chunks[0U], 2);
    } else {
      c2_r14 = c2_r15;
    }
  } else if (c2_d7 >= 1.4757395258967641E+20) {
    c2_r14 = c2_r16;
  } else {
    c2_r14 = c2_r17;
  }

  c2_a = c2_r14;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_MultiWordSignedWrap(chartInstance, &c2_a.chunks[0U], 2, 59U,
    &c2_r18.chunks[0U]);
  c2_r19 = c2_b0;
  c2_MultiWordSignedWrap(chartInstance, &c2_r19.chunks[0U], 2, 59U,
    &c2_r20.chunks[0U]);
  c2_MultiWordAdd(chartInstance, &c2_r18.chunks[0U], &c2_r20.chunks[0U],
                  &c2_r21.chunks[0U], 2);
  c2_sMultiWord2MultiWord(chartInstance, &c2_r21.chunks[0U], 2, &c2_r22.chunks
    [0U], 3);
  c2_sMultiWordShl(chartInstance, &c2_r22.chunks[0U], 3, 59U, &c2_r23.chunks[0U],
                   3);
  c2_sMultiWord2sMultiWordSat(chartInstance, &c2_r23.chunks[0U], 3,
    &c2_r24.chunks[0U], 2);
  c2_sMultiWordShr(chartInstance, &c2_r24.chunks[0U], 2, 59U, &c2_r21.chunks[0U],
                   2);
  return c2_r21;
}

static boolean_T c2_b_ge(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  int128m_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_a;
  int64_T c2_b_a0;
  int64_T c2_a1;
  int64_T c2_b_a1;
  int128m_T c2_r25;
  int128m_T c2_r26;
  int128m_T c2_r27;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  c2_a = c2_a0;
  c2_b_a0 = c2_a;
  c2_a1 = c2_b_a0;
  c2_b_a1 = c2_a1;
  c2_sLong2MultiWord(chartInstance, c2_b_a1, &c2_r25.chunks[0U], 2);
  c2_sMultiWordShl(chartInstance, &c2_r25.chunks[0U], 2, 31U, &c2_r26.chunks[0U],
                   2);
  c2_MultiWordSignedWrap(chartInstance, &c2_r26.chunks[0U], 2, 32U,
    &c2_r27.chunks[0U]);
  c2_r25 = c2_b0;
  c2_MultiWordSignedWrap(chartInstance, &c2_r25.chunks[0U], 2, 32U,
    &c2_r26.chunks[0U]);
  return c2_sMultiWordGe(chartInstance, &c2_r27.chunks[0U], &c2_r26.chunks[0U],
    2);
}

static int64_T c2_b_plus(SFc2_MASHInstanceStruct *chartInstance, int64_T c2_a0,
  real_T c2_b0)
{
  int64_T c2_c;
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  int64_T c2_a;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  real_T c2_u;
  real_T c2_v;
  real_T c2_d8;
  int64_T c2_i8;
  int64_T c2_b;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int64_T c2_i9;
  int64_T c2_i10;
  int64_T c2_i11;
  int64_T c2_i12;
  int64_T c2_i13;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  c2_a = c2_a0;
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_strcmpi(chartInstance);
  c2_u = c2_b0 * 4.194304E+6;
  c2_v = muDoubleScalarAbs(c2_u);
  if (c2_v < 4.503599627370496E+15) {
    if (c2_v >= 0.5) {
      c2_d8 = muDoubleScalarFloor(c2_u + 0.5);
    } else {
      c2_d8 = c2_u * 0.0;
    }
  } else {
    c2_d8 = c2_u;
  }

  if (c2_d8 < 8.589934592E+9) {
    if (c2_d8 >= -8.589934592E+9) {
      c2_i8 = (int64_T)c2_d8;
    } else {
      c2_i8 = -8589934592LL;
    }
  } else if (c2_d8 >= 8.589934592E+9) {
    c2_i8 = 8589934591LL;
  } else {
    c2_i8 = 0LL;
  }

  c2_b = c2_i8;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_i9 = c2_a;
  c2_i10 = c2_b;
  if ((c2_i9 & 17179869184LL) != 0LL) {
    c2_i11 = c2_i9 | -17179869184LL;
  } else {
    c2_i11 = c2_i9 & 17179869183LL;
  }

  if ((c2_i10 & 17179869184LL) != 0LL) {
    c2_i12 = c2_i10 | -17179869184LL;
  } else {
    c2_i12 = c2_i10 & 17179869183LL;
  }

  c2_i13 = c2_i11 + c2_i12;
  if ((c2_i13 & 17179869184LL) != 0LL) {
    c2_c = c2_i13 | -17179869184LL;
  } else {
    c2_c = c2_i13 & 17179869183LL;
  }

  return c2_c;
}

static int128m_T c2_b_mtimes(SFc2_MASHInstanceStruct *chartInstance, int64_T
  c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  int64_T c2_b_b0;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  int64_T c2_b;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int64_T c2_b_b;
  int128m_T c2_r28;
  int128m_T c2_r29;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_b_b0 = c2_b0;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  c2_b = c2_b_b0;
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  c2_strcmpi(chartInstance);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_b_b = c2_b;
  c2_sLong2MultiWord(chartInstance, c2_b_b, &c2_r28.chunks[0U], 2);
  c2_sMultiWordShl(chartInstance, &c2_r28.chunks[0U], 2, 33U, &c2_r29.chunks[0U],
                   2);
  c2_MultiWordSignedWrap(chartInstance, &c2_r29.chunks[0U], 2, 58U,
    &c2_r28.chunks[0U]);
  return c2_r28;
}

static int128m_T c2_c_plus(SFc2_MASHInstanceStruct *chartInstance, real_T c2_a0,
  int128m_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  real_T c2_u;
  real_T c2_v;
  real_T c2_d9;
  int128m_T c2_r30;
  static int128m_T c2_r31 = { { 0ULL, 18446744073709551584ULL } };

  static int128m_T c2_r32 = { { MAX_uint64_T, 31ULL } };

  static int128m_T c2_r33 = { { 0ULL, 0ULL } };

  int128m_T c2_a;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int128m_T c2_r34;
  int128m_T c2_r35;
  int128m_T c2_r36;
  int128m_T c2_r37;
  int192m_T c2_r38;
  int192m_T c2_r39;
  int128m_T c2_r40;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_strcmpi(chartInstance);
  c2_u = c2_a0 * 1.8014398509481984E+16;
  c2_v = muDoubleScalarAbs(c2_u);
  if (c2_v < 4.503599627370496E+15) {
    if (c2_v >= 0.5) {
      c2_d9 = muDoubleScalarFloor(c2_u + 0.5);
    } else {
      c2_d9 = c2_u * 0.0;
    }
  } else {
    c2_d9 = c2_u;
  }

  if (c2_d9 < 5.9029581035870565E+20) {
    if (c2_d9 >= -5.9029581035870565E+20) {
      c2_Double2MultiWord(chartInstance, c2_d9, &c2_r30.chunks[0U], 2);
    } else {
      c2_r30 = c2_r31;
    }
  } else if (c2_d9 >= 5.9029581035870565E+20) {
    c2_r30 = c2_r32;
  } else {
    c2_r30 = c2_r33;
  }

  c2_a = c2_r30;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_MultiWordSignedWrap(chartInstance, &c2_a.chunks[0U], 2, 57U,
    &c2_r34.chunks[0U]);
  c2_r35 = c2_b0;
  c2_MultiWordSignedWrap(chartInstance, &c2_r35.chunks[0U], 2, 57U,
    &c2_r36.chunks[0U]);
  c2_MultiWordAdd(chartInstance, &c2_r34.chunks[0U], &c2_r36.chunks[0U],
                  &c2_r37.chunks[0U], 2);
  c2_sMultiWord2MultiWord(chartInstance, &c2_r37.chunks[0U], 2, &c2_r38.chunks
    [0U], 3);
  c2_sMultiWordShl(chartInstance, &c2_r38.chunks[0U], 3, 57U, &c2_r39.chunks[0U],
                   3);
  c2_sMultiWord2sMultiWordSat(chartInstance, &c2_r39.chunks[0U], 3,
    &c2_r40.chunks[0U], 2);
  c2_sMultiWordShr(chartInstance, &c2_r40.chunks[0U], 2, 57U, &c2_r37.chunks[0U],
                   2);
  return c2_r37;
}

static int128m_T c2_minus(SFc2_MASHInstanceStruct *chartInstance, int128m_T
  c2_a0, real_T c2_b0)
{
  const mxArray *c2_propVal = NULL;
  const mxArray *c2_errid = NULL;
  const mxArray *c2_b_propVal = NULL;
  const mxArray *c2_b_errid = NULL;
  real_T c2_u;
  real_T c2_v;
  real_T c2_d10;
  int128m_T c2_r41;
  static int128m_T c2_r42 = { { 0ULL, 18446744073709551608ULL } };

  static int128m_T c2_r43 = { { MAX_uint64_T, 7ULL } };

  static int128m_T c2_r44 = { { 0ULL, 0ULL } };

  int128m_T c2_b;
  const mxArray *c2_c_propVal = NULL;
  const mxArray *c2_c_errid = NULL;
  const mxArray *c2_d_propVal = NULL;
  const mxArray *c2_d_errid = NULL;
  const mxArray *c2_e_propVal = NULL;
  const mxArray *c2_e_errid = NULL;
  const mxArray *c2_f_propVal = NULL;
  const mxArray *c2_f_errid = NULL;
  const mxArray *c2_g_propVal = NULL;
  const mxArray *c2_g_errid = NULL;
  const mxArray *c2_h_propVal = NULL;
  const mxArray *c2_h_errid = NULL;
  const mxArray *c2_i_propVal = NULL;
  const mxArray *c2_i_errid = NULL;
  const mxArray *c2_j_propVal = NULL;
  const mxArray *c2_j_errid = NULL;
  int128m_T c2_r45;
  int128m_T c2_r46;
  int128m_T c2_r47;
  int192m_T c2_r48;
  int192m_T c2_r49;
  int128m_T c2_r50;
  sf_mex_destroy(&c2_propVal);
  sf_mex_destroy(&c2_errid);
  sf_mex_destroy(&c2_b_propVal);
  sf_mex_destroy(&c2_b_errid);
  c2_strcmpi(chartInstance);
  c2_u = c2_b0 * 9.007199254740992E+15;
  c2_v = muDoubleScalarAbs(c2_u);
  if (c2_v < 4.503599627370496E+15) {
    if (c2_v >= 0.5) {
      c2_d10 = muDoubleScalarFloor(c2_u + 0.5);
    } else {
      c2_d10 = c2_u * 0.0;
    }
  } else {
    c2_d10 = c2_u;
  }

  if (c2_d10 < 1.4757395258967641E+20) {
    if (c2_d10 >= -1.4757395258967641E+20) {
      c2_Double2MultiWord(chartInstance, c2_d10, &c2_r41.chunks[0U], 2);
    } else {
      c2_r41 = c2_r42;
    }
  } else if (c2_d10 >= 1.4757395258967641E+20) {
    c2_r41 = c2_r43;
  } else {
    c2_r41 = c2_r44;
  }

  c2_b = c2_r41;
  sf_mex_destroy(&c2_c_propVal);
  sf_mex_destroy(&c2_c_errid);
  sf_mex_destroy(&c2_d_propVal);
  sf_mex_destroy(&c2_d_errid);
  sf_mex_destroy(&c2_e_propVal);
  sf_mex_destroy(&c2_e_errid);
  sf_mex_destroy(&c2_f_propVal);
  sf_mex_destroy(&c2_f_errid);
  sf_mex_destroy(&c2_g_propVal);
  sf_mex_destroy(&c2_g_errid);
  sf_mex_destroy(&c2_h_propVal);
  sf_mex_destroy(&c2_h_errid);
  sf_mex_destroy(&c2_i_propVal);
  sf_mex_destroy(&c2_i_errid);
  sf_mex_destroy(&c2_j_propVal);
  sf_mex_destroy(&c2_j_errid);
  c2_r45 = c2_a0;
  c2_MultiWordSignedWrap(chartInstance, &c2_r45.chunks[0U], 2, 59U,
    &c2_r46.chunks[0U]);
  c2_MultiWordSignedWrap(chartInstance, &c2_b.chunks[0U], 2, 59U,
    &c2_r45.chunks[0U]);
  c2_MultiWordSub(chartInstance, &c2_r46.chunks[0U], &c2_r45.chunks[0U],
                  &c2_r47.chunks[0U], 2);
  c2_sMultiWord2MultiWord(chartInstance, &c2_r47.chunks[0U], 2, &c2_r48.chunks
    [0U], 3);
  c2_sMultiWordShl(chartInstance, &c2_r48.chunks[0U], 3, 59U, &c2_r49.chunks[0U],
                   3);
  c2_sMultiWord2sMultiWordSat(chartInstance, &c2_r49.chunks[0U], 3,
    &c2_r50.chunks[0U], 2);
  c2_sMultiWordShr(chartInstance, &c2_r50.chunks[0U], 2, 59U, &c2_r47.chunks[0U],
                   2);
  return c2_r47;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_c_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i14;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i14, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i14;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int64_T c2_u;
  const mxArray *c2_y = NULL;
  int64_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int64_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 8, 0U, 0U, 0U, 0), FALSE);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE), FALSE);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), FALSE);
  }

  return c2_mxArrayOutData;
}

static int64_T c2_d_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_quant_out, const char_T *c2_identifier)
{
  int64_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_quant_out),
    &c2_thisId);
  sf_mex_destroy(&c2_quant_out);
  return c2_y;
}

static int64_T c2_e_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int64_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int64_T c2_i15;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_b_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), FALSE);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), FALSE);
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_i15, 1, 8, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_i15;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_quant_out;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int64_T c2_y;
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_quant_out = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_quant_out),
      &c2_thisId);
    sf_mex_destroy(&c2_quant_out);
    *(int64_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_MASH, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_is_active_c2_MASH),
    &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_MASH);
  return c2_y;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_MASHInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static boolean_T c2_sMultiWordLt(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n)
{
  boolean_T c2_y;
  if (c2_sMultiWordCmp(chartInstance, c2_u1, c2_u2, c2_n) < 0) {
    c2_y = TRUE;
  } else {
    c2_y = FALSE;
  }

  return c2_y;
}

static int32_T c2_sMultiWordCmp(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n)
{
  uint64_T c2_su1;
  uint64_T c2_su2;
  int32_T c2_cmp;
  int32_T c2_i;
  uint64_T c2_u1i;
  uint64_T c2_u2i;
  c2_su1 = c2_u1[c2_n - 1] & 9223372036854775808ULL;
  c2_su2 = c2_u2[c2_n - 1] & 9223372036854775808ULL;
  if ((c2_su1 ^ c2_su2) != 0ULL) {
    if (c2_su1 != 0ULL) {
      c2_cmp = -1;
    } else {
      c2_cmp = 1;
    }
  } else {
    c2_cmp = 0;
    c2_i = c2_n;
    while ((c2_cmp == 0) && (c2_i > 0)) {
      c2_i--;
      c2_u1i = c2_u1[c2_i];
      c2_u2i = c2_u2[c2_i];
      if (c2_u1i != c2_u2i) {
        if (c2_u1i > c2_u2i) {
          c2_cmp = 1;
        } else {
          c2_cmp = -1;
        }
      }
    }
  }

  return c2_cmp;
}

static void c2_MultiWordSignedWrap(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[])
{
  int32_T c2_n1m1;
  int32_T c2_i;
  uint32_T c2_ns;
  uint64_T c2_mask;
  uint64_T c2_ys;
  c2_n1m1 = c2_n1 - 1;
  for (c2_i = 0; c2_i < c2_n1m1; c2_i++) {
    c2_y[c2_i] = c2_u1[c2_i];
  }

  c2_ns = 63U - c2_n2;
  c2_mask = 1ULL << c2_ns;
  if ((c2_u1[c2_n1m1] & c2_mask) != 0ULL) {
    c2_ys = MAX_uint64_T;
  } else {
    c2_ys = 0ULL;
  }

  c2_mask = (c2_mask << 1U) - 1ULL;
  c2_y[c2_n1m1] = (c2_u1[c2_n1m1] & c2_mask) | (~c2_mask & c2_ys);
}

static void c2_sMultiWordShl(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_nb;
  uint64_T c2_ys;
  int32_T c2_nc;
  uint64_T c2_u1i;
  int32_T c2_i;
  uint32_T c2_nl;
  int32_T c2_nc1;
  uint32_T c2_nr;
  int32_T c2_i1;
  uint64_T c2_yi;
  c2_nb = (int32_T)c2_n2 / 64;
  if ((c2_u1[c2_n1 - 1] & 9223372036854775808ULL) != 0ULL) {
    c2_ys = MAX_uint64_T;
  } else {
    c2_ys = 0ULL;
  }

  if (c2_nb > c2_n) {
    c2_nc = c2_n;
  } else {
    c2_nc = c2_nb;
  }

  c2_u1i = 0ULL;
  for (c2_i = 0; c2_i < c2_nc; c2_i++) {
    c2_y[c2_i] = c2_u1i;
  }

  if (c2_nb < c2_n) {
    c2_nl = c2_n2 - (uint32_T)c2_nb * 64U;
    c2_nc1 = c2_n1 + c2_nb;
    if (c2_nc1 > c2_n) {
      c2_nc1 = c2_n;
    }

    c2_nc1 -= c2_i;
    if (c2_nl > 0U) {
      c2_nr = 64U - c2_nl;
      for (c2_i1 = 0; c2_i1 < c2_nc1; c2_i1++) {
        c2_yi = c2_u1i >> c2_nr;
        c2_u1i = c2_u1[c2_i1];
        c2_y[c2_i] = c2_yi | c2_u1i << c2_nl;
        c2_i++;
      }

      if (c2_i < c2_n) {
        c2_y[c2_i] = c2_u1i >> c2_nr | c2_ys << c2_nl;
        c2_i++;
      }
    } else {
      for (c2_i1 = 0; c2_i1 < c2_nc1; c2_i1++) {
        c2_y[c2_i] = c2_u1[c2_i1];
        c2_i++;
      }
    }
  }

  while (c2_i < c2_n) {
    c2_y[c2_i] = c2_ys;
    c2_i++;
  }
}

static void c2_sLong2MultiWord(SFc2_MASHInstanceStruct *chartInstance, int64_T
  c2_u, uint64_T c2_y[], int32_T c2_n)
{
  uint64_T c2_yi;
  int32_T c2_i;
  c2_y[0] = (uint64_T)c2_u;
  if (c2_u < 0LL) {
    c2_yi = MAX_uint64_T;
  } else {
    c2_yi = 0ULL;
  }

  for (c2_i = 1; c2_i < c2_n; c2_i++) {
    c2_y[c2_i] = c2_yi;
  }
}

static void c2_Double2MultiWord(SFc2_MASHInstanceStruct *chartInstance, real_T
  c2_u1, uint64_T c2_y[], int32_T c2_n)
{
  boolean_T c2_isNegative;
  int32_T c2_currExp;
  real_T c2_yn;
  int32_T c2_msl;
  uint64_T c2_yi;
  uint64_T c2_cb;
  int32_T c2_i;
  real_T c2_y0;
  int32_T c2_prevExp;
  real_T c2_yd;
  uint64_T c2_u1i;
  c2_isNegative = (c2_u1 < 0.0);
  c2_yn = frexp(c2_u1, &c2_currExp);
  if (c2_currExp <= 0) {
    c2_msl = -1;
  } else {
    c2_msl = (c2_currExp - 1) / 64;
  }

  c2_yi = 0ULL;
  c2_cb = 1ULL;
  for (c2_i = c2_msl + 1; c2_i < c2_n; c2_i++) {
    c2_y[c2_i] = c2_yi;
  }

  if (c2_isNegative) {
    c2_y0 = -c2_yn;
  } else {
    c2_y0 = c2_yn;
  }

  c2_prevExp = 64 * c2_msl;
  for (c2_i = c2_msl; c2_i >= 0; c2_i--) {
    c2_y0 = ldexp(c2_y0, c2_currExp - c2_prevExp);
    c2_yd = muDoubleScalarFloor(c2_y0);
    c2_y0 -= c2_yd;
    if (c2_i < c2_n) {
      c2_y[c2_i] = (uint64_T)c2_yd;
    }

    c2_currExp = c2_prevExp;
    c2_prevExp -= 64;
  }

  if (c2_isNegative) {
    for (c2_i = 0; c2_i < c2_n; c2_i++) {
      c2_u1i = ~c2_y[c2_i];
      c2_yi = c2_u1i + c2_cb;
      c2_y[c2_i] = c2_yi;
      if (c2_yi < c2_u1i) {
        c2_cb = 1ULL;
      } else {
        c2_cb = 0ULL;
      }
    }
  }
}

static void c2_sMultiWordShr(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_nb;
  int32_T c2_i;
  uint64_T c2_ys;
  int32_T c2_nc;
  uint32_T c2_nr;
  uint32_T c2_nl;
  uint64_T c2_u1i;
  int32_T c2_i1;
  uint64_T c2_yi;
  c2_nb = (int32_T)c2_n2 / 64;
  c2_i = 0;
  if ((c2_u1[c2_n1 - 1] & 9223372036854775808ULL) != 0ULL) {
    c2_ys = MAX_uint64_T;
  } else {
    c2_ys = 0ULL;
  }

  if (c2_nb < c2_n1) {
    c2_nc = c2_n + c2_nb;
    if (c2_nc > c2_n1) {
      c2_nc = c2_n1;
    }

    c2_nr = c2_n2 - (uint32_T)c2_nb * 64U;
    if (c2_nr > 0) {
      c2_nl = 64U - c2_nr;
      c2_u1i = c2_u1[c2_nb];
      for (c2_i1 = c2_nb + 1; c2_i1 < c2_nc; c2_i1++) {
        c2_yi = c2_u1i >> c2_nr;
        c2_u1i = c2_u1[c2_i1];
        c2_y[c2_i] = c2_yi | c2_u1i << c2_nl;
        c2_i++;
      }

      c2_yi = c2_u1i >> c2_nr;
      if (c2_nc < c2_n1) {
        c2_u1i = c2_u1[c2_nc];
      } else {
        c2_u1i = c2_ys;
      }

      c2_y[c2_i] = c2_yi | c2_u1i << c2_nl;
      c2_i++;
    } else {
      for (c2_i1 = c2_nb; c2_i1 < c2_nc; c2_i1++) {
        c2_y[c2_i] = c2_u1[c2_i1];
        c2_i++;
      }
    }
  }

  while (c2_i < c2_n) {
    c2_y[c2_i] = c2_ys;
    c2_i++;
  }
}

static void c2_sMultiWord2sMultiWordSat(SFc2_MASHInstanceStruct *chartInstance,
  const uint64_T c2_u1[], int32_T c2_n1, uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_nm1;
  int32_T c2_n1m1;
  uint64_T c2_ys;
  boolean_T c2_doSaturation = FALSE;
  int32_T c2_i;
  uint64_T c2_yi;
  int32_T c2_nc;
  c2_nm1 = c2_n - 1;
  c2_n1m1 = c2_n1 - 1;
  if ((c2_u1[c2_n1m1] & 9223372036854775808ULL) != 0ULL) {
    c2_ys = MAX_uint64_T;
  } else {
    c2_ys = 0ULL;
  }

  if (c2_n1 > c2_n) {
    c2_doSaturation = (((c2_u1[c2_n1m1] ^ c2_u1[c2_nm1]) &
                        9223372036854775808ULL) != 0ULL);
    c2_i = c2_n1m1;
    while ((!c2_doSaturation) && (c2_i >= c2_n)) {
      c2_doSaturation = (c2_u1[c2_i] != c2_ys);
      c2_i--;
    }
  }

  if (c2_doSaturation) {
    c2_yi = ~c2_ys;
    for (c2_i = 0; c2_i < c2_nm1; c2_i++) {
      c2_y[c2_i] = c2_yi;
    }

    c2_y[c2_i] = c2_yi ^ 9223372036854775808ULL;
  } else {
    c2_nc = (int32_T)sf_MIN(c2_n1, c2_n);
    for (c2_i = 0; c2_i < c2_nc; c2_i++) {
      c2_y[c2_i] = c2_u1[c2_i];
    }

    while (c2_i < c2_n) {
      c2_y[c2_i] = c2_ys;
      c2_i++;
    }
  }
}

static void c2_sMultiWord2MultiWord(SFc2_MASHInstanceStruct *chartInstance,
  const uint64_T c2_u1[], int32_T c2_n1, uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_nm;
  int32_T c2_i;
  uint64_T c2_u1i;
  c2_nm = (int32_T)sf_MIN(c2_n1, c2_n);
  for (c2_i = 0; c2_i < c2_nm; c2_i++) {
    c2_y[c2_i] = c2_u1[c2_i];
  }

  if (c2_n > c2_n1) {
    if ((c2_u1[c2_n1 - 1] & 9223372036854775808ULL) != 0ULL) {
      c2_u1i = MAX_uint64_T;
    } else {
      c2_u1i = 0ULL;
    }

    for (c2_i = c2_nm; c2_i < c2_n; c2_i++) {
      c2_y[c2_i] = c2_u1i;
    }
  }
}

static void c2_MultiWordSub(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_i;
  uint64_T c2_u1i;
  uint64_T c2_borrow = 0ULL;
  uint64_T c2_yi;
  uint64_T c2_borrow1;
  uint64_T c2_borrow2;
  for (c2_i = 0; c2_i < c2_n; c2_i++) {
    c2_u1i = c2_u1[c2_i];
    c2_yi = (c2_u1i - c2_u2[c2_i]) - c2_borrow;
    c2_y[c2_i] = c2_yi;
    if (c2_yi >= c2_u1i) {
      c2_borrow1 = 1ULL;
    } else {
      c2_borrow1 = 0ULL;
    }

    if (c2_yi > c2_u1i) {
      c2_borrow2 = 1ULL;
    } else {
      c2_borrow2 = 0ULL;
    }

    if (c2_borrow != 0ULL) {
      c2_borrow = c2_borrow1;
    } else {
      c2_borrow = c2_borrow2;
    }
  }
}

static int64_T c2_MultiWord2sLong(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u[])
{
  return (int64_T)c2_u[0];
}

static void c2_sMultiWordShrNear(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], int32_T c2_n1, uint32_T c2_n2, uint64_T c2_y[], int32_T c2_n)
{
  uint32_T c2_n2m1;
  int32_T c2_nb;
  uint32_T c2_nrb;
  uint64_T c2_mask;
  boolean_T c2_doNearest;
  uint64_T c2_ys;
  int32_T c2_i;
  c2_n2m1 = c2_n2 - 1U;
  c2_nb = (int32_T)c2_n2m1 / 64;
  if (c2_nb < c2_n1) {
    c2_nrb = c2_n2m1 - (uint32_T)(c2_nb * 64);
    c2_mask = 1ULL << c2_nrb;
    c2_doNearest = ((c2_u1[c2_nb] & c2_mask) != 0ULL);
  } else {
    if ((c2_u1[c2_n1 - 1] & 9223372036854775808ULL) != 0ULL) {
      c2_ys = MAX_uint64_T;
    } else {
      c2_ys = 0ULL;
    }

    c2_doNearest = (c2_ys != 0ULL);
  }

  c2_sMultiWordShr(chartInstance, c2_u1, c2_n1, c2_n2, c2_y, c2_n);
  c2_i = 0;
  while (c2_doNearest && (c2_i < c2_n)) {
    c2_y[c2_i]++;
    if (c2_y[c2_i] != 0ULL) {
      c2_doNearest = FALSE;
    }

    c2_i++;
  }
}

static void c2_MultiWordAdd(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], uint64_T c2_y[], int32_T c2_n)
{
  int32_T c2_i;
  uint64_T c2_u1i;
  uint64_T c2_carry = 0ULL;
  uint64_T c2_yi;
  uint64_T c2_carry1;
  uint64_T c2_carry2;
  for (c2_i = 0; c2_i < c2_n; c2_i++) {
    c2_u1i = c2_u1[c2_i];
    c2_yi = (c2_u1i + c2_u2[c2_i]) + c2_carry;
    c2_y[c2_i] = c2_yi;
    if (c2_yi <= c2_u1i) {
      c2_carry1 = 1ULL;
    } else {
      c2_carry1 = 0ULL;
    }

    if (c2_yi < c2_u1i) {
      c2_carry2 = 1ULL;
    } else {
      c2_carry2 = 0ULL;
    }

    if (c2_carry != 0ULL) {
      c2_carry = c2_carry1;
    } else {
      c2_carry = c2_carry2;
    }
  }
}

static boolean_T c2_sMultiWordGe(SFc2_MASHInstanceStruct *chartInstance, const
  uint64_T c2_u1[], const uint64_T c2_u2[], int32_T c2_n)
{
  boolean_T c2_y;
  if (c2_sMultiWordCmp(chartInstance, c2_u1, c2_u2, c2_n) >= 0) {
    c2_y = TRUE;
  } else {
    c2_y = FALSE;
  }

  return c2_y;
}

static void init_dsm_address_info(SFc2_MASHInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_MASH_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3931277153U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1195646032U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3770088200U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2034976447U);
}

mxArray *sf_c2_MASH_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("mdnaFYVCpDxT61ztXNsJv");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(34));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(-22));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(34));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(-22));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_MASH_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_MASH_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_MASH(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"quant_out\",},{M[8],M[0],T\"is_active_c2_MASH\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_MASH_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_MASHInstanceStruct *chartInstance;
    chartInstance = (SFc2_MASHInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MASHMachineNumber_,
           2,
           1,
           1,
           3,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_MASHMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_MASHMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MASHMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"quant_in");
          _SFD_SET_DATA_PROPS(1,2,0,1,"quant_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"nLev");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,3,0,6,0,1,0,2,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,432);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,132,-1,151);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,209,-1,227);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,281,-1,294);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,385,-1,407);
        _SFD_CV_INIT_EML_SATURATION(0,1,4,388,-1,398);
        _SFD_CV_INIT_EML_SATURATION(0,1,5,53,-1,71);
        _SFD_CV_INIT_EML_IF(0,1,0,98,115,171,432);
        _SFD_CV_INIT_EML_IF(0,1,1,171,192,247,432);
        _SFD_CV_INIT_EML_IF(0,1,2,304,360,-1,420);
        _SFD_CV_INIT_EML_FOR(0,1,0,256,271,428);

        {
          static int condStart[] = { 307, 334 };

          static int condEnd[] = { 330, 360 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,307,360,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT32,0,NULL,1,1,34,0,1,-22,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_INT32,0,NULL,1,1,34,0,1,-22,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          int64_T *c2_quant_in;
          int64_T *c2_quant_out;
          real_T *c2_nLev;
          c2_nLev = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_quant_out = (int64_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_quant_in = (int64_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_quant_in);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_quant_out);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_nLev);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MASHMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "6IR9B8DbcxdtMvnCob4URF";
}

static void sf_opaque_initialize_c2_MASH(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_MASHInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
  initialize_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_MASH(void *chartInstanceVar)
{
  enable_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_MASH(void *chartInstanceVar)
{
  disable_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_MASH(void *chartInstanceVar)
{
  sf_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_MASH(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_MASH((SFc2_MASHInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_MASH();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_MASH(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_MASH();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_MASH((SFc2_MASHInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_MASH(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_MASH(S);
}

static void sf_opaque_set_sim_state_c2_MASH(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_MASH(S, st);
}

static void sf_opaque_terminate_c2_MASH(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_MASHInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MASH_optimization_info();
    }

    finalize_c2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_MASH((SFc2_MASHInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_MASH(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_MASH((SFc2_MASHInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_MASH(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MASH_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(911589715U));
  ssSetChecksum1(S,(846890378U));
  ssSetChecksum2(S,(2132904162U));
  ssSetChecksum3(S,(465028264U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_MASH(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_MASH(SimStruct *S)
{
  SFc2_MASHInstanceStruct *chartInstance;
  chartInstance = (SFc2_MASHInstanceStruct *)utMalloc(sizeof
    (SFc2_MASHInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_MASHInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_MASH;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_MASH;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_MASH;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_MASH;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_MASH;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_MASH;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_MASH;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_MASH;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_MASH;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_MASH;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_MASH;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_MASH_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_MASH(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_MASH(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_MASH(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_MASH_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
