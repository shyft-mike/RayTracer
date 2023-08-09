#ifndef IDS_H
#define IDS_H

#include <atomic>

namespace ids
{
    inline std::atomic<int> shape_id = 0;

    inline int generate_shape_id()
    {
        return shape_id++;
    }
}

#endif