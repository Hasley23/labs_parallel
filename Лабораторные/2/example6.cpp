#include <stdio.h>
#include <omp.h>

void mode() {
    if(omp_in_parallel()) printf("Параллельная область\n");
    else printf("Последовательная область\n");
}

int main() {
    mode();
    #pragma omp parallel
    #pragma omp master
        mode();
}