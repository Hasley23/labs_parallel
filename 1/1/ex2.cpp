#include <iostream>

int main() {
    #pragma omp parallel
    std::cout << "Параллельнный участок" << std::endl;

    return 0;
}