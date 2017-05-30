/**
 * @file Mocking library
 *
 * Elements to allow unit tests primary focused on embedded-like environments,
 * but in a full featured environment
 *
 * @author     CieNTi
 * @version    1.0.0
 */


#include "cu_mocks.h"
#include "cu_commons.h"
#include "cu_ui.h"

#include <stdio.h>

/* Position at source array */
static int fgetc_mock_idx = 0;

/* Integer with multiple 0x00 as "nothing received" and a backspace */
static char nonblock_int[] =
{
  0x00, 0x00, '-', '1', '3', '\b', '2', 0x00, 0x00, 0x00, '\r', '\n'
};

/* Float with multiple 0x00 as "nothing received" and a backspace */
static char nonblock_float[] =
{
  0x00, 0x00, '-', '1', '3', '\b', '2', 0x00, 0x00, 0x00, '3', '.', '4',
  '5', '6', '\r', '\n'
};

/* String with multiple 0x00 as "nothing received" and a backspace */
static char nonblock_string[] =
{
  0x00, 0x00, 'h', 'e', 'k', '\b', 'l', 0x00, 0x00, 0x00, 'l', 'o', 'l',
  'o', 'l', 'o', 'l', 'o', 'l', 'o', 'l', 'o', 'l', 'o', 'l', 'o', 'l',
  'o', 'l', 'o', 'l', 'o', 'l', 'a', 'i', '\r', '\n'
};

/* Data selector */
static char *source_data = NULL;

/**/
void set_fgetc_mock_type(int data_type)
{
  /* Reset and set! */
  fgetc_mock_idx = 0;

  PRINTF("* FGETC will returns a ");
  switch (data_type)
  {
    case CU_MOCK_TYPE_INT:
      PRINTF("int");
      source_data = nonblock_int;
      break;
    case CU_MOCK_TYPE_FLOAT:
      PRINTF("float");
      source_data = nonblock_float;
      break;
    case CU_MOCK_TYPE_STRING:
      PRINTF("string");
      source_data = nonblock_string;
      break;
    default:
      source_data = NULL;
      break;
  }
  PRINTF(" type\n");
}

/**/
char fgetc_nonblock_mock(void)
{
  if (source_data != NULL)
  {
    if (source_data[fgetc_mock_idx] == '\n')
    {
      /* Start array again */
      fgetc_mock_idx = 0;
      return '\n';
    }
    else
    {
      /* Keep going */
      return source_data[fgetc_mock_idx++];
    }
  }
  return 0x00;
}
