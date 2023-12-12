#ifndef JSON_FUNCS_H__

#define JSON_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "consts.h"
#include "err_codes.h"
#include "abonent_funcs.h"

int createJSON(Abonent *abonents);

int readAbonentsFromJSON(const char *filename, Abonent *abonents, int max_abonents, size_t *cnt);

#endif
