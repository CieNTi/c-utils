/**
 * @file Test: User menu using cu_ui module
 *
 * @author     CieNTi
 */

#include <stdio.h>
#include <stdbool.h>
#include "cu_ui.h"

/* ------------
 * Menu actions
 */
/***/
int m_entry_nr1(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr1\n");
  return res;
}

/***/
int m_entry_nr2(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr2\n");
  return res;
}

/***/
int m_entry_nr3(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr3\n");
  return res;
}

/***/
int m_entry_nr4(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr4\n");
  return res;
}

/***/
int m_entry_nr5(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr5\n");
  return res;
}


/* -------------------------
 * Menu creation and handler
 */
/***/
int show_main_menu()
{
  /* Always failing function by default */
  static int res = 1;
  res = 1;

  /* Action to be called after menu wait */
  static menu_action *cb;
  cb = NULL;

  /* Options */
  __root static const struct menu_item_st menu[] =
  {
    { '1', "User entry nr.1", m_entry_nr1 },
    { '2', "User entry nr.2", m_entry_nr2 },
    { '3', "User entry nr.3", m_entry_nr3 },
    { '4', "User entry nr.4", m_entry_nr4 },
    { '5', "User entry nr.5", m_entry_nr5 },
    { 'x', "Exit",            NULL        }
  };

  /* Head text */
  PRINTF("\n\n\n"
         "##* ---------------------\n");
  PRINTF("#   User menu example   #\n");
  PRINTF("--------------------- *##\n\n");

  /* Show menu and wait for user interaction */
  res = display_menu(menu, &cb, false);

  /* Call action if all went fine */
  if ((!res) && (cb != NULL))
  {
    res = cb();
  }

  /* 0 ok, otherwise fails */
  return res;
}


/*
 * main loop: Ask for an action and exits
 */
/***/
int main()
{
  /* Always fail by default */
  static int res = 1;
  res = 1;

  while (res)
  {
    PRINTF(">> Sleeping for 1s\n");
    usleep(1000000);
    res = show_main_menu();
  }

  PRINTF("Exiting now ...\n\n");

  return res;
}
