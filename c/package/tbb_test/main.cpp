#include <iostream>
#include <vector>

#include "oneapi/tbb/parallel_for.h"
#include "oneapi/tbb/blocked_range.h"

int main() {
    std::vector<double> values = std::vector<double>(10000);
    tbb::parallel_for(
        tbb::blocked_range<int>(0, values.size()), 
        [&](tbb::blocked_range<int> r) {
            for (int i = r.begin(); i < r.end(); ++i) {
                values[i] = std::sin(0.001 * i);
            }
        }

    );

    double total = 0;
    for (double value: values) {
        total += value;
    }
    std::cout << total << std::endl;
    return 0;
}
