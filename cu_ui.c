/**
 * @file Some tools to ease recurrent tasks
 *
 * @author     CieNTi
 */

#include <stdio.h>
#include <stdbool.h>

#include "cu_ui.h"

/* ------------------------------------------------------------------------
 * --------------------- Read cu_ui.h for documentation -------------------
 * ------------------------------------------------------------------------ */

int display_menu(const struct menu_item_st *menu,
                 menu_action **cb,
                 bool wait_only)
{
  static char menu_choice;
  static bool menu_disabled;
  static int res;
  static int i;

  /* Function fails by default */
  res = 1;
  menu_disabled = false;
  menu_choice = 0;

  /* Wait the choice */
  while (1)
  {
    /* Wait for user interaction only or print menu too? */
    i = 0;
    do
    {
      if ((!wait_only) && (!menu_disabled))
      {
        /* Last element, used to exit, is put away from user menu entries */
        if (menu[i].cb == NULL)
        {
          PRINTF("\n");
        }

        /* Print menu entry */
        PRINTF(" %c. %s\n", menu[i].key, menu[i].text);
      }
    }
    while (menu[i++].cb != NULL);

    /* Tell the user to interact xD */
    if (!menu_disabled)
    {
      PRINTF("\n-- Select an option: ");
    }

    /* menu_disabled is used to disable menu+question for 1 cycle */
    menu_disabled = false;

    /* Use a custom function if no stdin is present */
    menu_choice = GETACHAR;
    if (menu_choice == '\n' || menu_choice == '\r')
    {
      menu_disabled = true;
      continue;
    }

    /* Assuming both non-blocking and blocking situations: 0 = 'no key' */
    if (menu_choice != 0)
    {
      /* Search for the pressed key in menu elements keys */
      i = 0;
      do
      {
        /* Assign a menu action if choice is found */
        if (menu[i].key == menu_choice)
        {
          /* Exit search loop after action is triggered */
          *cb = menu[i].cb;
          res = 0;
          break;
        }
      }
      while (menu[i++].cb != NULL);

      /* Wrong key? */
      if ((i > 1) && (menu[i - 1].cb == NULL))
      {
        PRINTF("\nxx Key %c unknown, please try again\n\n", menu_choice);
      }
      else
      {
        /* Exit main wait loop */
        break;
      }
    }
    else
    {
      menu_disabled = true;
    }

    /* TODO/IMPROVEMENT: OS wait to avoid high CPU use */
    // OS_wait_function();
  }

  /* Avoid action assignation in a fail situation */
  if (res)
  {
    *cb = NULL;
  }

  /* 0 ok, otherwise fails */
  return res;
}
