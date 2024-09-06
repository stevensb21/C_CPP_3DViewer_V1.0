#ifndef parser_h
#define parser_h

#include "s21_3dviewer.h"

int allocate_memory(data *model);
void count_vertices_and_indexes(FILE *file, data *model);
int clear_data(data *model);
int parse_vertices_and_indexes(FILE *file, data *model);

#endif /* parser_h */
