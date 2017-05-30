/**
 * @file Mocking library
 *
 * Elements to allow unit tests primary focused on embedded-like environments,
 * but in a full featured environment
 *
 * @author     CieNTi
 * @version    1.0.0
 */

#ifndef H_CU_MOCKS
#define H_CU_MOCKS

/* ----------------------------------------
 * Macros
 */
/** Tell the system mocking is available and ready */
#define CU_MOCK_IS_ALIVE

/* Mocking data types */
#define CU_MOCK_TYPE_NONE    0
#define CU_MOCK_TYPE_INT     1
#define CU_MOCK_TYPE_FLOAT   2
#define CU_MOCK_TYPE_STRING  3
#define CU_MOCK_TYPE_POINTER 4

/* Use mocking FGETC instead system-defined one */
#if defined(CU_MOCK_FGETC_NONBLOCK)

#if defined(FGETC)
#undef FGETC
#endif

#define FGETC fgetc_nonblock_mock()

#endif

/* ----------------------------------------
 * File functions
 */
/**
 * @brief      Selects the data type 'fgetc_nonblock_mock()' will returns
 *
 * @param[in]  data_type  One of:
 *                        - CU_MOCK_TYPE_INT
 *                        - CU_MOCK_TYPE_FLOAT
 *                        - CU_MOCK_TYPE_STRING
 */
void set_fgetc_mock_type(int data_type);

/**
 * @brief      fgetc mocking function, returns a keypress/nonblock simulation
 *
 * @return     Character supposely read from interface
 */
char fgetc_nonblock_mock(void);


#endif /* H_CU_MOCKS */
