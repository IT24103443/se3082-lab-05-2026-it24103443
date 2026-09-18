#include <omp.h>
#include <stdio.h>

int fib(int n) {
    int i, j;
    if (n < 2) return n;

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 30, result;
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }
    printf("fib(%d) = %d\n", n, result);
    return 0;
}