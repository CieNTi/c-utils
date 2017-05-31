/**
 * @file Some tools to ease recurrent tasks
 *
 * @author     CieNTi
 * @version    1.3.3
 */

#include "cu_ui.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

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
static menu_action *menu_lst[MAX_HMENU_LST];

/* ------------------------------------------------------------------------
 * --------------------- Read cu_ui.h for documentation -------------------
 * ------------------------------------------------------------------------ */

/**/
int m_entry_header(void)
{
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
    menu_choice = FGETC;
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
  for (menu_idx = MAX_HMENU_LST; menu_idx > 0; menu_idx--)
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
         (menu_idx <= MAX_HMENU_LST) &&        // Enough high side index ?
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
      if (++menu_idx == MAX_HMENU_LST)
      {
        PRINTF("\nxx Max depth reached, please increase MAX_HMENU_LST\n");
        PRINTF("xx Entering an infinite loop here now ...\n");
        while (1)
        {
          /* Dear programmer:
           * -- Update MAX_HMENU_LST and try again! --
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

/**/
char *uart_fgets(char *str, int num)
{
  int i = 0;

  while (((str[i] = FGETC) != '\n') && (str[i] != '\r'))
  {
    /* Go out 0x00! */
    if (str[i] == 0x00)
    {
      continue;
    }

    #if defined(M_FGETS_ECHO_ON)
    /* We don't want backspace or delete to be printed if there is no data */
    if (((i == 0) && (str[i] == '\b')) ||
        ((i == 0) && (str[i] == 0x7F)))
    {
      continue;
    }

    if (((str[i] > 0x1F)  && // 0x20 = Space ' '
         (str[i] < 0x7F)) || // 0x7E = Tilde '~'
        (str[i] == '\b')  || // Backspace and delete keys are allowed
        (str[i] == 0x7F))    // once accepted by first filter
    {
      PRINTF("%c", str[i]);
    }

    #endif

    /* Let's see if user was a good boy */
    switch (str[i])
    {
      /* Backspace and Del key (Del can be an escape sequence -> will exit) */
      case 0x7F:
      case '\b':
        i = (i > 0)?i - 1:0;
        str[i] = 0x00;
        break;

      /* Escape key */
      case 0x1B:
        /* Exit with EOF equivalent (not exactly an error, just canceled) */
        return NULL;
        break;

      default:
        /* Printable/typeable characters */
        if ((str[i] > 0x1F) &&  // 0x20 = Space ' '
            (str[i] < 0x7F))    // 0x7E = Tilde '~'
        {
          /* As EOF is not an option to end parsing, '\n' is needed. Therefore
           * string will end in ['\n', 0x00] */
          if (i < (num - 2))
          {
            /* Accept it */
            i++;
          }
        }
        break;
    }
  }

  #if defined(M_FGETS_ECHO_ON)
  PRINTF("\n");
  #endif

  /* Ensure valid string with newline (overwriting carriage return, if one) */
  str[i] = '\n';
  str[++i] = 0x00;

  /* All fine */
  return str;
}


int display_question(char *question, enum menu_data_type dtype, ...)
{
  int res = 1;
  char tmp_str[Q_ANSWER_SIZE] = { 0x00 };
  char *dst_string = tmp_str;
  void *scan_data = NULL;
  char *scan_fmt = NULL;
  int max_data = Q_ANSWER_SIZE;

  /* Create and initialize variable argument list */
  static va_list args;
  va_start(args, dtype);
  scan_data = va_arg(args, void *);
  if (dtype == m_type_string)
  {
    /* If expecting a string, use it directly */
    dst_string = scan_data;
    max_data = va_arg(args, int);
  }
  va_end(args);

  /* Display question and wait the user to type something */
  PRINTF("\n-- %s: ", question);
  if (FGETS(dst_string, max_data) == dst_string)
  {
    res = 0;
    switch (dtype)
    {
      case m_type_int:
        scan_fmt = "%i";
        break;
      case m_type_float:
        scan_fmt = "%f";
        break;
      case m_type_string:
        break;
      default:
        /* Oops */
        res = 1;
        break;
    }

    /* Last error check */
    if ((scan_fmt != NULL )&& (sscanf(tmp_str, scan_fmt, scan_data) == 0))
    {
      /* No elements, invalid scan */
      res = 1;
    }
  }
  return res;
}