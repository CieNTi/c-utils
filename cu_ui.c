/**
 * @file Some tools to ease recurrent tasks
 *
 * @author     CieNTi
 * @version    1.1.0
 */

#include <stdio.h>
#include <stdbool.h>

#include "cu_ui.h"

/* ----------------------------------------
 * Module variables
 */
/**
 * Entries calls hierarchy index
 */
static int menu_idx = 0;

/**
 * Entries calls hierarchy array
 */
static menu_action *menu_lst[MAX_MENU_LST];

/* ------------------------------------------------------------------------
 * --------------------- Read cu_ui.h for documentation -------------------
 * ------------------------------------------------------------------------ */

/**/
int m_entry_header(void)
{
  return 0;
}

/**/
int display_menu(const struct menu_item_st *menu,
                 int *sel_item,
                 bool wait_only)
{
  char menu_choice = 0;
  bool menu_disabled = false;
  bool header_sent;
  int i;

  /* Function fails by default */
  int res = 1;

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

/**/
int start_hmenu(menu_action *first_parent)
{
  /* Always failing function by default */
  int res = 1;

  /* Reset list */
  for (menu_idx = MAX_MENU_LST; menu_idx > 0; menu_idx--)
  {
    menu_lst[menu_idx - 1] = NULL;
  }

  /* First element */
  menu_lst[menu_idx++] = first_parent;

  /*
   * Starting menu parsing:
   * ---------------------
   * Every menu_lst call will update menu_lst[menu_idx] before exit. If no more
   * action is required (exit or endpoint entry) a NULL is used.
   * Index check and update is done here, and NULL is used as end-of-list.
   */
  res = 0;
  while ((menu_idx > 0) &&                     // Enough low side index?
         (menu_idx <= MAX_MENU_LST) &&         // Enough high side index ?
         (menu_lst[menu_idx - 1] != NULL) &&   // Is a function ?
         (!(res = menu_lst[menu_idx - 1]())))  // Call the function! No error ?
  {
    /* Ok, safe zone, let's check what to do */
    if (menu_lst[menu_idx] == NULL)
    {
      /* Go back if possible */
      if (menu_idx > 0)
      {
        menu_idx--;
      }
    }
    else
    {
      /* New member! */
      if (++menu_idx == MAX_MENU_LST)
      {
        PRINTF("\nxx Max depth reached, please increase MAX_MENU_LST\n");
        PRINTF("xx Entering an infinite loop here now ...\n");
        while (1)
        {
          /* Dear programmer:
           * -- Update MAX_MENU_LST and try again! --
           * Thanks
           */
        }
      }

      /* Ensures a brand new callback */
      menu_lst[menu_idx] = NULL;
    }
  }

  /* Errors? */
  if (res)
  {
    PRINTF("\nxx Exiting with errors:\n");
    PRINTF("xx menu_idx: %i, menu_lst[menu_idx]: %08X\n",
           menu_idx,
           menu_lst[menu_idx]);
  }

  /* 0 ok, otherwise fails */
  return res;
}

/**/
int display_hmenu(const struct menu_item_st *menu)
{
  /* Always failing function by default */
  int res = 1;

  /* Selected option holder */
  int sel_item = 0;

  /* Show menu and wait for user interaction */
  res = display_menu(menu, &sel_item, false);

  /* Call action if all went fine */
  if (!res)
  {
    menu_lst[menu_idx] = menu[sel_item].cb;
  }

  /* 0 ok, otherwise fail */
  return res;
}
