#include <stdio.h>
#include <stdlib.h>

// Structure to store employee details
struct Employee {
    int id;
    char name[50];
    float basicSalary;
    float hra;
    float da;
    float deductions;
    float netSalary;
};

// Function to calculate salary
void calculateSalary(struct Employee *e) {
    e->hra = 0.20 * e->basicSalary;       // 20% HRA
    e->da = 0.10 * e->basicSalary;        // 10% DA
    e->deductions = 0.05 * e->basicSalary;// 5% deduction

    e->netSalary = e->basicSalary + e->hra + e->da - e->deductions;
}

// Function to add employee
void addEmployee() {
    struct Employee e;
    FILE *fp = fopen("employee.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &e.id);

    printf("Enter Name: ");
    scanf("%s", e.name);

    printf("Enter Basic Salary: ");
    scanf("%f", &e.basicSalary);

    // Calculate salary
    calculateSalary(&e);

    fwrite(&e, sizeof(e), 1, fp);
    fclose(fp);

    printf("Employee Added Successfully!\n");
}

// Function to display employees
void displayEmployees() {
    struct Employee e;
    FILE *fp = fopen("employee.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Employee Records ---\n");

    while (fread(&e, sizeof(e), 1, fp)) {
        printf("\nID: %d", e.id);
        printf("\nName: %s", e.name);
        printf("\nBasic Salary: %.2f", e.basicSalary);
        printf("\nHRA: %.2f", e.hra);
        printf("\nDA: %.2f", e.da);
        printf("\nDeductions: %.2f", e.deductions);
        printf("\nNet Salary: %.2f\n", e.netSalary);
    }

    fclose(fp);
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n\n--- Employee Salary System ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
