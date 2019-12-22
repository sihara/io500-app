#ifndef IO500_UTIL_H
#define IO500_UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <time.h>

#include <io500-debug.h>

#define INI_UNSET_STRING NULL
#define INI_UNSET_INT (-2147483648)
#define INI_UNSET_UINT (unsigned)(-1)
#define INI_UNSET_UINT64 (uint64_t)(-1)
#define INI_UNSET_BOOL 2

typedef enum{
  INI_STRING,
  INI_INT,
  INI_UINT,
  INI_UINT64,
  INI_BOOL
} ini_var_type_e;

typedef struct {
  char const * name; // the flag, e.g., testArg
  char const * help; // help text provided to understand what this flag does

  bool mandatory;
  ini_var_type_e type; // for checking during the parsing

  char * default_val; // the default value, NULL if no value set
  void * var;         // the pointer to the variable to fill of the given type
} ini_option_t;

typedef struct {
  char const * name; // the section name
  ini_option_t * option;
} ini_section_t;

/**
 Parse the ini file in data according to the expected specification
 @Return 0 if parsing is successfull
 */
int u_parse_ini(char const * data, ini_section_t ** specification);

/**
 Compute a hash based on the current values
 */
uint32_t u_ini_gen_hash(ini_section_t ** sections);

void u_ini_print_hash(FILE * file, ini_section_t ** sections);
void u_ini_print_values(ini_section_t ** sections);

// imported from IOR
double GetTimeStamp(void);
void u_create_datadir(char const * dir);
void u_purge_datadir(char const * dir);
void u_purge_file(char const * file);

void u_create_dir_recursive(char const * dir, char const * api);

void u_print_timestamp(void);
void * u_malloc(int size);


FILE * u_res_file_prep(char const * name);
void u_res_file_close(FILE * out);

/**
 * Functions to handle the argument vectors for invoking other APIs
 */
typedef struct{
 int size;
 char ** vector;
} u_argv_t;

u_argv_t * u_argv_create(void);
void u_argv_free(u_argv_t * argv);
void u_argv_push(u_argv_t * argv, char const * str);

void u_argv_push_default_if_set(u_argv_t * argv, char * const arg, char const * dflt, char const * var);
void u_argv_push_default_if_set_bool(u_argv_t * argv, char * const arg, int dflt, int var);

void u_argv_push_printf(u_argv_t * argv, char const * format, ...)
  __attribute__ ((format (printf, 2, 3)));
char * u_flatten_argv(u_argv_t * argv);

#endif