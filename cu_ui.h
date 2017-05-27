/**
 * @file C-Utils User Interface
 *
 * @author     CieNTi
 * @version    0.2.0
 */

#ifndef H_CU_UI
#define H_CU_UI

#include "cu_commons.h"

/* ----------------------------------------
 * Macros
 */
/** Character used as header id, it should not be any typeable character */
#if !defined(M_H)
#define M_H (char)0xFF
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
  char key;   	   /**< Key requested to trigger the menu action */
  char *text; 	   /**< Text displayed to user */
  menu_action *cb; /**< Action triggered when the user hit the required key */
};

/* ----------------------------------------
 * File functions
 */
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
                 menu_action **cb,
                 bool wait_only);

/**
 * @brief      Dummy function to use with a menu header (and never called)
 *
 * @return     0 ok, always
 */
int m_entry_header(void);
#endif /* H_CU_UI */
