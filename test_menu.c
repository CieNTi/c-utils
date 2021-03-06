/**
 * @file Test: User menu using cu_ui module
 *
 * @author     CieNTi
 */

#include "cu_ui.h"

#include <stdio.h>
#include <stdbool.h>

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


/* ------------------------------ main loop ------------------------------ */
int main()
{
  /* Always fail by default */
  static int res = 1;
  res = 1;

  #if defined(CU_MOCK_IS_ALIVE)
  PRINTF("\n***\n* C-Utils mocking enabled\n***\n\n");
  #endif

  #if defined(CU_MOCK_IS_ALIVE) && defined(CU_MOCK_FGETC_NONBLOCK)
  set_fgetc_mock_type(CU_MOCK_TYPE_FLOAT);
  #endif


  /* Test for comparing fgets() with uart_fgets() */
  char my_str[15];
  PRINTF("Expecting string here: ");
  if (FGETS(my_str, 15) == my_str)
  {
    /* Received */
    PRINTF("String received: %s\n", my_str);
  }


  /* Test parsed string against a float */
  float my_float = 0;
  PRINTF("sscanf() exits with 0x%X\n",
         sscanf(my_str, "%f", &my_float));

  PRINTF("my_float is %f\n", my_float);


  /* Questions example */
  int q_int = 0;
  float q_float = 0.0;
  char q_str[10];

  display_question("Type an integer", m_type_int, &q_int);
  PRINTF("q_int is: %i\n", q_int);

  display_question("Type a float", m_type_float, &q_float);
  PRINTF("q_float is: %f\n", q_float);

  display_question("Type a string", m_type_string, &q_str, 10);
  PRINTF("q_str is: %s\n", q_str);


  /* Simple menu example */
  /* Uncomment for infinite loop */
  //res = 0;
  //while (!res)
  {
    PRINTF(">> Sleeping for 1s\n");
    usleep(1000000);
    res = show_main_menu();
  }

  /* Hierarchical menu creation and control example */
  res = start_hmenu(ui_menu_main);

  PRINTF("\nExiting now ...\n\n");

  return res;
}

