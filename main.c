
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

typedef struct {
    char title[100];
    int completed; 
    int is_monthly; 
    int priority; 
    char due_date[20];
} Task;

int add_task(Task tasks[], int count, int is_monthly);
void edit_task(Task tasks[], int count);
void save_tasks(Task daily_tasks[], int daily_count, Task monthly_tasks[], int monthly_count);
void load_tasks(Task daily_tasks[], int *daily_count, Task monthly_tasks[], int *monthly_count);
void view_tasks(Task tasks[], int count);
int mark_tasks_as_completed(Task tasks[], int count);
int remove_task(Task tasks[], int count);
int manage_daily_tasks(Task tasks[], int daily_count);
int manage_monthly_tasks(Task tasks[], int monthly_count);
void view_all_tasks(Task daily_tasks[], int daily_count, Task monthly_tasks[], int monthly_count);

int main() {
    Task daily_tasks[MAX_TASKS];
    Task monthly_tasks[MAX_TASKS];
    int daily_count = 0, monthly_count = 0;
    int choice;

    load_tasks(daily_tasks, &daily_count, monthly_tasks, &monthly_count); // Load tasks at the start

    while (1) {
        printf("======================\n");
        printf("  TO-DO LIST MANAGER  \n");
        printf("======================\n\n");

        printf("1. Manage Daily Tasks\n");
        printf("2. Manage Monthly Tasks\n");
        printf("3. View All Tasks (Daily & Monthly)\n");
        printf("4. Exit\n\n");
        printf("-----------------------------------------\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                daily_count = manage_daily_tasks(daily_tasks, daily_count);
                break;
            case 2:
                monthly_count = manage_monthly_tasks(monthly_tasks, monthly_count);
                break;
            case 3:
                view_all_tasks(daily_tasks, daily_count, monthly_tasks, monthly_count);
                break;
            case 4:
                save_tasks(daily_tasks, daily_count, monthly_tasks, monthly_count);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int manage_daily_tasks(Task tasks[], int daily_count) {
    int choice;
    while (1) {
        printf("======================\n");
        printf("     DAILY TASKS      \n");
        printf("======================\n\n");

        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Remove Task\n");
        printf("4. Save and Exit Tasks\n");
        printf("5. View Tasks\n");
        printf("6. Mark Tasks as Completed\n");
        printf("7. Back to Main Menu\n\n");
        printf("-----------------------------------------\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                daily_count = add_task(tasks, daily_count, 0); // Daily task
                break;
            case 2:
                edit_task(tasks, daily_count);
                break;
            case 3:
                daily_count = remove_task(tasks, daily_count); 
                break;
            case 4:
                save_tasks(tasks, daily_count, NULL, 0); 
                return daily_count;  
            case 5:
                view_tasks(tasks, daily_count); 
                break;
            case 6:
                daily_count = mark_tasks_as_completed(tasks, daily_count); 
                break;
            case 7:
                return daily_count;  
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int manage_monthly_tasks(Task tasks[], int monthly_count) {
    int choice;
    while (1) {
        printf("======================\n");
        printf("    MONTHLY TASKS     \n");
        printf("======================\n\n");

        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Remove Task\n");
        printf("4. Save and Exit Tasks\n");
        printf("5. View Tasks\n");
        printf("6. Mark Tasks as Completed\n");
        printf("7. Back to Main Menu\n\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                monthly_count = add_task(tasks, monthly_count, 1); 
                break;
            case 2:
                edit_task(tasks, monthly_count);
                break;
            case 3:
                monthly_count = remove_task(tasks, monthly_count); 
                break;
            case 4:
                save_tasks(NULL, 0, tasks, monthly_count);
                return monthly_count;  
            case 5:
                view_tasks(tasks, monthly_count); 
                break;
            case 6:
                monthly_count = mark_tasks_as_completed(tasks, monthly_count); 
                break;
            case 7:
                return monthly_count; 
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void view_all_tasks(Task daily_tasks[], int daily_count, Task monthly_tasks[], int monthly_count) {
    printf("===========================================\n");
    printf("          VIEWING ALL TASKS (DAILY)        \n");
    printf("===========================================\n\n");
    view_tasks(daily_tasks, daily_count);

    printf("===========================================\n");
    printf("        VIEWING ALL TASKS (MONTHLY)        \n");
    printf("===========================================\n\n");
    view_tasks(monthly_tasks, monthly_count);
}

int add_task(Task tasks[], int count, int is_monthly) {
    if (count >= MAX_TASKS) {
        printf("Task limit reached. Cannot add more tasks.\n");
        return count;
    }

    printf("Enter task title: ");
    fgets(tasks[count].title, 100, stdin);
    tasks[count].title[strcspn(tasks[count].title, "\n")] = 0;

    printf("Enter task priority (1 - Low, 2 - Medium, 3 - High): ");
    scanf("%d", &tasks[count].priority);
    getchar(); 

    if (is_monthly) {
        printf("Enter due date (e.g., YYYY-MM-DD): ");
        fgets(tasks[count].due_date, 20, stdin);
        tasks[count].due_date[strcspn(tasks[count].due_date, "\n")] = 0;
    } else {
        strcpy(tasks[count].due_date, "N/A");
    }

    tasks[count].completed = 0;
    tasks[count].is_monthly = is_monthly;
    return count + 1;
}

void edit_task(Task tasks[], int count) {
    int task_number;

    if (count == 0) {
        printf("No tasks to edit.\n");
        return;
    }

    printf("Enter task number to edit (1 to %d): ", count);
    scanf("%d", &task_number);
    getchar(); 

    if (task_number < 1 || task_number > count) {
        printf("Invalid task number.\n");
        return;
    }

    task_number--; 

    printf("Editing task: %s\n", tasks[task_number].title);

    printf("Enter new task title: ");
    fgets(tasks[task_number].title, 100, stdin);
    tasks[task_number].title[strcspn(tasks[task_number].title, "\n")] = 0;

    printf("Enter new task priority (1 - Low, 2 - Medium, 3 - High): ");
    scanf("%d", &tasks[task_number].priority);
    getchar();  

    if (tasks[task_number].is_monthly) {
        printf("Enter new due date (e.g., YYYY-MM-DD): ");
        fgets(tasks[task_number].due_date, 20, stdin);
        tasks[task_number].due_date[strcspn(tasks[task_number].due_date, "\n")] = 0;
    }
}

void save_tasks(Task daily_tasks[], int daily_count, Task monthly_tasks[], int monthly_count) {
    FILE *file = fopen("tasks.dat", "wb");
    if (file == NULL) {
        printf("Error saving tasks.\n");
        return;
    }

    fwrite(&daily_count, sizeof(int), 1, file);
    if (daily_count > 0) {
        fwrite(daily_tasks, sizeof(Task), daily_count, file);
    }

    fwrite(&monthly_count, sizeof(int), 1, file);
    if (monthly_count > 0) {
        fwrite(monthly_tasks, sizeof(Task), monthly_count, file);
    }

    fclose(file);
    printf("Tasks saved successfully.\n");
}

void load_tasks(Task daily_tasks[], int *daily_count, Task monthly_tasks[], int *monthly_count) {
    FILE *file = fopen("tasks.dat", "rb");
    if (file == NULL) {
        printf("No saved tasks found. Starting fresh.\n");
        *daily_count = 0;
        *monthly_count = 0;
        return;
    }

    fread(daily_count, sizeof(int), 1, file);
    if (*daily_count > 0) {
        fread(daily_tasks, sizeof(Task), *daily_count, file);
    }

    fread(monthly_count, sizeof(int), 1, file);
    if (*monthly_count > 0) {
        fread(monthly_tasks, sizeof(Task), *monthly_count, file);
    }

    fclose(file);
    printf("Tasks loaded successfully.\n");
}

void view_tasks(Task tasks[], int count) {
    if (count == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("===========================================\n");
    printf("            VIEWING ALL TASKS              \n");
    printf("===========================================\n\n");

    for (int i = 0; i < count; i++) {
        printf("Task %d: %s\n", i + 1, tasks[i].title);
        printf("Priority: %d\n", tasks[i].priority);
        printf("Completed: %s\n", tasks[i].completed ? "Yes" : "No");
        printf("Type: %s\n", tasks[i].is_monthly ? "Monthly" : "Daily");
        printf("Due Date: %s\n\n", tasks[i].due_date);
    }
}

int mark_tasks_as_completed(Task tasks[], int count) {
    int task_number;
    if (count == 0) {
        printf("No tasks to mark as completed.\n");
        return count;
    }

    printf("Enter task number to mark as completed (1 to %d): ", count);
    scanf("%d", &task_number);
    getchar(); 

    if (task_number < 1 || task_number > count) {
        printf("Invalid task number.\n");
        return count;
    }

    task_number--;  

    tasks[task_number].completed = 1;

    printf("Task '%s' marked as completed.\n", tasks[task_number].title);

    for (int i = task_number; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    return count - 1; 
}

int remove_task(Task tasks[], int count) {
    int task_number;

    if (count == 0) {
        printf("No tasks to remove.\n");
        return count;
    }

    printf("Enter task number to remove (1 to %d): ", count);
    scanf("%d", &task_number);
    getchar();  

    if (task_number < 1 || task_number > count) {
        printf("Invalid task number.\n");
        return count;
    }

    task_number--;  

    for (int i = task_number; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    printf("Task removed successfully.\n");

    return count - 1;
}

    
