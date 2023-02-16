#include <stdio.h>

// Structure of Employee
typedef struct
{
    char full_name[20];
    int employee_ID;
    float salary;
} Employee;

// Function to add employee details
void addEmployeeDetails(Employee EmployeeDB[], int n)
{
    Employee emp;
    int fg, i;
    do
    {
        printf("Enter Employee-ID: ");
        scanf("%d", &emp.employee_ID);
        fg = 0;
        for (i = 0; i < n; i++)
        {
            if (EmployeeDB[i].employee_ID == emp.employee_ID)
            {
                printf("employee_ID already exist!");
                fg = 1;
            }
        }
    } while (fg != 0);
    getchar();
    printf("Enter Employee Full Name: ");
    scanf("%[^\n]", emp.full_name);
    printf("Enter Employee salary: ");
    scanf("%f", &emp.salary);

    EmployeeDB[n] = emp;
}

// Function to find employee record
void findEmployee(Employee EmployeeDB[], int n)
{
    int i, id;
    printf("Enter Employee-ID to search: ");
    scanf("%d", &id);
    for (i = 0; i < n; i++)
    {
        if (EmployeeDB[i].employee_ID == id)
        {
            printf("Employee Name: %s\n", EmployeeDB[i].full_name);
            printf("Employee id : %d\n", EmployeeDB[i].employee_ID);
            printf("Salary : %.2f\n", EmployeeDB[i].salary);
            return;
        }
    }
    printf("Not found\n");
}

// Function to update a Employee record
void updateEmployee(Employee EmployeeDB[], int n)
{
    int id, i, op;
    printf("Enter Employee-ID to update: ");
    scanf("%d", &id);
    for (i = 0; i < n; i++)
    {
        if (EmployeeDB[i].employee_ID == id)
        {
            printf("\n1. Update name: ");
            printf("\n2. Update salary: ");
            printf("\nEnter option: ");
            scanf("%d", &op);
            if (op == 1)
            {
                printf("Enter name: ");
                getchar();
                scanf("%[^\n]", EmployeeDB[i].full_name);
            }
            else
            {
                printf("Enter salary: ");
                scanf("%f", &EmployeeDB[i].salary);
            }
            return;
        }
    }
}

// Function to count and print the total number of Employees in the system
void countEmployees(int n)
{
    printf("Total number of Employees in the system = %d\n", n);
}

// Function to print the Employee Database
void printDB(Employee EmployeeDB[], int n)
{
    int i;
    printf("Employee-Name Employee-ID Salary\n");
    printf("-----------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%-20s%-15d%.2f\n", EmployeeDB[i].full_name, EmployeeDB[i].employee_ID, EmployeeDB[i].salary);
    }
}

// Function to read the Employee Database from the file
void ReadDB(FILE *f, Employee EmployeeDB[], int *n)
{
    char line[100];
    int i = 0;

    while (!feof(f))
    {
        fgets(EmployeeDB[i].full_name, 20, f);
        if (feof(f))
            break;
        fscanf(f, "%d%f\n", &EmployeeDB[i].employee_ID, &EmployeeDB[i].salary);
        i++;
    }
    *n = i;
}

// Function to write the Employee Database to the file
void WriteDB(FILE *f, Employee EmployeeDB[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fprintf(f, "%-20s\n%d\t%.2f\n", EmployeeDB[i].full_name, EmployeeDB[i].employee_ID, EmployeeDB[i].salary);
    }
}

// main function
int main()
{
    Employee EmployeeDB[100];
    int n = 0, op;
    FILE *f;
    // open the file
    f = fopen("employee.dat", "r");
    if (f != NULL)
    {
        // read the Employee Database from the file
        ReadDB(f, EmployeeDB, &n);
        // close the file
        fclose(f);
    }

    printf("* Employee Database *");
    while (1)
    {
        // display the menu
        printf("\n1. Add Employee Details.");
        printf("\n2. Update Employee Record.");
        printf("\n3. Find Employee Record.");
        printf("\n4. Count Employees.");
        printf("\n5. Print the Database.");
        printf("\n6. Exit.");

        printf("\nEnter option: ");
        scanf("%d", &op);
        if (op == 6)
            break;

        switch (op)
        {
        case 1:
            // add employee details
            addEmployeeDetails(EmployeeDB, n);
            n++;
            break;

        case 2:
            // Update Employee Record
            updateEmployee(EmployeeDB, n);
            break;

        case 3:
            // Find Employee Record
            findEmployee(EmployeeDB, n);
            break;

        case 4:
            // Count Employees
            countEmployees(n);
            break;

        case 5:
            // Print the Database
            printDB(EmployeeDB, n);
            break;
        }
    }

    // open the file in write mode
    f = fopen("employee.dat", "w");
    // write the Employee Database to the file
    WriteDB(f, EmployeeDB, n);
    // close the file
    fclose(f);

    return 0;
}