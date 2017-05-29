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

  /* Good boy */
  res = 0;
  return res;
}

/***/
int m_entry_nr2(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr2\n");

  /* Good boy */
  res = 0;
  return res;
}

/***/
int m_entry_nr3(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr3\n");

  /* Good boy */
  res = 0;
  return res;
}

/***/
int m_entry_nr4(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr4\n");

  /* Good boy */
  res = 0;
  return res;
}

/***/
int m_entry_nr5(void)
{
  int res = 1;
  PRINTF("\n>> Called m_entry_nr5\n");

  /* Good boy */
  res = 0;
  return res;
}


/* -------------------------
 * Menu creation and control
 */
/***/
int show_main_menu()
{
  /* Always failing function by default */
  static int res = 1;
  res = 1;

  /* Selected option holder */
  static int sel_item = 0;
  sel_item = 0;

  /* Options */
  __root static const struct menu_item_st menu[] =
  {
    { M_H, "First, more decorated header",    m_entry_header },
    { M_H, "Not the first header, less deco", m_entry_header },
    { '1', "User entry nr.1",                 m_entry_nr1    },
    { '2', "User entry nr.2",                 m_entry_nr2    },
    { '3', "User entry nr.3",                 m_entry_nr3    },
    { '4', "User entry nr.4",                 m_entry_nr4    },
    { '5', "User entry nr.5",                 m_entry_nr5    },
    { M_H, "Not the first header, less deco", m_entry_header },
    { '6', "User entry nr.1",                 m_entry_nr1    },
    { '7', "User entry nr.2",                 m_entry_nr2    },
    { '8', "User entry nr.3",                 m_entry_nr3    },
    { '9', "User entry nr.4",                 m_entry_nr4    },
    { '0', "User entry nr.5",                 m_entry_nr5    },
    { 'x', "Exit",                            NULL           }
  };

  /* Show menu and wait for user interaction */
  res = display_menu(menu, &sel_item, false);

  /* Call action if all went fine */
  if ((!res) && (menu[sel_item].cb != NULL))
  {
    res = menu[sel_item].cb();
  }

  /* 0 ok, otherwise fails */
  return res;
}


/* --------------------------------------
 * main loop: Ask for an action and exits
 */

int ui_menu_main(void);

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

  /* Hierarchical menu creation and control example */
  res = start_hmenu(ui_menu_main);

  PRINTF("Exiting now ...\n\n");

  return res;
}

/* ---------------------- Hierarchical menu members ---------------------- */

/*
 * --------------------------
 * *** Menus and submenus ***
 * --------------------------
 */

int ui_submenu_nr1(void);
int ui_submenu_nr2(void);

/***/
int ui_menu_main(void)
{
  /* Options */
  __root static const struct menu_item_st menu[] =
  {
    { M_H, "Hierarchical menu",       m_entry_header },

    { '1', "Go to submenu #1",        ui_submenu_nr1 },
    { '2', "Go to submenu #2",        ui_submenu_nr2 },

    { 'x', "Exit",                    NULL           }
  };

  /* 0 ok, otherwise fail */
  return display_hmenu(menu);
}

/***/
int ui_submenu_nr1(void)
{
  /* Options */
  __root static const struct menu_item_st menu[] =
  {
    { M_H, "Submenu #1",              m_entry_header },

    { '1', "Call to end-point nr.1",  m_entry_nr1    },
    { '2', "Call to end-point nr.2",  m_entry_nr2    },
    { '3', "Call to end-point nr.3",  m_entry_nr3    },
    { '4', "Call to end-point nr.4",  m_entry_nr4    },

    { 'x', "Exit",                    NULL           }
  };

  /* 0 ok, otherwise fail */
  return display_hmenu(menu);
}

/***/
int ui_submenu_nr2(void)
{
  /* Options */
  __root static const struct menu_item_st menu[] =
  {
    { M_H, "Submenu #2",              m_entry_header },

    { '1', "Call to end-point nr.1",  m_entry_nr1    },
    { '2', "Call to end-point nr.2",  m_entry_nr2    },
    { '3', "Call to end-point nr.3",  m_entry_nr3    },
    { '4', "Call to end-point nr.4",  m_entry_nr4    },
    { '5', "Call to end-point nr.5",  m_entry_nr5    },

    { 'x', "Exit",                    NULL           }
  };

  /* 0 ok, otherwise fail */
  return display_hmenu(menu);
}
