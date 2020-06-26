//standard library inclusion
#include<stdio.h>
#include<ctype.h>
#include <time.h>
#include <stdlib.h>

//global variable declaration
int num_of_vertices = 0;

//function declaration
int floyd_algorithm(int **w_matrix, int **p_matrix);

int print_path(int index_q, int index_r, int **p_matrix);
/*
 This function  will take input from user and will generate random number.
 As per user's input main will call sorting function
*/

int main() {
    //variable declaration
    int max_display_num = 10;
    int min_display_num = 1;

    //loop counter declaration
    int i, j;

    //srand function used to get proper random numbers
    srand((unsigned) time(NULL));
    //random generation of num between 5 to 10
    while (num_of_vertices < 5 || num_of_vertices > 10) {
        num_of_vertices = (rand() % 10) + 5;
    }

    printf("\n\nNumber of Vertices are = %d\n", num_of_vertices);

    //Generating array of random numbers as per count given by user
    //size allocated to pointer inoput and pointer matrix
    int **input_matrix_a = malloc(num_of_vertices * sizeof(*input_matrix_a));
    int **pointer_array_p = malloc(num_of_vertices * sizeof(*pointer_array_p));
    int array_element = 0;
    int diagonal_element;

    for (i = 0; i < num_of_vertices; i++) {
        input_matrix_a[i] = malloc(num_of_vertices * sizeof(*input_matrix_a[i]));
        pointer_array_p[i] = malloc(num_of_vertices * sizeof(*pointer_array_p[i]));
    }

    //need to clear random generator to null before generation of random number
    srand((unsigned) time(NULL));

    //generating random number using rand() function and adding the same into input matrix
    //need to assign number in such a way that matrix maintain symmetry as input_matrix_a[j][i] = input_matrix_a[i][j];
    printf("\n\nInitial weighted matrix is :\n\n");
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            if (i == j) {
                input_matrix_a[i][j] = 0;
                diagonal_element = j;
            } else if (j > diagonal_element) {
                array_element = (rand() % max_display_num) + min_display_num;
                input_matrix_a[i][j] = array_element;
                input_matrix_a[j][i] = input_matrix_a[i][j];
            }
            printf("%d\t", input_matrix_a[i][j]);
        }
        printf("\n");
    }

    //printing pointer matrix
    printf("\n\nInitial pointer matrix is :\n\n");
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            printf("%d\t", pointer_array_p[i][j]);
        }
        printf("\n");
    }

    //calling floyd algorithm function
    floyd_algorithm(input_matrix_a, pointer_array_p);

    //free up the heap space of pointers
    for (i = 0; i < num_of_vertices; i++) {
        free(input_matrix_a[i]);
        free(pointer_array_p[i]);
    }
    free(input_matrix_a);
    free(pointer_array_p);
    return 0;
}

/*
 This function takes 2 input, weighted matrix and pointer matrix and allocate pointer matrix after calculating formula
 D[i,j]← D[i,k] + D[k,j]
*/

int floyd_algorithm(int **w_matrix, int **p_matrix) {
    //loop counter declaration
    int i, j, k;
    //declaration and space allotment to double pointer
    int **d_matrix = malloc(num_of_vertices * sizeof(*d_matrix));
    for (i = 0; i < num_of_vertices; i++) {
        d_matrix[i] = malloc(num_of_vertices * sizeof(*d_matrix[i]));
    }
    //initialize d array to w
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            d_matrix[i][j] = w_matrix[i][j];
        }
    }

    //assign smallest among d_matrix[i][k] + d_matrix[k][j] and d[i][j] and accordingly allocate node in pointer matrix
    for (k = 0; k < num_of_vertices; k++) {
        for (i = 0; i < num_of_vertices; i++) {
            for (j = 0; j < num_of_vertices; j++) {
                if (d_matrix[i][j] > d_matrix[i][k] + d_matrix[k][j]) {
                    d_matrix[i][j] = d_matrix[i][k] + d_matrix[k][j];
                    //allocate node to pointer matrix
                    p_matrix[i][j] = k;
                }
            }
        }
    }

    //printing updated adjacency matrix
    printf("\n\n****************************************\n\n");
    printf("\n\nFinal adjacency matrix is :\n\n");
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            printf("%d\t", d_matrix[i][j]);
        }
        printf("\n");
    }

    //printing updated pointer matrix
    printf("\n\nFinal pointer matrix is :\n\n");
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            printf("%d\t", p_matrix[i][j]);
        }
        printf("\n");
    }

    //printing all pairs shortest paths and their lengths
    printf("\n\n");
    for (i = 0; i < num_of_vertices; i++) {
        for (j = 0; j < num_of_vertices; j++) {
            if (i != j) {
                printf("Shortest (Distance = %d) and Path between V%d and V%d : \t\t V%d, ", d_matrix[i][j], i, j, i);
                //calling print function to print nodes from pointer matrix in recursive way
                print_path(i, j, p_matrix);
                printf("V%d", j);
            } else {
                printf("Shortest (Distance = 0) and Path between V%d and V%d : \t\t 0", i, j);
            }
            printf("\n");
        }
        printf("\n");
    }

    //free up the heap space malloced to pointers

    for (i = 0; i < num_of_vertices; i++) {
        free(d_matrix[i]);
    }

    free(d_matrix);

    return 0;
}

/*
 This function print shortest path using pointer matrix in recursive way till subpath weight become 0
*/

int print_path(int index_q, int index_r, int **p_matrix) {
    //local variable declaration
    int first_index = index_q;
    int second_index = index_r;

    //print node in recursive manner till weight of edge becomes 0
    if (p_matrix[first_index][second_index] != 0) {
        //checking path from first node till weight of edge node from pointer matrix
        print_path(first_index, p_matrix[first_index][second_index], p_matrix);
        //printing respective node i.e. weight of edge
        printf("V%d, ", p_matrix[first_index][second_index]);
        //checking path from first node till weight of edge node from pointer matrix
        print_path(p_matrix[first_index][second_index], second_index, p_matrix);
    }
    return 0;
}
