#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP 64

int main() {
    double *A = aligned_alloc(64, N * sizeof(double));
    double *B = aligned_alloc(64, N * sizeof(double));
    double *C = aligned_alloc(64, N * sizeof(double));

    for (int i = 0; i < N; i++) { A[i] = i * 0.5; B[i] = i * 2.0; }

    double t0 = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int s = 0; s < N; s += STRIP) {
        int end = (s + STRIP < N) ? s + STRIP : N;
        #pragma omp simd
        for (int i = s; i < end; i++)
            C[i] = A[i] * B[i];
    }

    printf("time = %f s, C[999999] = %f\n", omp_get_wtime() - t0, C[N-1]);
    free(A); free(B); free(C);
    return 0;
}