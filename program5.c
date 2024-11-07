#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void insert_at_first(struct node** head, int new_data) {
    struct node* new_node = malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
}

void insert_at_end(struct node** head, int new_data) {
    struct node* new_node = malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void insert_at_pos(struct node** head, int pos, int new_data) {
    if (pos < 1) {
        printf("Position should be >= 1\n");
        return;
    }

    struct node* new_node = malloc(sizeof(struct node));
    new_node->data = new_data;

    if (pos == 1) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    struct node *last = *head;
    for (int i = 1; i < pos - 1 && last != NULL; i++) {
        last = last->next;
    }

    if (last == NULL) {
        printf("Position exceeds list length\n");
        free(new_node);
        return;
    }

    new_node->next = last->next;
    last->next = new_node;
}

void delete_begin(struct node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_last(struct node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct node *last = *head;
    struct node *second_last = NULL;

    while (last->next != NULL) {
        second_last = last;
        last = last->next;
    }

    if (second_last != NULL) {
        second_last->next = NULL;
    } else {
        *head = NULL; 
    }
    free(last);
}

void delete_pos(struct node** head, int pos) {
    if (*head == NULL || pos < 1) {
        printf("Invalid position or list is empty\n");
        return;
    }

    struct node *temp = *head;

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position exceeds list length\n");
        return;
    }

    struct node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void search(struct node** head, int search) {
    int i = 1;
    struct node *current = *head;
    while (current != NULL) {
        if (current->data == search) {
            printf("Element found %d at position %d\n", search, i);
            return;
        }
        current = current->next;
        i++;
    }
    printf("Element not found\n");
}

void printList(struct node* nod) {
    while (nod != NULL) {
        printf(" %d ", nod->data);
        nod = nod->next;
    }
    printf("\n");
}

int main() {
    struct node* head = NULL;
    int new_data, choice = 0; 

    while (choice != -1) {
        printf("Enter the choice\n1.Insert at beginning\n2.Insert at end\n3.Insert at position\n4.Delete at beginning\n5.Delete at end\n6.Delete at position\n7.Search\n-1.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &new_data);
                insert_at_first(&head, new_data);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 2:
                printf("Enter the data to insert: ");
                scanf("%d", &new_data);
                insert_at_end(&head, new_data);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 3:
                printf("Enter the data to insert: ");
                scanf("%d", &new_data);
                int pos;
                printf("Enter the position: ");
                scanf("%d", &pos);
                insert_at_pos(&head, pos, new_data);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 4:
                delete_begin(&head);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 5:
                delete_last(&head);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 6:
                printf("Enter the position: ");
                scanf("%d", &pos);
                delete_pos(&head, pos);
                printf("The updated Linked list is:\n");
                printList(head);
                break;
            case 7:
                printf("Enter the number to search: ");
                int s;
                scanf("%d", &s);
                search(&head, s);
                break;
            case -1:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    while (head != NULL) {
        delete_begin(&head);
    }

    return 0;
}
