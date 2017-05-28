/**
 * @file Some tools to ease recurrent tasks
 *
 * @author     CieNTi
 * @version    1.0.0
 */

#include <stdio.h>
#include <stdbool.h>

#include "cu_ui.h"

/* ------------------------------------------------------------------------
 * --------------------- Read cu_ui.h for documentation -------------------
 * ------------------------------------------------------------------------ */

int m_entry_header(void)
{
  return 0;
}

int display_menu(const struct menu_item_st *menu,
                 int *sel_item,
                 bool wait_only)
{
  static char menu_choice;
  static bool menu_disabled;
  static bool header_sent;
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
    header_sent = false;
    do
    {
      if ((!wait_only) && (!menu_disabled))
      {
        /* Heading element */
        if (menu[i].key == M_H && menu[i].cb == m_entry_header)
        {
          /* Head text */
          if (!header_sent)
          {
            PRINTF("\n\n#*");
          }

          PRINTF("\n#  %s\n", menu[i].text);

          if (!header_sent)
          {
            PRINTF("#*\n\n");
          }

          header_sent = true;
          continue;
        }

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

    /* Default selected item is the last, exit one, so the callback still can
     * be checked against NULL */
    *sel_item = i - 1;

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
          *sel_item = i;
          res = 0;
          break;
        }
      }
      while (menu[i++].cb != NULL);

      /* Wrong key? */
      if ((i > 1) && (menu[i - 1].cb == NULL))
      {
        PRINTF("\nxx Key %c unknown, please try again\n\n\n\n", menu_choice);
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

  /* 0 ok, otherwise fails */
  return res;
}
