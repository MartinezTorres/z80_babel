#include <common.h>

#include <sieve.h>
#include <quicksort.h>

static T_TEST_RESULT test_results_global[12];

static const T_TEST_CASE test_cases_sieve_50k_1[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},

	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_end = sieve_of_eratosthenes_d_1_end_50k
	},
	
	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_end = sieve_of_eratosthenes_zig_end_50k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_end = sieve_of_eratosthenes_rust_end_50k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__50k,
		.fn_end = sieve_of_eratosthenes_fortran_end__50k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__1k,
		.fn_end = sieve_of_eratosthenes_fortran_end__1k
	},
};

static const T_TEST test_sieve_50k_1 = {
	
	.name = "Sieve of Eratosthenes 50k - 1",
	.test_cases = test_cases_sieve_50k_1,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};

static const T_TEST_CASE test_cases_sieve_50k_2[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k
	},

	
	{
		.name = "C v2",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_2_50k,
		.fn_end = sieve_of_eratosthenes_c_2_end_50k
	},

	{
		.name = "C v3",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_end = sieve_of_eratosthenes_c_3_end_50k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},

	{
		.name = "C++ v2",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_2_50k,
		.fn_end = sieve_of_eratosthenes_cc_2_end_50k
	},

	{
		.name = "C++ v3",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_50k
	},


	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_end = sieve_of_eratosthenes_d_1_end_50k
	},
	
	{
		.name = "D v2",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_2_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_2_50k,
		.fn_end = sieve_of_eratosthenes_d_2_end_50k
	},

	{
		.name = "D v3",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_3_50k,
		.fn_end = sieve_of_eratosthenes_d_3_end_50k
	},

	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_end = sieve_of_eratosthenes_zig_end_50k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_end = sieve_of_eratosthenes_rust_end_50k
	},
};

static const T_TEST test_sieve_50k_2 = {
	
	.name = "Sieve of Eratosthenes 50k - 2",
	.test_cases = test_cases_sieve_50k_2,
	.test_results = test_results_global,
	.n_test_cases = 11,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};

static const T_TEST_CASE test_cases_sieve_50k_3[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},

	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_50k,
		.fn_end = sieve_of_eratosthenes_d_1_end_50k
	},
	
	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_end = sieve_of_eratosthenes_zig_end_50k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_end = sieve_of_eratosthenes_rust_end_50k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__50k,
		.fn_end = sieve_of_eratosthenes_fortran_end__50k
	},

	{
		.name = "C v1 MDL",
		.segment = ML_SEGMENT_B(sieve_c_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k_mdl_ro
	},

	{
		.name = "C++ v1 MDL",
		.segment = ML_SEGMENT_B(sieve_cc_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k_mdl_ro
	},

	{
		.name = "D v1 MDL",
		.segment = ML_SEGMENT_B(sieve_d_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_d_1_end_50k_mdl_ro
	},
	
	{
		.name = "ZIG MDL",
		.segment = ML_SEGMENT_B(sieve_zig_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_zig_end_50k_mdl_ro
	},
	
	{
		.name = "RUST MDL",
		.segment = ML_SEGMENT_B(sieve_rs_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_rust_end_50k_mdl_ro
	},

	{
		.name = "F. MDL",
		.segment = ML_SEGMENT_B(sieve_f_50k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_50k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__50k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_fortran_end__50k_mdl_ro
	},
};

static const T_TEST test_sieve_50k_3 = {
	
	.name = "Sieve of Eratosthenes 50k - 3",
	.test_cases = test_cases_sieve_50k_3,
	.test_results = test_results_global,
	.n_test_cases = 12,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};

static const T_TEST_CASE test_cases_sieve_1k_1[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_end = sieve_of_eratosthenes_c_1_end_1k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k
	},

	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_end = sieve_of_eratosthenes_d_1_end_1k
	},
	
	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_end = sieve_of_eratosthenes_zig_end_1k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_end = sieve_of_eratosthenes_rust_end_1k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__1k,
		.fn_end = sieve_of_eratosthenes_fortran_end__1k
	},
};

static const T_TEST test_sieve_1k_1 = {
	
	.name = "Sieve of Eratosthenes 1k - 1",
	.test_cases = test_cases_sieve_1k_1,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_1k_2[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_end = sieve_of_eratosthenes_c_1_end_1k
	},

	
	{
		.name = "C v2",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_2_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_2_1k,
		.fn_end = sieve_of_eratosthenes_c_2_end_1k
	},

	{
		.name = "C v3",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_end = sieve_of_eratosthenes_c_3_end_1k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k
	},

	{
		.name = "C++ v2",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_2_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_2_1k,
		.fn_end = sieve_of_eratosthenes_cc_2_end_1k
	},

	{
		.name = "C++ v3",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_1k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_1k
	},


	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_end = sieve_of_eratosthenes_d_1_end_1k
	},
	
	{
		.name = "D v2",
		.segment = ML_SEGMENT_B(sieve_d_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_2_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_2_1k,
		.fn_end = sieve_of_eratosthenes_d_2_end_1k
	},

	{
		.name = "D v3",
		.segment = ML_SEGMENT_B(sieve_d_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_3_1k,
		.fn_end = sieve_of_eratosthenes_d_3_end_1k
	},

	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_end = sieve_of_eratosthenes_zig_end_1k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_end = sieve_of_eratosthenes_rust_end_1k
	},
};

static const T_TEST test_sieve_1k_2 = {
	
	.name = "Sieve of Eratosthenes 1k - 2",
	.test_cases = test_cases_sieve_1k_2,
	.test_results = test_results_global,
	.n_test_cases = 11,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};

static const T_TEST_CASE test_cases_sieve_1k_3[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_end = sieve_of_eratosthenes_c_1_end_1k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k
	},

	{
		.name = "D v1",
		.segment = ML_SEGMENT_B(sieve_d_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_1k,
		.fn_end = sieve_of_eratosthenes_d_1_end_1k
	},
	
	{
		.name = "ZIG",
		.segment = ML_SEGMENT_B(sieve_zig_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_end = sieve_of_eratosthenes_zig_end_1k
	},
	
	{
		.name = "RUST",
		.segment = ML_SEGMENT_B(sieve_rs_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_end = sieve_of_eratosthenes_rust_end_1k
	},

	{
		.name = "FORTRAN",
		.segment = ML_SEGMENT_B(sieve_f_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__1k,
		.fn_end = sieve_of_eratosthenes_fortran_end__1k
	},

	{
		.name = "C v1 MDL",
		.segment = ML_SEGMENT_B(sieve_c_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_c_1_end_1k_mdl_ro
	},

	{
		.name = "C++ v1 MDL",
		.segment = ML_SEGMENT_B(sieve_cc_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k_mdl_ro
	},

	{
		.name = "D v1 MDL",
		.segment = ML_SEGMENT_B(sieve_d_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_d_1_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_d_1_1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_d_1_end_1k_mdl_ro
	},
	
	{
		.name = "ZIG MDL",
		.segment = ML_SEGMENT_B(sieve_zig_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_zig_end_1k_mdl_ro
	},
	
	{
		.name = "RUST MDL",
		.segment = ML_SEGMENT_B(sieve_rs_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_rust_end_1k_mdl_ro
	},

	{
		.name = "F. MDL",
		.segment = ML_SEGMENT_B(sieve_f_1k_mdl_ro),
		.fn_test = (T_FN)sieve_of_eratosthenes_fortran_1k_mdl_ro,
		.fn_begin = (T_FN)sieve_of_eratosthenes_fortran__1k_mdl_ro,
		.fn_end = sieve_of_eratosthenes_fortran_end__1k_mdl_ro
	},
};

static const T_TEST test_sieve_1k_3 = {
	
	.name = "Sieve of Eratosthenes 1k - 3",
	.test_cases = test_cases_sieve_1k_3,
	.test_results = test_results_global,
	.n_test_cases = 12,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_c_1[] = {
	
	{
		.name = "C 1k",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_1k,
		.fn_end = sieve_of_eratosthenes_c_1_end_1k
	},

	{
		.name = "C 2k",
		.segment = ML_SEGMENT_B(sieve_c_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_2k,
		.fn_end = sieve_of_eratosthenes_c_1_end_2k
	},

	{
		.name = "C 5k",
		.segment = ML_SEGMENT_B(sieve_c_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_5k,
		.fn_end = sieve_of_eratosthenes_c_1_end_5k
	},

	{
		.name = "C 10k",
		.segment = ML_SEGMENT_B(sieve_c_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_10k,
		.fn_end = sieve_of_eratosthenes_c_1_end_10k
	},

	{
		.name = "C 20k",
		.segment = ML_SEGMENT_B(sieve_c_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_20k,
		.fn_end = sieve_of_eratosthenes_c_1_end_20k
	},

	{
		.name = "C 50k",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_1_50k,
		.fn_end = sieve_of_eratosthenes_c_1_end_50k
	},
};

static const T_TEST test_sieve_c_1 = {
	
	.name = "Sieve of Eratosthenes (C v1)",
	.test_cases = test_cases_sieve_c_1,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_c_3[] = {
	

	{
		.name = "C 1k",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_end = sieve_of_eratosthenes_c_3_end_1k
	},

	{
		.name = "C 2k",
		.segment = ML_SEGMENT_B(sieve_c_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_2k,
		.fn_end = sieve_of_eratosthenes_c_3_end_2k
	},

	{
		.name = "C 5k",
		.segment = ML_SEGMENT_B(sieve_c_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_5k,
		.fn_end = sieve_of_eratosthenes_c_3_end_5k
	},

	{
		.name = "C 10k",
		.segment = ML_SEGMENT_B(sieve_c_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_10k,
		.fn_end = sieve_of_eratosthenes_c_3_end_10k
	},

	{
		.name = "C 20k",
		.segment = ML_SEGMENT_B(sieve_c_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_20k,
		.fn_end = sieve_of_eratosthenes_c_3_end_20k
	},

	{
		.name = "C 50k",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_end = sieve_of_eratosthenes_c_3_end_50k
	},

};

static const T_TEST test_sieve_c_3 = {
	
	.name = "Sieve of Eratosthenes (C v3)",
	.test_cases = test_cases_sieve_c_3,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};



static const T_TEST_CASE test_cases_sieve_cpp_1[] = {
	
	{
		.name = "C++ 1k",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k
	},

	{
		.name = "C++ 2k",
		.segment = ML_SEGMENT_B(sieve_cc_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_2k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_2k
	},

	{
		.name = "C++ 5k",
		.segment = ML_SEGMENT_B(sieve_cc_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_5k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_5k
	},

	{
		.name = "C++ 10k",
		.segment = ML_SEGMENT_B(sieve_cc_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_10k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_10k
	},

	{
		.name = "C++ 20k",
		.segment = ML_SEGMENT_B(sieve_cc_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_20k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_20k
	},

	{
		.name = "C++ 50k",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},
};

static const T_TEST test_sieve_cpp_1 = {
	
	.name = "Sieve of Eratosthenes (C++ v1)",
	.test_cases = test_cases_sieve_cpp_1,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_cpp_3[] = {
	

	{
		.name = "C++ 1k",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_1k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_1k
	},

	{
		.name = "C++ 2k",
		.segment = ML_SEGMENT_B(sieve_cc_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_2k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_2k
	},

	{
		.name = "C++ 5k",
		.segment = ML_SEGMENT_B(sieve_cc_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_5k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_5k
	},

	{
		.name = "C++ 10k",
		.segment = ML_SEGMENT_B(sieve_cc_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_10k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_10k
	},

	{
		.name = "C++ 20k",
		.segment = ML_SEGMENT_B(sieve_cc_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_20k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_20k
	},

	{
		.name = "C++ 50k",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_3_50k,
		.fn_end = sieve_of_eratosthenes_cc_3_end_50k
	},

};

static const T_TEST test_sieve_cpp_3 = {
	
	.name = "Sieve of Eratosthenes (C++ v3)",
	.test_cases = test_cases_sieve_cpp_3,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};



static const T_TEST_CASE test_cases_sieve_d_1[] = {
	
	{
		.name = "D 1k",
		.segment = ML_SEGMENT_B(sieve_cc_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_1k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_1k
	},

	{
		.name = "D 2k",
		.segment = ML_SEGMENT_B(sieve_cc_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_2k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_2k
	},

	{
		.name = "D 5k",
		.segment = ML_SEGMENT_B(sieve_cc_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_5k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_5k
	},

	{
		.name = "D 10k",
		.segment = ML_SEGMENT_B(sieve_cc_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_10k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_10k
	},

	{
		.name = "D 20k",
		.segment = ML_SEGMENT_B(sieve_cc_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_20k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_20k
	},

	{
		.name = "D 50k",
		.segment = ML_SEGMENT_B(sieve_cc_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_cc_1_50k,
		.fn_end = sieve_of_eratosthenes_cc_1_end_50k
	},
};

static const T_TEST test_sieve_d_1 = {
	
	.name = "Sieve of Eratosthenes (D v1)",
	.test_cases = test_cases_sieve_d_1,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_d_3[] = {
	

	{
		.name = "D 1k",
		.segment = ML_SEGMENT_B(sieve_c_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_1k,
		.fn_end = sieve_of_eratosthenes_c_3_end_1k
	},

	{
		.name = "D 2k",
		.segment = ML_SEGMENT_B(sieve_c_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_2k,
		.fn_end = sieve_of_eratosthenes_c_3_end_2k
	},

	{
		.name = "D 5k",
		.segment = ML_SEGMENT_B(sieve_c_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_5k,
		.fn_end = sieve_of_eratosthenes_c_3_end_5k
	},

	{
		.name = "D 10k",
		.segment = ML_SEGMENT_B(sieve_c_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_10k,
		.fn_end = sieve_of_eratosthenes_c_3_end_10k
	},

	{
		.name = "D 20k",
		.segment = ML_SEGMENT_B(sieve_c_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_20k,
		.fn_end = sieve_of_eratosthenes_c_3_end_20k
	},

	{
		.name = "D 50k",
		.segment = ML_SEGMENT_B(sieve_c_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_c_3_50k,
		.fn_end = sieve_of_eratosthenes_c_3_end_50k
	},

};

static const T_TEST test_sieve_d_3 = {
	
	.name = "Sieve of Eratosthenes (D v3)",
	.test_cases = test_cases_sieve_d_3,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};


static const T_TEST_CASE test_cases_sieve_rust[] = {
	
	{
		.name = "RUST 1k",
		.segment = ML_SEGMENT_B(sieve_rs_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_1k,
		.fn_end = sieve_of_eratosthenes_rust_end_1k
	},

	{
		.name = "RUST 2k",
		.segment = ML_SEGMENT_B(sieve_rs_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_2k,
		.fn_end = sieve_of_eratosthenes_rust_end_2k
	},

	{
		.name = "RUST 5k",
		.segment = ML_SEGMENT_B(sieve_rs_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_5k,
		.fn_end = sieve_of_eratosthenes_rust_end_5k
	},

	{
		.name = "RUST 10k",
		.segment = ML_SEGMENT_B(sieve_rs_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_10k,
		.fn_end = sieve_of_eratosthenes_rust_end_10k
	},

	{
		.name = "RUST 20k",
		.segment = ML_SEGMENT_B(sieve_rs_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_20k,
		.fn_end = sieve_of_eratosthenes_rust_end_20k
	},

	{
		.name = "RUST 50k",
		.segment = ML_SEGMENT_B(sieve_rs_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_rust_50k,
		.fn_end = sieve_of_eratosthenes_rust_end_50k
	},
};

static const T_TEST test_sieve_rust = {
	
	.name = "Sieve of Eratosthenes (RUST)",
	.test_cases = test_cases_sieve_rust,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};

static const T_TEST_CASE test_cases_sieve_zig[] = {
	
	{
		.name = "ZIG 1k",
		.segment = ML_SEGMENT_B(sieve_zig_1k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_1k,
		.fn_end = sieve_of_eratosthenes_zig_end_1k
	},

	{
		.name = "ZIG 2k",
		.segment = ML_SEGMENT_B(sieve_zig_2k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_2k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_2k,
		.fn_end = sieve_of_eratosthenes_zig_end_2k
	},

	{
		.name = "ZIG 5k",
		.segment = ML_SEGMENT_B(sieve_zig_5k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_5k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_5k,
		.fn_end = sieve_of_eratosthenes_zig_end_5k
	},

	{
		.name = "ZIG 10k",
		.segment = ML_SEGMENT_B(sieve_zig_10k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_10k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_10k,
		.fn_end = sieve_of_eratosthenes_zig_end_10k
	},

	{
		.name = "ZIG 20k",
		.segment = ML_SEGMENT_B(sieve_zig_20k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_20k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_20k,
		.fn_end = sieve_of_eratosthenes_zig_end_20k
	},

	{
		.name = "ZIG 50k",
		.segment = ML_SEGMENT_B(sieve_zig_50k),
		.fn_test = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_begin = (T_FN)sieve_of_eratosthenes_zig_50k,
		.fn_end = sieve_of_eratosthenes_zig_end_50k
	},
};

static const T_TEST test_sieve_zig = {
	
	.name = "Sieve of Eratosthenes (ZIG)",
	.test_cases = test_cases_sieve_zig,
	.test_results = test_results_global,
	.n_test_cases = 6,
	.fn_reference = run_reference_sieve_of_erastosthenes,
	.fn_verify = (T_FN_VERIFY_TEST)verify_sieve_of_erastosthenes,
	.fn_run_test = (T_FN_CALL_TEST)run_test_sieve_of_erastosthenes
};



static const T_TEST_CASE test_cases_quicksort_50k_1[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(quicksort_c_50k),
		.fn_test = (T_FN)quicksort_c_50k,
		.fn_begin = (T_FN)quicksort_c_50k,
		.fn_end = quicksort_c_end_50k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(quicksort_cc_50k),
		.fn_test = (T_FN)quicksort_cc_50k,
		.fn_begin = (T_FN)quicksort_cc_50k,
		.fn_end = quicksort_cc_end_50k
	},


	{
		.name = "C v1 MDL",
		.segment = ML_SEGMENT_B(quicksort_c_50k_mdl_ro),
		.fn_test = (T_FN)quicksort_c_50k_mdl_ro,
		.fn_begin = (T_FN)quicksort_c_50k_mdl_ro,
		.fn_end = quicksort_c_end_50k_mdl_ro
	},

	{
		.name = "C++ v1 MDL",
		.segment = ML_SEGMENT_B(quicksort_cc_50k_mdl_ro),
		.fn_test = (T_FN)quicksort_cc_50k_mdl_ro,
		.fn_begin = (T_FN)quicksort_cc_50k_mdl_ro,
		.fn_end = quicksort_cc_end_50k_mdl_ro
	},

};

static const T_TEST test_quicksort_50k_1 = {
	
	.name = "Quicksort 50k - 1",
	.test_cases = test_cases_quicksort_50k_1,
	.test_results = test_results_global,
	.n_test_cases = 4,
	.fn_reference = run_reference_quicksort,
	.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
	.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
};



static const T_TEST_CASE test_cases_quicksort_1k_1[] = {
	
	{
		.name = "C v1",
		.segment = ML_SEGMENT_B(quicksort_c_1k),
		.fn_test = (T_FN)quicksort_c_1k,
		.fn_begin = (T_FN)quicksort_c_1k,
		.fn_end = quicksort_c_end_1k
	},

	{
		.name = "C++ v1",
		.segment = ML_SEGMENT_B(quicksort_cc_1k),
		.fn_test = (T_FN)quicksort_cc_1k,
		.fn_begin = (T_FN)quicksort_cc_1k,
		.fn_end = quicksort_cc_end_1k
	},


	{
		.name = "C v1 MDL",
		.segment = ML_SEGMENT_B(quicksort_c_1k_mdl_ro),
		.fn_test = (T_FN)quicksort_c_1k_mdl_ro,
		.fn_begin = (T_FN)quicksort_c_1k_mdl_ro,
		.fn_end = quicksort_c_end_1k_mdl_ro
	},

	{
		.name = "C++ v1 MDL",
		.segment = ML_SEGMENT_B(quicksort_cc_1k_mdl_ro),
		.fn_test = (T_FN)quicksort_cc_1k_mdl_ro,
		.fn_begin = (T_FN)quicksort_cc_1k_mdl_ro,
		.fn_end = quicksort_cc_end_1k_mdl_ro
	},

};

static const T_TEST test_quicksort_1k_1 = {
	
	.name = "Quicksort 1k - 1",
	.test_cases = test_cases_quicksort_1k_1,
	.test_results = test_results_global,
	.n_test_cases = 4,
	.fn_reference = run_reference_quicksort,
	.fn_verify = (T_FN_VERIFY_TEST)verify_quicksort,
	.fn_run_test = (T_FN_CALL_TEST)run_test_quicksort
};


const uint8_t n_tests = 16;
const T_TEST *all_tests[] = {
	&test_quicksort_1k_1,
	&test_quicksort_50k_1,
	
	&test_sieve_1k_1,
	&test_sieve_50k_1,
	
	&test_sieve_50k_2,
	&test_sieve_1k_2,
	
	&test_sieve_50k_3,
	&test_sieve_1k_3,
	
	&test_sieve_c_1,
	&test_sieve_c_3,

	&test_sieve_cpp_1,
	&test_sieve_cpp_3,

	&test_sieve_d_1,
	&test_sieve_d_3,

	&test_sieve_rust,

	&test_sieve_zig,
};

