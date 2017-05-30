/**
 * @file C-Utils commons
 *
 * @author     CieNTi
 * @version    1.1.0
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
#if !defined(FGETC)
  #define FGETC fgetc(stdin)

  /* fgetc() echoes every character, so disable it in cu_ui uart_fgets() */
  #if !defined(M_FGETS_ECHO_ON)
    #define M_FGETS_ECHO_ON
  #endif
#endif

#endif /* H_CU_COMMONS */
