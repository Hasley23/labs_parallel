#include <stdio.h>
#include <omp.h>

int main() {
	// переопределим размер массива большей вместимостью (так как потоков больше)
    // иначе получим stack smashing
    int i, m[12];
    printf("Массив m в начале:\n");
    
    // Заполним массив m нулями и напечатаем его
    for (i=0; i<12; i++) {
        m[i]=0;
        printf("%d ", m[i]);
    }

    printf("\n");

    // Присвоим 1 элементу массива m, номер которого совпадает с номером текущей нити
    #pragma omp parallel shared(m)
        m[omp_get_thread_num()]=1;
        

    //Ещё раз напечатаем массив
    printf("Массив m в конце:\n");
    for (i=0; i<12; i++)
        printf("%d ", m[i]);

    printf("\n");
}
