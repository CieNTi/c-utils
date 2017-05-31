/**
 * @file C-Utils User Interface
 *
 * @author     CieNTi
 * @version    1.3.3
 */

#ifndef H_CU_UI
#define H_CU_UI

#include "cu_commons.h"

#include <stdbool.h>

/* ----------------------------------------
 * Macros
 */
/** Character used as header id, it should not be any typeable character */
#if !defined(M_H)
#define M_H (char)0xFF
#endif

/** Max hierarchical menu depth level */
#if !defined(MAX_HMENU_LST)
#define MAX_HMENU_LST 8
#endif

/** Function to use as fgets() */
#if !defined(FGETS)
#define FGETS(x,y) fgets(x,y,stdin)
#endif

/** Allocated number of char type inside display_question() */
#if !defined(Q_ANSWER_SIZE)
#define Q_ANSWER_SIZE 25
#endif

/* ----------------------------------------
 * Types, Structs and Enums
 */
/**
 * Every menu action have to be this type of function
 */
typedef int (menu_action)(void);

/**
 * @brief      Menu entry structure
 */
struct menu_item_st
{
  char key;        /**< Key requested to trigger the menu action */
  char *text;      /**< Text displayed to user */
  menu_action *cb; /**< Action triggered when the user hit the required key */
};

/**
 * @brief      Type of data to write or read within the user interface
 */
enum menu_data_type
{
  m_type_int,
  m_type_float,
  m_type_string
};

/* ----------------------------------------
 * File functions
 */
/**
 * @brief      Dummy function to use with a menu header (and never called)
 *
 * @return     0 ok, always
 */
int m_entry_header(void);

/**
 * @brief      Display (or not) a menu, and wait for user interaction
 *
 * @param[in]  menu       The menu array
 * @param[in]  cb         Pointer to menu action to trigger (NULL if nothing)
 * @param[in]  wait_only  Set to true if only the user-wait is needed
 *
 * @return     0 ok, otherwise fail
 */
int display_menu(const struct menu_item_st *menu,
                 int *sel_item,
                 bool wait_only);

/**
 * @brief      Controls hierarchical menu without deep calling
 *
 *             The final actions will be called inside the menu action,
 *             therefore at least `stack + 1` is used there
 *
 * @param[in]  First menu to be shown, exiting this one exits the menu loop
 *
 * @return     0 ok, otherwise fail
 */
int start_hmenu(menu_action *first_parent);

/**
 * @brief      Display + update helper to ease (sub)menu maintenance
 *
 *             Ensures every member do the right job
 *
 * @param[in]  menu  pointer to first element of menu items array
 *
 * @return     0 ok, otherwise fail
 */
int display_hmenu(const struct menu_item_st *menu);

/**
 * @brief      Simulates standard library `fgets(str, num, stdin)` but
 *             allowing a non-blocking uart getchar-like interface.
 *
 *             The main difference resides in the way the EOF (0x00) is
 *             parsed, a continuous non-blocking environment (polling with no
 *             IRQ/ISR) returns 0x00 when no character is received. It can be
 *             useful in an embedded C code without FILE streams support.
 *             **Useless if using real fgetc()/fgets() functions are
 *             available**
 *
 * @param      str   Pointer to an array of chars where the string read is
 *                   copied.
 * @param[in]  num   Maximum number of characters to be copied into str
 *                   (including the terminating null-character).
 *
 * @return     This function returns str on success, and NULL on error
 */
char *uart_fgets(char *str, int num);

/**
 * @brief      Display a question and wait the user to type an answer
 *
 *             When typing, use ESCAPE key to cancel or press ENTER to accept.
 *             If dtype expects a string, it'll have a trailing newline + NULL
 *             characters, see { '\n', 0x00 }
 *             
 *             Ask for an integer:
 *             - display_question("Type an integer", m_type_int, &q_int);
 *             
 *             Ask for a float:
 *             - display_question("Type a float", m_type_float, &q_float);
 *             
 *             Ask for a string, be careful to set the limit
 *             - display_question("Type a string", m_type_string, &q_str, 10);
 *
 * @param      question   String to display
 * @param[in]  dtype      Data type to parse
 * @param[in]  <unnamed>  Variable argument list
 *
 * @return     0 ok, otherwise fail
 */
int display_question(char *question, enum menu_data_type dtype, ...);

#endif /* H_CU_UI */
