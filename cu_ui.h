/**
 * @file C-Utils User Interface
 *
 * @author     CieNTi
 */

#ifndef H_CU_UI
#define H_CU_UI

#include "cu_commons.h"

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

#endif /* H_CU_UI */
