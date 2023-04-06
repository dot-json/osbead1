#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// write employee struct with name and workdays. the workdays is an array of 5 integers
struct employee
{
    char name[128];
    int workdays[5];
};
typedef struct employee employee;

// write a function to read a file and print it to the screen
void read_file(char *filename, int size)
{
    FILE *fp;
    char c;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    employee *employees = malloc(size * sizeof(employee));
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';
        char *divider = strchr(line, ';');
        *divider = '\0';
        char *name = line;
        char *days = divider + 1;
        int workdays[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i++)
        {
            workdays[i] = days[i] - '0';
        }
        // print the name and workdays
        printf("Name: %s\n", name);
        printf("Workdays: ");
        for (int k = 0; k < 5; k++)
        {
            printf("%d ", workdays[k]);
        }
        printf("\n");
        // employees[i].name = name;
        // employees[i].workdays = workdays;
        i++;
    }
    fclose(fp);
}

int main()
{
    read_file("data", 2);
    return 0;
}