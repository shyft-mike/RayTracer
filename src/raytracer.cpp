#include <chrono>
#include <raytracer.hpp>

int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    RayTracer().run();

    auto end = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(end - start);

    std::cerr << "-------------------------\n"
              << "total time: " << ms_int.count() << std::endl;

    return 0;
}
