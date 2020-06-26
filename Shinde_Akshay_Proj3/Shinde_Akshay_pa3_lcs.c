//standard library inclusion
#include <stdio.h>
#include <string.h>

//global variable declaration
int str1_length;
int str2_length;

//function declaration
int lcs(char str1[], char str2[], char show_lcs[]);

int initialize_array(int c[str1_length + 1][str2_length + 1]);

int load_output(char str1[], char b[str1_length + 1][str2_length + 1], char show_lcs[]);

/*
 This function takes 2 strings as input from user and finds the common sequence between them
*/
int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("\n\nIncorrect parameters passed from command line.....Please provide 2 strings as parameter\n\n");
        return 0;
    }

    //local variable declaration
    str1_length = strlen(argv[1]);
    str2_length = strlen(argv[2]);
    char str1[str1_length];
    char str2[str2_length];
    int show_length;


    if (str1_length > str2_length) {
        show_length = str1_length;
    } else {
        show_length = str2_length;
    }

    char show_lcs[show_length];
    memset(show_lcs, '\0', show_length);

    //loop counter declaration
    int i;

    //maximum input string length is 100
    if (str1_length > 100 || str2_length > 100) {
        printf("\n\nString length is greater than 100....please enter string with length less than 100\n\n");
        return 0;
    }

    //copy of user input to local array
    strcpy(str1, argv[1]);
    strcpy(str2, argv[2]);

    //calling of lcs funcion
    lcs(str1, str2, show_lcs);

    show_length = strlen(show_lcs);

    printf("\n\nCommon Sequence is --> ");
    for (i = show_length - 1; i >= 0; i--) {
        printf("%c", show_lcs[i]);
    }
    //printf("Common Sequence is --> %s", show_lcs);
    printf("\n\nLength of common sequence is --> %d\n", show_length);
    return 0;
}

/*
 This function takes 2 strings as input and one output string which is copied with common sequence
*/
int lcs(char str1[], char str2[], char show_lcs[]) {
    //loop counter declaration
    int i, j;

    //local variable declaration
    int row = str1_length + 1;
    int column = str2_length + 1;
    char b[row][column];
    int c[row][column];

    //displaying 2 input strings
    printf("\n\nString 1 is --> %s\n", str1);
    printf("\nString 2 is --> %s\n", str2);

    //initializing number array
    initialize_array(c);

    //traverse through string1
    for (i = 1; i < row; i++) {
        //traverse through string2
        for (j = 1; j < column; j++) {
            //in both string are same as per recursion equation, calculate number matrix value and diagonal
            if (str1[i - 1] == str2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'D'; //diagonal element
            } else {
                if (str1_length >= str2_length) {
                    //if upper element is greater or equal with left element ....save it accordingly
                    if (c[i - 1][j] >= c[i][j - 1]) {
                        c[i][j] = c[i - 1][j];
                        b[i][j] = 'U';  //upper element
                    }
                        //if left element is greater than upper element ....save it accordingly
                    else {
                        c[i][j] = c[i][j - 1];
                        b[i][j] = 'L';
                    }
                } else {
                    //if left element is greater or equal with left element ....save it accordingly
                    if (c[i][j - 1] >= c[i - 1][j]) {
                        c[i][j] = c[i][j - 1];
                        b[i][j] = 'L';  //left element
                    }
                        //if upper element is greater than upper element ....save it accordingly
                    else {
                        c[i][j] = c[i - 1][j];
                        b[i][j] = 'U'; //upper element
                    }
                }
            }
        }
    }

    //calling function to load output using pointer matrix and string 1
    load_output(str1, b, show_lcs);
    return 0;
}

/*
 This function initializes first row and first column of number matrix
 */
int initialize_array(int c[str1_length + 1][str2_length + 1]) {
    int i, j;
    //initialize first row with 0
    for (i = 0; i < str1_length + 1; i++) {
        c[i][0] = 0;
    }
    //initialize first column with 0
    for (j = 0; j < str2_length + 1; j++) {
        c[0][j] = 0;
    }

    return 0;
}

/*
 This function load output array using pointer matrix and string 1 using directions , U, L, D
 */
int load_output(char str1[], char b[str1_length + 1][str2_length + 1], char show_lcs[]) {
    //local variable declaration
    int i, j;
    int row = str1_length;
    int column = str2_length;
    int output_index = 0;

    //if either row or column gets zero, stop the loop
    //start loop with last row, last column element
    while (row != 0 && column != 0) {
        //if pointer matrix shows D, store character in output array
        if (b[row][column] == 'D') {
            show_lcs[output_index] = str1[row - 1];
            //reduce counter to reach diagonal element above current element in matrix
            row--;
            column--;
            //increase counter of output array
            output_index++;
        }
            //if pointer matrix shows U, move one row up in matrix
        else if (b[row][column] == 'U') {
            //reduce row counter
            row--;
        }
            //if pointer matrix shows L, move one column up in matrix
        else if (b[row][column] == 'L') {
            //reduce column counter
            column--;
        }
    }

    return 0;
}
