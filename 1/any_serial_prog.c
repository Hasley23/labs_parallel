#include <stdio.h>

int main() {
    int two = 2;
    #pragma omp parallel
    printf("2 + 2 = %d\n", two + two);
    return 0;
}
