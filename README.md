# C-Utils

Some C utilities to ease my daily coding


# `cu_ui`: C-Utils User Interface


## Display question and wait for typed text

Invoking `display_question(string, data_type, data_holder[, max_length])` will display a text as a question, waiting the user to type text.

Available data types are `m_type_int`, `m_type_float`, `m_type_string` . This last one also need an extra integer argument `max_len`, to limit the data grabbed from the user and avoid overflows, so be sure to set it correctly.

Basic examples are:

```C
  display_question("Type an integer", m_type_int, &q_int);
  PRINTF("q_int is: %i\n", q_int);

  display_question("Type a float", m_type_float, &q_float);
  PRINTF("q_float is: %f\n", q_float);

  /* Limit is set to 10, so max is 8 chars + newline + null */
  display_question("Type a string", m_type_string, &q_str, 10);
  PRINTF("q_str is: %s\n", q_str);
```

The resulting console output looks like:

```
-- Type an integer: 12345
q_int es: 12345

-- Type a float: -12.345
q_float es: -12.345000

-- Type a string: Hello World!
q_str es: Hello Wo
```


## Menu with user interaction

Invoking `display_menu(menu, &sel_item, wait_only)` will display(or not) an option menu and will wait the user to type a choice, exiting only when exit key is pressed.

There is a single **mandatory entry**, the exit one. It **have to be the last** in the array and **have to have a NULL callback**.

To include a header entry, it have to use `M_H` as its key and `m_entry_header` as its callback (both declared inside `cu_ui.h`.

A menu example array looks like:

```C
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
```

The resulting console output looks like:

```
#*
#  First, more decorated header
#*


#  Not the first, less deco
 1. User entry nr.1
 2. User entry nr.2
 3. User entry nr.3
 4. User entry nr.4
 5. User entry nr.5

#  Not the first, less deco
 6. User entry nr.1
 7. User entry nr.2
 8. User entry nr.3
 9. User entry nr.4
 0. User entry nr.5

 x. Exit

-- Select an option:
```


## Changelog

### [1.3.0] - 2017-05-31

#### Added

- `display_question()` to ease display + parse typed text. Overflow safe.


### [1.2.1] - 2017-05-31

#### Added

- `uart_fgets()` is a `fgets()`-like function with support for a non-blocking stream (uart) where the returned character can be 0x00.


### [1.1.0] - 2017-05-29

#### Added

- Hierarchical menus without deep call made easy with `start_hmenu(menu_action *)` and `display_hmenu(menu_item_st *)`.


### [1.0.0] - 2017-05-28

#### Changed

- `display_menu()` now updates the selected index instead a callback as argument. User can now choose freedomly what to do within a full perspective (switch..case the key, check..call the callback, ...)


### [0.2.0] - 2017-05-28

#### Added

- Main and secondary headers support


### [0.1.0] - 2017-05-26

#### Added

- First release, menu with user interaction


# `cu_mocks`: C-Utils mocks for offline testing


# TO-DO list

- [ ] Check and improve `cu_ui` module documentation
- [ ] Add use cases and how-to to `cu_ui`

