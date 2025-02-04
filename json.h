#ifndef JSON_H
#define JSON_H

#include "word.h"

struct json_object *createJSON(mot_data_t **d);
mot_data_t **extractJSON(struct json_object *o);

#endif