#include "transformations.h"

void x_rotation(data *model, double angle) {
  angle *= M_PI / 180;
  const double angle_cos = cos(angle), angle_sin = sin(angle);
  for (size_t i = 0; i < model->count_vertices * 3; i += 3) {
    double y = model->vertices[i + 1];
    double z = model->vertices[i + 2];
    model->vertices[i + 1] = y * angle_cos + z * angle_sin;
    model->vertices[i + 2] = -y * angle_sin + z * angle_cos;
  }
}

void y_rotation(data *model, double angle) {
  angle *= M_PI / 180;
  const double angle_cos = cos(angle), angle_sin = sin(angle);
  for (size_t i = 0; i < model->count_vertices * 3; i += 3) {
    double x = model->vertices[i];
    double z = model->vertices[i + 2];
    model->vertices[i] = x * angle_cos + z * angle_sin;
    model->vertices[i + 2] = -x * angle_sin + z * angle_cos;
  }
}

void z_rotation(data *model, double angle) {
  angle *= M_PI / 180;
  const double angle_cos = cos(angle), angle_sin = sin(angle);
  for (size_t i = 0; i < model->count_vertices * 3; i += 3) {
    double x = model->vertices[i];
    double y = model->vertices[i + 1];
    model->vertices[i] = x * angle_cos + y * angle_sin;
    model->vertices[i + 1] = -x * angle_sin + y * angle_cos;
  }
}

void scale_t(data *model, const double d) {
  if (d != 0) {
    for (size_t i = 0; i < model->count_vertices * 3; i++) {
      model->vertices[i] *= d;
    }
  }
}

void x_move(data *model, const double d) {
  for (size_t i = 0; i < model->count_vertices * 3; i += 3) {
    model->vertices[i] += d;
  }
}

void y_move(data *model, const double d) {
  for (size_t i = 1; i < model->count_vertices * 3; i += 3) {
    model->vertices[i] += d;
  }
}

void z_move(data *model, const double d) {
  for (size_t i = 2; i < model->count_vertices * 3; i += 3) {
    model->vertices[i] += d;
  }
}
