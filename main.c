#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 32

struct Employee
{
    char name[128];
    int workdays[5];
};

void read_file(char *filename, int size, struct Employee *employees)
{
    FILE *fp;
    char c;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
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
        char *day;
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                day = "hetfo";
                break;
            case 1:
                day = "kedd";
                break;
            case 2:
                day = "szerda";
                break;
            case 3:
                day = "csutortok";
                break;
            case 4:
                day = "pentek";
                break;
            }
            if (strstr(days, day) != NULL)
            {
                workdays[i] = 1;
            }
        }

        strcpy(employees[i].name, name);
        memcpy(employees[i].workdays, workdays, sizeof(workdays));
        i++;
    }
    fclose(fp);
}

int **initSchedule(int size)
{
    int **schedule = (int **)malloc(5 * sizeof(int *));
    for (int i = 0; i < 5; i++)
    {
        schedule[i] = (int *)malloc(size * sizeof(int));
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < size; j++)
        {
            schedule[i][j] = -1;
        }
    }
    return schedule;
}

void initEmployees(struct Employee *employees)
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        strcpy(employees[i].name, "");
        memset(employees[i].workdays, 0, sizeof(employees[i].workdays));
    }
}

int getEmployeeSize(struct Employee *employees)
{
    int size = 0;
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        if (employees[i].name[0] != '\0')
        {
            size++;
        }
    }
    return size;
}

void newEmployee(struct Employee *employees, int size)
{
    char name[128];
    int workdays[5] = {0, 0, 0, 0, 0};
    char days[128];
    printf("Enter name (Surname_Lastname): ");
    scanf("%s", name);
    printf("Enter workdays (delim: ,): ");
    scanf("%s", days);
    char *day;
    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            day = "hetfo";
            break;
        case 1:
            day = "kedd";
            break;
        case 2:
            day = "szerda";
            break;
        case 3:
            day = "csutortok";
            break;
        case 4:
            day = "pentek";
            break;
        }
        if (strstr(days, day) != NULL)
        {
            workdays[i] = 1;
        }
    }
    // replace the _ with space in the name
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == '_')
        {
            name[i] = ' ';
        }
    }
    strcpy(employees[size].name, name);
    memcpy(employees[size].workdays, workdays, sizeof(workdays));
}

void removeEmployee(struct Employee *employees, int size, int index)
{
    for (int i = index; i < size; i++)
    {
        strcpy(employees[i].name, employees[i + 1].name);
        memcpy(employees[i].workdays, employees[i + 1].workdays, sizeof(employees[i + 1].workdays));
    }
    strcpy(employees[size - 1].name, "");
    memset(employees[size - 1].workdays, 0, sizeof(employees[size - 1].workdays));
}

void modifyEmployee(struct Employee *employees, int size, int index)
{
    char name[128];
    int workdays[5] = {0, 0, 0, 0, 0};
    char *days;
    printf("* Enter 'same' to keep the same data *\n");
    printf("Enter new name (Surname_Lastname): ");
    scanf("%s", name);
    printf("Enter workdays (delim: ,): ");
    scanf("%s", days);
    char *day;
    if (strcmp(name, "same") != 0)
    {
        for (int i = 0; i < strlen(name); i++)
        {
            if (name[i] == '_')
            {
                name[i] = ' ';
            }
        }
        strcpy(employees[index].name, name);
    }
    if (strcmp(days, "same") != 0)
    {
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                day = "hetfo";
                break;
            case 1:
                day = "kedd";
                break;
            case 2:
                day = "szerda";
                break;
            case 3:
                day = "csutortok";
                break;
            case 4:
                day = "pentek";
                break;
            }
            if (strstr(days, day) != NULL)
            {
                workdays[i] = 1;
            }
        }
        memcpy(employees[index].workdays, workdays, sizeof(workdays));
    }
}

void scheduleEmlpoyees(int **schedule, int size, int capacity[], struct Employee *employees)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (employees[i].workdays[j] == 1)
            {
                for (int k = 0; k < size; k++)
                {
                    if (schedule[j][k] == i || capacity[j] == 0)
                    {
                        break;
                    }
                    if (schedule[j][k] == -1)
                    {
                        schedule[j][k] = i;
                        capacity[j]--;
                        break;
                    }
                }
            }
        }
    }
}

void descheduleEmployees(int **schedule, int size, int capacity[], struct Employee *employees)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (employees[i].workdays[j] == 1)
            {
                for (int k = 0; k < size; k++)
                {
                    if (schedule[j][k] == i)
                    {
                        schedule[j][k] = -1;
                        capacity[j]++;
                        break;
                    }
                }
            }
        }
    }
}

void printSchedule(int **schedule, int size, struct Employee *employees)
{
    char *days[] = {"HETFO", "KEDD", "SZERDA", "CSUTORTOK", "PENTEK"};
    for (int i = 0; i < 5; i++)
    {
        printf("------------\n%s \n", days[i]);
        for (int j = 0; j < size; j++)
        {
            if (schedule[i][j] != -1)
            {
                printf(" - %s \n", employees[schedule[i][j]].name);
            }
        }
    }
}

void printEmployees(struct Employee *employees, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d: %s - ", i, employees[i].name);
        for (int j = 0; j < 5; j++)
        {
            if (employees[i].workdays[j] == 1)
            {
                switch (j)
                {
                case 0:
                    printf("hetfo ");
                    break;
                case 1:
                    printf("kedd ");
                    break;
                case 2:
                    printf("szerda ");
                    break;
                case 3:
                    printf("csutortok ");
                    break;
                case 4:
                    printf("pentek");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void runMenu(int **schedule, struct Employee *employees, int capacity[])
{
    int choice;
    int id;
    do
    {
        system("clear");
        printf("1. Register new employee\n");
        printf("2. Remove employee\n");
        printf("3. Modify employee\n");
        printf("4. Schedule all registered employees\n");
        printf("5. Deschedule all registered employees\n");
        printf("6. List employees\n");
        printf("7. List schedule\n");
        printf("8. Exit\n");
        printf("Enter operation number: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("clear");
            newEmployee(employees, getEmployeeSize(employees));
            break;
        case 2:
            system("clear");
            printEmployees(employees, getEmployeeSize(employees));
            descheduleEmployees(schedule, getEmployeeSize(employees), capacity, employees);
            printf("Index of employee to remove: ");
            scanf("%d", &id);
            removeEmployee(employees, getEmployeeSize(employees), id);
            scheduleEmlpoyees(schedule, getEmployeeSize(employees), capacity, employees);
            break;
        case 3:
            system("clear");
            printEmployees(employees, getEmployeeSize(employees));
            descheduleEmployees(schedule, getEmployeeSize(employees), capacity, employees);
            printf("Index of employee to modify: ");
            scanf("%d", &id);
            modifyEmployee(employees, getEmployeeSize(employees), id);
            scheduleEmlpoyees(schedule, getEmployeeSize(employees), capacity, employees);
            break;
        case 4:
            system("clear");
            printf("Scheduling all registered employees...\n");
            scheduleEmlpoyees(schedule, getEmployeeSize(employees), capacity, employees);
            break;
        case 5:
            system("clear");
            printf("Descheduling all registered employees...\n");
            descheduleEmployees(schedule, getEmployeeSize(employees), capacity, employees);
            break;
        case 6:
            system("clear");
            printf("Employees:\n");
            printEmployees(employees, getEmployeeSize(employees));
            break;
        case 7:
            system("clear");
            printf("Schedule:\n");
            printSchedule(schedule, getEmployeeSize(employees), employees);
            break;
        case 8:
            printf("Exiting...\n");
            return;
            break;
        }
        printf("\nPress enter to continue...");
        getchar();
        getchar();
    } while (choice != 8);
}

int main()
{
    struct Employee employees[MAX_EMPLOYEES];
    initEmployees(employees);
    read_file("data", 2, employees);
    int size = getEmployeeSize(employees);
    int capacity[] = {2, 4, 6, 3, 4};
    int **schedule = initSchedule(size);

    runMenu(schedule, employees, capacity);
    return 0;
}