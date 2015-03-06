/**
  *@file    testfunc.c
  *@date	2014-01-07
  *@author	klinuxer001
  */
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

extern int max(int, int);
/*
 * 初始化测试组件
 */
int init_suite1(void)
{
   return 0;
}

/*
 * 注销测试组件
 */
int clean_suite1(void)
{
   return 0;
}

void test_max( void )
{
	CU_ASSERT( 3 == max(3,2));
}

void test_min( void )
{
	CU_ASSERT( 2 == min(3,2));
}

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
	{
		return CU_get_error();
	}

   /* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if((NULL == CU_add_test(pSuite, "test of max()", test_max) ) ||
		(NULL == CU_add_test(pSuite, "test of min()", test_min) ))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
//	CU_console_run_tests();
//	CU_curses_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
