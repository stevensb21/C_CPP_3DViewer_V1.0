#include "parser.h"

#include "s21_3dviewer.h"

int parse_file(const char *filename, data *model) {
  int exit_status = OK;
  if (filename == NULL || model == NULL) {
    exit_status = ERROR;
  } else {
    FILE *f = fopen(filename, "r");
    if (f) {
      count_vertices_and_indexes(f, model);
      exit_status = allocate_memory(model);
      if (exit_status != ERROR) {
        fseek(f, 0, SEEK_SET);
        exit_status = parse_vertices_and_indexes(f, model);
      }
      fclose(f);
    } else {
      exit_status = ERROR;
    }
  }
  return exit_status;
}

int allocate_memory(data *model) {
  int exit_status = OK;
  if (model->count_vertices) {
    model->vertices = calloc(model->count_vertices * 3, sizeof(double));
  }
  if (model->count_index) {
    model->indexes = calloc(model->count_index * 2, sizeof(int));
  }
  if (model->vertices == NULL || model->indexes == NULL) {
    exit_status = ERROR;
  }
  return exit_status;
}

void count_vertices_and_indexes(FILE *file, data *model) {
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      // model->vertices_amount++;
      model->count_vertices++;
    } else if (strncmp(line, "f ", 2) == 0) {
      char *index = strtok(line + 2, " ");
      while (index != NULL) {
        if (atoi(index)) {
          model->count_index++;
          // model->indexes_amount++;
        }
        index = strtok(NULL, " ");
      }
    }
  }
  if (line) {
    free(line);
    line = NULL;
  }
}

int clear_data(data *model) {
  int exit_status = 1;
  if (model != NULL) {
    exit_status = 0;
    if (model->vertices != NULL) {
      free(model->vertices);
      model->vertices = NULL;
    }
    if (model->indexes != NULL) {
      free(model->indexes);
      model->indexes = NULL;
    }
  }
  return exit_status;
}

int parse_vertices_and_indexes(FILE *file, data *model) {
  int exit_status = OK;
  char *line = NULL;
  size_t len = 0;
  size_t i = 0;
  size_t vertex_counter = 0;
  size_t vertex_indexes_counter = 0;

  while (getline(&line, &len, file) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      vertex_counter++;
      double x, y, z;
      sscanf(line, "v %lf %lf %lf", &x, &y, &z);
      model->vertices[i++] = x;
      model->vertices[i++] = y;
      model->vertices[i++] = z;
    } else if (strncmp(line, "f ", 2) == 0) {
      int first_index = 0;
      int is_first_index = 0;
      char *vertex_index = strtok(line + 2, " ");
      while (vertex_index != NULL) {
        int index_val = atoi(vertex_index);
        if (index_val) {
          if (index_val < 0) {
            index_val += vertex_counter + 1;
          }
          model->indexes[vertex_indexes_counter] = index_val - 1;
          if (!is_first_index) {
            first_index = index_val - 1;
            is_first_index = 1;
          } else {
            model->indexes[++vertex_indexes_counter] = index_val - 1;
          }
          vertex_indexes_counter++;
        }
        vertex_index = strtok(NULL, " ");
      }
      model->indexes[vertex_indexes_counter] = first_index;
      vertex_indexes_counter++;
    }
  }
  if (line) {
    free(line);
    line = NULL;
  }

  if (!model->vertices[model->count_vertices * 3 - 1] ||
      !model->indexes[model->count_index * 2 - 1]) {
    exit_status = ERROR;
  }

  return exit_status;
}
