#ifndef CHAPTER4_H
#define CHAPTER4_H

#include "raytracer/canvas.h"
#include "raytracer/cartesia.h"
#include "raytracer/matrices/helper.h"

namespace Chapter4
{
    struct Program
    {
        void execute(Canvas &canvas)
        {
            Color color = Color(1, 0, 0);
            Point center = Point(0, 0, 0);
            float offset_x = canvas.width / 2;
            float offset_y = canvas.height / 2;

            for (int i = 0; i < 12; i++)
            {
                float rotation = (2 * M_PI / 12) * i;

                float translation = offset_y - 5;

                Point point = MatrixHelper(center)
                                  .translate(0, translation, 0)
                                  .rotate_z(rotation)
                                  .translate(offset_x, offset_y, 0)
                                  .to_point();

                canvas.setPixel(point.x, canvas.height - point.y, color);
            }
        }
    };
}

#endif