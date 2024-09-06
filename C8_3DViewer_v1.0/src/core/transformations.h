#ifndef transformations_h
#define transformations_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_3dviewer.h"

void x_rotation(data *model, double angle);
void y_rotation(data *model, double angle);
void z_rotation(data *model, double angle);
void scale_t(data *model, const double d);
void x_move(data *model, const double d);
void y_move(data *model, const double d);
void z_move(data *model, const double d);

#endif /* transformations_h */
