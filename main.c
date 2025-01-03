// Created: 2025-01-03 17:00:00
// V 1.0.1
// Comment lang: EN
// CMD text lang: PL
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> // Including the module that lets the program print UTF-8 characters

struct matrix_size { // Defining a structure that will store the size of the matrix
    int col;
    int row;
};

FILE* open_file(const char *file_name) {
    // Opening the file in read mode
    // If the file doesn't exist, the program will print an error message and return nullptr
    // Takes the file name as an argument
    // Returns a pointer to the file
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return nullptr;
    }
    return file;
}

void close_file(FILE* file) {
    // Closes the file
    // Takes a pointer to the file as an argument
    fclose(file);
}

int** allocate_matrix(const int col, const int row) {
    // Allocating memory for the matrix
    // Takes the number of columns and rows as arguments
    // Returns a pointer to the matrix
    int **matrix = malloc(col * sizeof(int*));
    for (int i = 0; i < col; i++) {
        matrix[i] = malloc(row * sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, const int col) {
    // Frees the memory allocated for the matrix
    // Takes a pointer to the matrix and the number of columns as arguments
    for (int i = 0; i < col; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

struct matrix_size get_matrix_size(FILE* file) {
    // Get the size of the matrix
    // Takes a pointer to the file as an argument
    // Returns a structure that contains the size of the matrix
    struct matrix_size size;
    fscanf(file, "%d %d", &size.row, &size.col);
    return size;
}

bool can_be_multiplied(const struct matrix_size size_1, const struct matrix_size size_2) {
    // Checks if the matrices can be multiplied
    // Takes both structures including size of both matrices as arguments
    // Returns true when matrices can be multiplied
    if (size_1.col == size_2.row) {
        return true;
    }
    return false;
}

void save_matrix(int** matrix, const struct matrix_size size) {
    // Saves the matrix to the file
    // Takes the pointer to the matrix and the struct with its size as arguments
    FILE *file = fopen("result.txt", "w");
    for (int i = 0; i < size.row; i++) {
        for (int j = 0; j < size.col - 1; j++) {
            fprintf(file, "%d ", matrix[j][i]);
        }
        fprintf(file, "%d", matrix[size.col - 1][i]); // To avoid the space at the end of the line
        if (i < size.row - 1) {
            fprintf(file, "\n"); // To avoid the newline character at the end of the file
        }
    }
    close_file(file);
}

int** read_matrix(FILE* file, const struct matrix_size size) {
    // Read the matrix from the file
    // Takes a pointer to the file and a struct describing size as arguments
    // Returns a pointer to the matrix
    int** matrix = allocate_matrix(size.col, size.row);
    int curr_col = 0;
    int curr_row = 0;
    char curr_num[3];
    int i = 0;
    while (!feof(file)) {
        const char ch = fgetc(file);
        if (isdigit(ch)) {
            curr_num[i] = ch;
            i++;
        } else if (ch == ' ') {
            matrix[curr_col][curr_row] = atoi(curr_num);
            curr_col++;
            for (int f = 0; f <= i; f++) {
                curr_num[f] = 0;
            }
            i = 0;
        } else if (ch == '\n') {
            matrix[curr_col][curr_row] = atoi(curr_num);
            curr_col = 0;
            curr_row++;
            for (int f = 0; f <= i; f++) {
                curr_num[f] = 0;
            }
            i = 0;
        } else if (feof(file)) {
            matrix[curr_col][curr_row] = atoi(curr_num);
            break;
        }
    }
    return matrix;
}

void print_matrix(int** matrix, const struct matrix_size size) {
    // Print the matrix, was used for debugging
    // Takes a pointer to the matrix and a struct describing size as arguments
    for (int i = 0; i < size.row; i++) {
        for (int j = 0; j < size.col; j++) {
            printf("%d ", matrix[j][i]);
        }
        printf("\n");
    }
}

int multiply_matrix(FILE* matrix_1_f, FILE* matrix_2_f) {
    // Multiply two matrices
    // Takes two pointers to the files as arguments
    // Returns a pointer to the result matrix
    // Returns 1 if matrices can't be multiplied
    // Returns 0 if operation has been done without any problems

    // Define structures with matrices size
    const struct matrix_size matrix_1_size = get_matrix_size(matrix_1_f);
    fscanf(matrix_1_f, "\n"); // Skip the newline character
    const struct matrix_size matrix_2_size = get_matrix_size(matrix_2_f);
    fscanf(matrix_2_f, "\n"); // Skip the newline character
    // printf("Size 2: %d x %d\n", matrix_2_size.col, matrix_2_size.row); // Debug

    // Check if matrices can be multiplied, returns nullptr if can't
    if (!can_be_multiplied(matrix_1_size, matrix_2_size)) {
        return 1;
    }

    // Defines the matrices in the memory
    int** matrix_1 = read_matrix(matrix_1_f, matrix_1_size);
    int** matrix_2 = read_matrix(matrix_2_f, matrix_2_size);
    // print_matrix(matrix_1, matrix_1_size); // Debug
    // print_matrix(matrix_2, matrix_2_size); // Debug

    // Defines the result matrix
    struct matrix_size result_size;
    result_size.col = matrix_2_size.col;
    result_size.row = matrix_1_size.row;
    int** result = allocate_matrix(result_size.col, result_size.row);

    // Multiplies the matrices and saves the result
    for (int i = 0; i < result_size.col; i++) {
        for (int j = 0; j < result_size.row; j++) {
            int num = 0;
            for (int x = 0; x < matrix_1_size.col; x++) {
                num += matrix_1[x][i] * matrix_2[j][x];
            }
            result[j][i] = num;
        }
    }

    // Saves the matrix to the result file
    save_matrix(result, result_size);

    // Cleans the memory
    free_matrix(matrix_1, matrix_1_size.col);
    free_matrix(matrix_2, matrix_2_size.col);
    free_matrix(result, result_size.col);

    return 0;
}

int main(void) {
    setlocale(LC_ALL, ""); // Setting the locale to the system's default

    // Defines the files
    FILE *matrix_file_1 = open_file("matrix_1.txt");
    if (matrix_file_1 == nullptr) {
        return 2;
    }
    FILE *matrix_file_2 = open_file("matrix_2.txt");
    if (matrix_file_2 == nullptr) {
        return 3;
    }

    const int result = multiply_matrix(matrix_file_1, matrix_file_2);

    if (result != 0) {
        wprintf(L"Nie udało się przemnożyć macierzy. Upewnij się, że liczba kolumn pierwszej macierzy jest równa liczbie wierszy drugiej macierzy.");
        close_file(matrix_file_1);
        close_file(matrix_file_2);
        return 1;
    }

    wprintf(L"Macierz wynikowa została zapisana do pliku: result.txt");
    close_file(matrix_file_1);
    close_file(matrix_file_2);

    return 0;
}
