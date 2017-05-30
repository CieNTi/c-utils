/**
 * @file C-Utils configuration file
 *
 * This file is meant to be used as a preinclude file so every module have
 * full access to every symbol described here
 *
 * @author     CieNTi
 * @version    1.0.0
 */

#ifndef H_CU_CONFIG
#define H_CU_CONFIG

/* ----------------------------------------
 * Commons
 */

/** Function to use as fgetc(). Default: fgetc() <cu_commons.h> */
//#define FGETC uart_fgetc()

/** Function to use as fgets(). Default: fgets() <cu_ui.h> */
#define FGETS(x,y) uart_fgets(x,y)


/* ----------------------------------------
 * Mocks
 */

/** Test non-block fgetc(), simulating a non-wait UART-like */
//#define CU_MOCK_FGETC_NONBLOCK


/* ----------------------------------------
 * User interface
 */

/** Enable character echo when using uart_fgets() */
#define M_FGETS_ECHO_ON

/** Max allowed depth level when processing hierarchical menus. Default: 8 */
#define MAX_HMENU_LST 8

#endif /* H_CU_CONFIG */
