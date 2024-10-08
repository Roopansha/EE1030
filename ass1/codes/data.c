#include <stdio.h>
#include <math.h>

int main() {
    // Given values
    double a = 3.5;        // One side of the triangle
    double sum_bc = 5.5;   // Sum of the other side and the hypotenuse

    // Variables to hold the lengths of the other side and the hypotenuse
    double b, c;

    // Calculate the other side (b) and the hypotenuse (c)
    b = (pow(sum_bc, 2) - pow(a, 2)) / (2 * sum_bc);
    c = sum_bc - b;

    // Calculate the endpoints
    double Ax = 0.0, Ay = 0.0;         // Vertex A
    double Bx = 0.0, By = a;            // Vertex B
    double Cx = b, Cy = 0.0;            // Vertex C

    // Open a file for writing
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the endpoints to the file
    fprintf(file, "Endpoints of the triangle:\n");
    fprintf(file, "A (0.00, 0.00)\n");
    fprintf(file, "B (0.00, %.2f)\n", By);
    fprintf(file, "C (%.3f, 0.00)\n", Cx);

    // Close the file
    fclose(file);

    // Output to console (optional)
    printf("Endpoints saved to data.txt\n");
    printf("A (%.2f, %.2f)\n", Ax, Ay);
    printf("B (%.2f, %.2f)\n", Bx, By);
    printf("C (%.3f, %.2f)\n", Cx, Cy);

    return 0;
}

