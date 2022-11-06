#include <stdio.h>
#include <omp.h>

int main() {
    // Пример 7 демонстрирует использование вложенных параллельных областей и функции omp_set_nested(). Вызов функции omp_set_nested() перед первой частью разрешает использование вложенных параллельных областей.
    int n;
    // можно использовать параллельные области
    omp_set_nested(1);
    // private - Указывает, что каждый поток должен иметь собственный экземпляр переменной.
    #pragma omp parallel private(n)
    {
    	// определение номера нити в области
        n = omp_get_thread_num();
        #pragma omp parallel
            // номер нити вместе с номером нити породившей данную
            printf("Часть 1, нить %d - %d\n", n, omp_get_thread_num());
    }
    // параллельные области использовать уже нельзя
    omp_set_nested(0);
    printf("----------------\n");
    #pragma omp parallel private(n)
    {
        n = omp_get_thread_num();
        #pragma omp parallel
            printf("Часть 2, нить %d - %d\n", n, omp_get_thread_num());
    }
}
