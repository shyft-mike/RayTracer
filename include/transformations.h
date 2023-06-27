#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrices.h"
#include "cartesia.h"

Matrix translation(float x, float y, float z);
Matrix translation(const Point &point);

Matrix scaling(float x, float y, float z);
Matrix scaling(const Point &point);

Matrix rotation_x(float radians);
Matrix rotation_y(float radians);
Matrix rotation_z(float radians);

Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);

#endif