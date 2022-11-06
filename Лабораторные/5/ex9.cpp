#include <stdio.h>
#include <omp.h>

double** new_matrix(int n)
{
    double** matrix;
    matrix = new double*[n];
    for(int i = 0; i < n; ++i)
        matrix[i] = new double[n];
    return matrix;
}

void read_matrix(double** matrix, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%lf", &matrix[i][j]);
}

void print_matrix(double** matrix, int n)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}



int main()
{
    double t1, t2;

    int n;
    scanf("%d", &n);

    double** A = new_matrix(n);
    double** B = new_matrix(n);
    double** C = new_matrix(n);

    read_matrix(A, n);
    read_matrix(B, n);

    t1 = omp_get_wtime();
    // основной вычислительный блок
    #pragma omp parallel for shared(A, B, C) reduction(sum) collapse(2)
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

    printf("Time=%lf\n", t2 - t1);

}