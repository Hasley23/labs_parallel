#include <stdio.h>
#include <omp.h>

// матрица
double** new_matrix(int n)
{
    double** matrix;
    matrix = new double*[n];
    for(int i = 0; i < n; ++i)
        matrix[i] = new double[n];
    return matrix;
}

// чтение матрицы с клавиатуры
void read_matrix(double** matrix, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%lf", &matrix[i][j]);
}

// вывод матрицы
void print_matrix(double** matrix, int n)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}


// точка входа
int main()
{
    double t1, t2;

    int n, k, intBool;
    printf("0 - последовательно | !0 - параллельно\n");
    scanf("%d", &intBool);

	if (intBool)
	{
		printf("параллельная версия\n");
		printf("потоки\n");
    	// количество потоков
    	scanf("%d", &k);
	}
	printf("Размер матриц\n");
    // размер матриц
    scanf("%d", &n);

    double** A = new_matrix(n);
    double** B = new_matrix(n);
    double** C = new_matrix(n);

    read_matrix(A, n);
    read_matrix(B, n);

    t1 = omp_get_wtime();

    if (!intBool)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                C[i][j] = 0.0;
                for (int k = 0; k < n; ++k)
                    C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    

    // основной вычислительный блок (с collapse(2) для работы со связанными циклами)
    #pragma omp parallel for shared(A, B, C) num_threads(k) collapse(2) if (intBool)
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = 0.0;
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    t2 = omp_get_wtime();

    print_matrix(C, n);

    printf("Замер времени: %lf\n", t2 - t1);

}
