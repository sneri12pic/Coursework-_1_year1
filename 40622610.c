// Code written by Stepan Demianenko
// 12.03.2023
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define LENGTH 25000

void output_file_creation(int line_counter, int character_counter, int comment_counter, int int_variable_counter, int double_variable_counter, int char_variable_counter, char arr_of_variables[2048][50], int variables_counter, int arr_of_references[2048]);

int main()
{
    // Openning any .c file on which we would like to use
    // Here we are saying a location of a test file 
    FILE *input = fopen("test1.c", "r");
     // Simple check if the file was opened successfully 
    if (!input)
    {
        perror("File opening failed");
        return 1;
    }
    else
    {
        printf("*************************************\n");
        printf("*   File was sucessfully openned    *\n");
        printf("*************************************\n");
    }

    // Counters
    int counter = 0;
    int line_counter = 1;      // Adds 1 to itself when the line will be found
    int character_counter = 0; // Adds 1 to itself when the letter will be found
    int comment_counter = 0;   // Adds 1 to itself when the comment will be found

    int int_variable_counter = 0;    // Adds 1 to itself when the int variable will be found
    int double_variable_counter = 0; // Adds 1 to itself when the double variable will be found
    int char_variable_counter = 0;   // Adds 1 to itself when the char variable will be found

    int index = 0;
    char curr_character;

    // Arrays
    char arr[LENGTH];
    char arr_of_variables[2048][50];
    int arr_of_references[2048];
    for (int i = 0; i < 2048; i++)
    {
        // Setting every i to minus one, so it is easy to count every reference without declaration
        arr_of_references[i] = -1;
    }
    //Going through file using character to character method
    while ((curr_character = fgetc(input)) != EOF)
    {
        // 1)Line counter
        if (curr_character == '\n')
        {
            line_counter++;
        }
        // 2)Character counter
        if (curr_character == ' ')
            ;
        else if (curr_character == '\t')
            ;
        else if (curr_character == '\n')
            ;
        else if (curr_character == '\0')
            ;
        else
        {
            // Getting number of characters in a file(excluding: '\n','\t','\0',' ')
            character_counter++;
        }

        // Setting array of characters which means that we will get one character in each array index(including: '\n','\t','\0',' ')
        arr[index] = curr_character;
        index++;
    }

    // Names of int, double, char variables
    char int_variable_name[50];
    char double_variable_name[50];
    char char_variable_name[50];

    // index_of_arr
    int index_of_ints_arr = 0;
    int local_counter = 0;

    // We are doing this for loop to delete comments so it is to find every variable excluding comments------------------------
    for (int i = 0; i < index; i++)
    {
        // Here are we are looking for comments
        if (arr[i] == '/' && arr[i + 1] == '/' && arr[i + 2] == ' ')
        {
            comment_counter++;
            while (arr[i] != '\n')
            {
                arr[i] = ' ';
                i++;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------------------

    // Checking every index in an already filled array for "/" and same on the next index if we found any, than we are adding one to comment counter
    for (int i = 0; i < index; i++)
    {
        // Here we are looking for int variables
        if ((arr[i - 1] == '\t' || arr[i - 1] == '\n' || arr[i - 1] == ' ') && arr[i] == 'i' && arr[i + 1] == 'n' && arr[i + 2] == 't' && arr[i + 3] == ' ')
        {
            // Going through all of pointer stars
            int j = i + 4;
            if (arr[j] == '*')
            {
                while (arr[j] == '*')
                {
                    j++;
                }
                j++;
            }
            // Here we are going through all variable name characters
            while (arr[j] != ' ')
            {
                int_variable_name[local_counter] = arr[j];
                local_counter++;
                j++;
            }
            j++;
            int_variable_name[local_counter] = '\0';
            // adding variables to an array of variables excluding the variables function declaration
            if (arr[j] != '(')
            {
                // Adding each name of int variables to an array of variables
                memcpy(arr_of_variables[index_of_ints_arr], int_variable_name, strlen(int_variable_name) + 1);
                // counter of ints
                index_of_ints_arr++;
                int_variable_counter++;
            }
            local_counter = 0;
        }

        else if ((arr[i - 1] == '\t' || arr[i - 1] == '\n' || arr[i - 1] == ' ') && arr[i] == 'd' && arr[i + 1] == 'o' && arr[i + 2] == 'u' && arr[i + 3] == 'b' && arr[i + 4] == 'l' && arr[i + 5] == 'e' && arr[i + 6] == ' ')
        {
            // Going through all of pointer stars
            int j = i + 7;
            if (arr[j] == '*')
            {
                while (arr[j] == '*')
                {
                    j++;
                }
                j++;
            }
            // Here we are going through all variable name characters
            while (arr[j] != ' ')
            {
                double_variable_name[local_counter] = arr[j];
                local_counter++;
                j++;
            }
            j++;
            double_variable_name[local_counter] = '\0';

            // adding variables to an array of variables excluding the variables function declaration
            if (arr[j] != '(')
            {
                // Adding each name of double variables to an array of variables
                memcpy(arr_of_variables[index_of_ints_arr], double_variable_name, strlen(double_variable_name) + 1);
                index_of_ints_arr++;
                // counter of doubles
                double_variable_counter++;
            }
            local_counter = 0;
        }
        else if ((arr[i - 1] == '\t' || arr[i - 1] == '\n' || arr[i - 1] == ' ') && arr[i] == 'c' && arr[i + 1] == 'h' && arr[i + 2] == 'a' && arr[i + 3] == 'r' && arr[i + 4] == ' ')
        {
            // Going through all of pointer stars
            int j = i + 5;
            if (arr[j] == '*')
            {
                while (arr[j] == '*')
                {
                    j++;
                }
                j++;
            }
            // Here we are going through all variable name characters
            while (arr[j] != ' ')
            {
                char_variable_name[local_counter] = arr[j];
                local_counter++;
                j++;
            }
            j++;
            char_variable_name[local_counter] = '\0';

            // adding variables to an array of variables excluding the variables function declaration
            if (arr[j] != '(')
            {
                // Adding each name of char variables to an array of variables
                memcpy(arr_of_variables[index_of_ints_arr], char_variable_name, strlen(char_variable_name) + 1);
                index_of_ints_arr++;
                // counter of doubles
                char_variable_counter++;
            }
            local_counter = 0;
        }
    }
    //------------------------------------------------------------------------------------------------------------------------

    // Adding every variable counter to know the total number of characters
    int variables_counter = int_variable_counter + double_variable_counter + char_variable_counter;

    // Main printf's----------------------------------------------------------------------------------------------------------
    printf("\n1) There are %d lines in the .c file", line_counter);
    printf("\n2) There are %d characters in the .c file", character_counter);
    printf("\n3) There are %d comments in the .c file", comment_counter);
    printf("\n4) There are %d total number of variables in the .c file", variables_counter);
    printf("\n--------------------------------------------------------");
    printf("\n5) int counter : %d", int_variable_counter);
    printf("\n6) double counter : %d", double_variable_counter);
    printf("\n7) char counter : %d\n", char_variable_counter);
    //------------------------------------------------------------------------------------------------------------------------

    // Here we find number of references--------------------------------------------------------------------------------------
    char token[100];
    for (int i = 0; i < variables_counter; i++)
    {
        token[0] = ' ';
        memcpy(token + 1, arr_of_variables[i], strlen(arr_of_variables[i]));
        token[strlen(arr_of_variables[i]) + 1] = ' ';
        token[strlen(arr_of_variables[i]) + 2] = '\0';

        // Here we are finding every specific token
        char *tmp = arr;
        while (tmp = strstr(tmp, token))
        {
            arr_of_references[i]++;
            tmp++;
        }

        token[0] = '\t';
        tmp = arr;
        while (tmp = strstr(tmp, token))
        {
            arr_of_references[i]++;
            tmp++;
        }
    }
    //------------------------------------------------------------------------------------------------------------------------

    // End----------------------------------------------------------------------------------------------------------
    output_file_creation(line_counter, character_counter, comment_counter, int_variable_counter, double_variable_counter, char_variable_counter, arr_of_variables, variables_counter, arr_of_references);
    fclose(input);
    return 0;
}

void output_file_creation(int line_counter, int character_counter, int comment_counter, int int_variable_counter, int double_variable_counter, int char_variable_counter, char arr_of_variables[2048][50], int variables_counter, int arr_of_references[2048])
{
    // Creating Output.s file
    FILE *fp;

    // Creating Output.s file where is every varible name is written and also it's time of reference
    // Here we are saying a location where Output.s file will be created or changed
    fp = fopen("Output.s", "w");

    // Simple check if the file creation and opening was done successfully 
    if (!fp)
    {
        perror("File opening failed");
    }

    // Outputing every varible name is written and also it's time of reference
    for (int i = 0; i < variables_counter; i++)
    {
        fprintf(fp, "%s\t%d\n", arr_of_variables[i], arr_of_references[i]);
    }

    // End
    fclose(fp);
}