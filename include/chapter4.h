#ifndef CHAPTER4_H
#define CHAPTER4_H

#include "canvas.h"
#include "cartesia.h"

namespace Chapter4
{
    struct Program
    {
        Canvas canvas;

        Program(Canvas canvas) : canvas(canvas)
        {
        }

        void execute()
        {
            Color color = Color(1, 0.75, 0.75);
            Point center = Point(0, 0, 0);
            float offset_x = this->canvas.width / 2 - 50;
            float offset_y = this->canvas.height / 2 - 50;

            for (int i = 0; i < 12; i++)
            {
                float rotation = (2 * M_PI / 12) * i;

                float translation = this->canvas.height / 2 - 50;

                Point point = MatrixHelper(center)
                                  .translate(0, translation, 0)
                                  .rotate_z(rotation)
                                  .translate(offset_x, offset_y, 0)
                                  .to_point();

                this->canvas.setPixel(point.x, this->canvas.height - point.y, color);
            }
        }
    };
}

#endif