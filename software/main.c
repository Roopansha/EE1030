#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100  // Maximum matrix size
#define EPS 1e-9 // Convergence tolerance

typedef struct {
    double real;
    double imag;
} Complex;

// Complex arithmetic functions
Complex add(Complex a, Complex b) {
    return (Complex){a.real + b.real, a.imag + b.imag};
}

Complex subtract(Complex a, Complex b) {
    return (Complex){a.real - b.real, a.imag - b.imag};
}

Complex multiply(Complex a, Complex b) {
    return (Complex){a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
}

Complex divide(Complex a, Complex b) {
    double denom = b.real * b.real + b.imag * b.imag;
    return (Complex){
        (a.real * b.real + a.imag * b.imag) / denom,
        (a.imag * b.real - a.real * b.imag) / denom};
}

double magnitude(Complex a) {
    return sqrt(a.real * a.real + a.imag * a.imag);
}

// QR algorithm functions
void qrDecomposition(Complex A[MAX][MAX], Complex Q[MAX][MAX], Complex R[MAX][MAX], int n);
void multiplyMatrices(Complex A[MAX][MAX], Complex B[MAX][MAX], Complex C[MAX][MAX], int n);
void copyMatrix(Complex src[MAX][MAX], Complex dest[MAX][MAX], int n);
int isConverged(Complex A[MAX][MAX], int n);

void qrAlgorithm(Complex A[MAX][MAX], int n) {
    Complex Q[MAX][MAX], R[MAX][MAX], temp[MAX][MAX];
    int iterations = 0;

    while (!isConverged(A, n)) {
        // Perform QR decomposition
        qrDecomposition(A, Q, R, n);

        // Update A = R * Q
        multiplyMatrices(R, Q, temp, n);
        copyMatrix(temp, A, n);

        iterations++;
        if (iterations > 1000) {  // Limit iterations to prevent infinite loops
            printf("QR Algorithm did not converge.\n");
            return;
        }
    }

    // Eigenvalues are the diagonal elements of the final A matrix
    printf("Eigenvalues:\n");
    for (int i = 0; i < n; i++) {
        printf("%.6f + %.6fi\n", A[i][i].real, A[i][i].imag);
    }
}

// Function to perform QR decomposition (Gram-Schmidt Process)
void qrDecomposition(Complex A[MAX][MAX], Complex Q[MAX][MAX], Complex R[MAX][MAX], int n) {
    Complex v[MAX][MAX];
    double norm;

    // Initialize Q to zero
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Q[i][j] = (Complex){0, 0};

    // Gram-Schmidt process to compute Q and R
    for (int k = 0; k < n; k++) {
        // Copy column k of A to v[k]
        for (int i = 0; i < n; i++) {
            v[i][k] = A[i][k];
        }

        // Subtract projections
        for (int j = 0; j < k; j++) {
            R[j][k] = (Complex){0, 0};
            for (int i = 0; i < n; i++) {
                R[j][k] = add(R[j][k], multiply(Q[i][j], A[i][k]));
            }
            for (int i = 0; i < n; i++) {
                v[i][k] = subtract(v[i][k], multiply(R[j][k], Q[i][j]));
            }
        }

        // Compute norm of v[k] and normalize to get Q[:, k]
        norm = 0;
        for (int i = 0; i < n; i++) {
            norm += magnitude(v[i][k]) * magnitude(v[i][k]);
        }
        norm = sqrt(norm);
        R[k][k] = (Complex){norm, 0};

        for (int i = 0; i < n; i++) {
            Q[i][k] = divide(v[i][k], R[k][k]);
        }
    }
}

// Function to multiply two matrices: C = A * B
void multiplyMatrices(Complex A[MAX][MAX], Complex B[MAX][MAX], Complex C[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = (Complex){0, 0};
            for (int k = 0; k < n; k++) {
                C[i][j] = add(C[i][j], multiply(A[i][k], B[k][j]));
            }
        }
    }
}

// Function to copy one matrix to another
void copyMatrix(Complex src[MAX][MAX], Complex dest[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Function to check convergence (off-diagonal elements are close to zero)
int isConverged(Complex A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && magnitude(A[i][j]) > EPS) {
                return 0;  // Not yet converged
            }
        }
    }
    return 1;  // Converged
}

int main() {
    int n;
    Complex A[MAX][MAX];

    // Input matrix size and elements
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter the elements of the matrix (real and imaginary parts):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            scanf("%lf %lf", &A[i][j].real, &A[i][j].imag);
        }
    }

    // Perform QR Algorithm
    qrAlgorithm(A, n);

    return 0;
}

