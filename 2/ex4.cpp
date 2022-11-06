#include <stdio.h>

int main() {
    int count = 0;
    // Пример 4 демонстрирует применение опции reduction. В данном примере производится подсчет общего количества порождённых нитей.
    #pragma omp parallel reduction (+: count)
    {
        count++;
        printf("Текущее значение count: %d\n", count);
    }
    printf("Число нитей: %d\n", count);
}
