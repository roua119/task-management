#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct Task {
    int id;
    char description[100];
    int priority_level;
    char status[15];
    struct Task* next;
} Task;

Task* createTask(int id, const char* description, int priority_level, const char* status) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->priority_level = priority_level;
    strcpy(newTask->status, status);
    newTask->next = NULL;
    return newTask;
}

void insertTask(Task** head, Task* newTask) {
    if (*head == NULL || (*head)->priority_level < newTask->priority_level) {
        newTask->next = *head;
        *head = newTask;
    } else {
        Task* current = *head;
        while (current->next != NULL && current->next->priority_level >= newTask->priority_level) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }
}

void deleteTask(Task** head, int id) {
    Task* current = *head;
    Task* prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Task with ID %d deleted.\n", id);
}

void updateTaskStatus(Task* head, int id, const char* newStatus) {
    const char* statuses[] = {"Pending", "In Progress", "Completed"};
    Task* current = head;

    while (current != NULL) {
        if (current->id == id) {
            for (int i = 0; i < 3; i++) {
                if (strcasecmp(newStatus, statuses[i]) == 0) {
                    strcpy(current->status, statuses[i]);
                    printf("Task with ID %d updated to status: %s\n", id, statuses[i]);
                    return;
                }
            }
            printf("Invalid status. Use: Pending, In Progress, or Completed.\n");
            return;
        }
        current = current->next;
    }

    printf("Task with ID %d not found.\n", id);
}


void displayTasks(Task* head) {
    const char* statuses[] = {"Pending", "In Progress", "Completed"};

    for (int i = 0; i < 3; i++) {
        Task* current = head;
        printf("%s tasks:\n", statuses[i]);
        while (current != NULL) {
            if (strcasecmp(current->status, statuses[i]) == 0)
 {
                printf("  ID: %d, Desc: %s, Priority: %d\n", current->id, current->description, current->priority_level);
            }
            current = current->next;
        }
        printf("\n");
    }
}

void searchByPriority(Task* head, int priority_level) {
    Task* current = head;
    int found = 0;

    while (current != NULL) {
        if (current->priority_level == priority_level) {
            printf("  ID: %d, Desc: %s, Status: %s\n", current->id, current->description, current->status);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No tasks found with priority %d.\n", priority_level);
    }
}

int main() {
    Task* taskList = NULL;
    int choice, id, priority_level;
    char description[100], status[15];

    while (1) {
        printf("\nTask Management System\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Update Task Status\n");
        printf("4. Display Tasks\n");
        printf("5. Search by Priority\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Task ID: ");
                scanf("%d", &id);
                printf("Enter Description: ");
                scanf(" %[^\n]", description);
               do {
    printf("Enter Priority Level (1-5): ");
    scanf("%d", &priority_level);
    if (priority_level < 1 || priority_level > 5) {
        printf("Invalid priority level. Please enter a value between 1 and 5.\n");
    }
} while (priority_level < 1 || priority_level > 5);

                printf("Enter Status (Pending, In Progress, Completed): ");
                scanf("%s", status);
                insertTask(&taskList, createTask(id, description, priority_level, status));
                break;
            case 2:
                printf("Enter Task ID to delete: ");
                scanf("%d", &id);
                deleteTask(&taskList, id);
                break;
            case 3:
                printf("Enter Task ID to update: ");
                scanf("%d", &id);
                printf("Enter new Status (Pending, In Progress, Completed): ");
                scanf("%s", status);
                updateTaskStatus(taskList, id, status);
                break;
            case 4:
                displayTasks(taskList);
                break;
            case 5:
                printf("Enter Priority Level to search: ");
                scanf("%d", &priority_level);
                searchByPriority(taskList, priority_level);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
