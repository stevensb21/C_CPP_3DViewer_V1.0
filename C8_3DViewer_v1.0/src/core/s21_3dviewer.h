#ifndef CORE_3D_VIEWER_H_
#define CORE_3D_VIEWER_H_

#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  unsigned int count_index;
  unsigned int count_vertices;
  double *vertices;
  int *indexes;
} data;

enum statuses { OK, ERROR };

int parse_file(const char *filename, data *model);
int make_matrix(data *model);
int clear_data(data *model);

#endif  // CORE_3D_VIEWER_H_
