#include <chrono>
#include <raytracer/core/canvas.hpp>
#include <raytracer/core/matrices/matrix.hpp>
#include <raytracer.hpp>

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    Canvas canvas = Canvas(100, 100);

    auto start = high_resolution_clock::now();

    RayTracer(canvas).run();

    auto end = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(end - start);

    std::cerr << ms_int.count() << std::endl;

    return 0;
}
