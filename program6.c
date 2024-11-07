#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertEnd(struct Node** head_ref, int data) {
    struct Node* newNode = createNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void deleteNode(struct Node** head_ref, int key) {
    struct Node* temp = *head_ref;
    while (temp != NULL) {
        if (temp->data == key) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                *head_ref = temp->next; // If head node is to be deleted
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Node with data %d deleted.\n", key);
            return;
        }
        temp = temp->next;
    }
    printf("Node with data %d not found.\n", key);
}

struct Node* search(struct Node* head, int key) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, data;

    do {
        printf("\nMenu:\n");
        printf("1. Insert at End\n");
        printf("2. Delete a Node\n");
        printf("3. Search a Node\n");
        printf("4. Print List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &data);
                if (search(head, data)) {
                    printf("Node with data %d found.\n", data);
                } else {
                    printf("Node with data %d not found.\n", data);
                }
                break;
            case 4:
                printList(head);
                break;
            case 5:
                freeList(head);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

