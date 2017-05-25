/**
 * @file C-Utils commons
 *
 * @author     CieNTi
 */

#ifndef H_CU_COMMONS
#define H_CU_COMMONS

/* ----------------------------------------
 * Macros
 */
/** Define PRINTF outside this file to override use of 'printf()' function */
#if !defined(PRINTF)
#define PRINTF printf
#endif

/** IAR compiler uses this to force-store affected variable data into flash */
#if !defined(__root)
#define __root
#endif

/** This macro should be a function that returns a single character */
#if !defined(GETACHAR)
#define GETACHAR fgetc(stdin)
#endif

#endif /* H_CU_COMMONS */
