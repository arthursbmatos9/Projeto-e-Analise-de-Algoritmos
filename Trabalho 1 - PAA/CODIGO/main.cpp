#include "graph_utils.hpp"
#include <vector>

int main() {
    std::vector<int> vertices_list = {100, 1000, 10000, 100000};
    testPerformance(vertices_list);
    return 0;
}