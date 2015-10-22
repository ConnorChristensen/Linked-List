/*************************
** Program: Assignment5.c
** Author: Connor Christensen
** Date: 6/6/2015
** Description: A snazzy program that creates and sorts linked lists
** Input: Various characters and numbers from the keyboard that makes the program go
** Output: Snazzy colors and sorting
*************************/

#include <stdio.h>
#include <stdlib.h>
//this is to include the bool
#include <stdbool.h>
//this is for usleep() which pauses the computer code
//for a certain ammount of miliseconds
#include <unistd.h>
//this is for the random seed
#include <time.h>
//my .h library
#include "./prototypes.h"


int main() {
    //seed for random number generator
    srand(time(NULL));
    struct node *head = NULL;
    struct node *tail = NULL;
    
    //call the main program
    the_menu(head, tail);
    
    //if the list has not been deleted, delete the list
    if (head != NULL) {
        head = clear(head);
    }
    printf("\nThank you for using the program\n");
}

void the_menu(struct node *head, struct node *tail) {
    char choice[2];
    int place, number;
    do {
        printf("\nWould you like to... \nenter numbers, ");
        printf("sort, remove, print, delete list, ");
        printf("clear screen, insert pointer, or quit?");
        printf("\n(e/s/r/p/d/c/i/q) ");
        scanf("%s", choice);
        if (choice[0] == 'e') {
            //menu for entering items
            entering_menu(&head, &tail);
        }
        else if (choice[0] == 's') {
            //menu for sorting the list
            head = sort_menu(head);
        }
        else if (choice[0] == 'r') {
            //menu for removing nodes
            head = removing_entries(head);
        }
        else if (choice[0] == 'p') {
            //prints the linked list
            print_colors(head);
        }
        else if (choice[0] == 'c') {
            //clears the screen
            clear_screen(head);
        }
        else if (choice[0] == 'd') {
            //deletes the linked list
            head = clear(head);
        }
        else if (choice[0] == 'i') {
            printf("Enter your place: ");
            scanf("%d", &place);
            printf("Enter your number: ");
            scanf("%d", &number);
            head = insert_middle(head, place, number);
        }
    } while (choice[0] != 'q');
}
void entering_menu(struct node **head, struct node **tail) {
    int list_number, x;
    char random[2];
    
    printf("How many items do you want to enter? ");
    scanf("%d", &list_number);
    
    printf("Would you like your inputs to be random? (y/n) ");
    scanf("%s", random);
    
    //for the number of items specified
    for (x = 0; x < list_number; x++) {
        if (random[0] == 'n') {
            //adds numbers defined by user
            not_random_add(head, tail, x);
        }
        else if (random[0] == 'y') {
            //adds numbers with the random generator
            random_add(head, tail, x);
        }
    }
    print_colors(*head);
}

int length (struct node *head) {
    int size = 0;
    
    while (head != NULL) {
        size++;
        head = head->next;
    }
    
    return size;
}

void print_colors(struct node *head) {
    struct node *temporary = head;
    int y;
    printf("Linked list: ");
    for (y = 0; y < length(head); y++) {
        //this is a ton of ansii escape codes to colorize every 10 digit
        //group a different color
        
        if ((temporary->value >= 0) && (temporary->value <= 9)) {
            printf("\e[31m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 10) && (temporary->value <= 19)) {
            printf("\e[32m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 20) && (temporary->value <= 29)) {
            printf("\e[33m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 30) && (temporary->value <= 39)) {
            printf("\e[34m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 40) && (temporary->value <= 49)) {
            printf("\e[35m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 50) && (temporary->value <= 59)) {
            printf("\e[36m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 60) && (temporary->value <= 69)) {
            printf("\e[41m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 70) && (temporary->value <= 79)) {
            printf("\e[42m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 80) && (temporary->value <= 89)) {
            printf("\e[43m%d\e[0m ", temporary->value);
        }
        else if ((temporary->value >= 90) && (temporary->value <= 99)) {
            printf("\e[44m%d\e[0m ", temporary->value);
        }
        else {
            //if its bigger than 99 then they are just white
            printf("%d ", temporary->value);
        }
        //run through the list
        temporary = temporary->next;
    }
    printf("\n");
}
void print_normal(struct node *head) {
    //this is a normal printing function with no colors
    //its not used, but should be included
    
    struct node *temporary = head;
    int y;
    printf("Linked list: ");
    for (y = 0; y < length(head); y++) {
        printf("%d ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

struct node * push(struct node *head, int x) {
    struct node *insert_pointer = NULL;
    
    //allocate space
    insert_pointer = malloc(sizeof(struct node));
    //set value
    insert_pointer->value = x;
    //set pointer next
    insert_pointer->next = head;
    //point head to the new node
    head = insert_pointer;
    
    return head;
}
struct node * append(struct node *head, struct node *tail, int x) {
    //same thing as head, but uses tail
    tail->next = malloc(sizeof(struct node));
    tail->next->value = x;
    tail->next->next = NULL;
    tail = tail->next;
    
    return tail;
}

struct node * sort_menu(struct node *head) {
    char sorting_choice[2];
    
    printf("\nWould you like to sort in Ascending, Decending or Neither? \n(a/d/n) ");
    scanf("%s", sorting_choice);
    
    if (sorting_choice[0] == 'a') {
        printf("\n\n");
        head = sort_ascending(head);
    }
    else if (sorting_choice[0] == 'd') {
        printf("\n\n");
        head = sort_decending(head);
    }
    
    printf("\nSorted:\n");
    print_colors(head);
    
    return head;
}

bool is_decending(struct node *head) {
    //this checks to see if its already sorted in decending order
    //so it doesnt try to sort a sorted list
    
    struct node *pointer = head;
    bool is_sorted = true;
    
    while (pointer->next != NULL) {
        if ((pointer->value) < (pointer->next->value)) {
            is_sorted = false;
        }
        pointer = pointer->next;
    }
    
    if (is_sorted == true) {
        return true;
    }
    else {
        return false;
    }
    
}
struct node * sort_decending(struct node *head) {
    //create a pointer to run though the list
    struct node *pointer = head;
    //create a lasso so that you dont loose the items when you switch
    struct node *lasso = NULL;
    
    
    //if its already sorted, no need to sort
    if (is_decending(head) == true) {
        printf("\nThe list is sorted in decending order\n");
        return head;
    }
    //but you should sort it if its not already sorted
    else {
        //as long as its not sorted
        while (is_decending(head) == false) {
            //if the next next value is less than the next[x3] value
            if ((pointer->next->value) < (pointer->next->next->value)) {
                //then the lasso holds on to pointer next so
                //it doesnt loose the list
                lasso = pointer->next;
                //set pointer next after lasso to start reversing
                pointer->next = lasso->next;
                //if lasso next next doesnt exist, dont make the program seg fault
                if (lasso->next->next == NULL) {
                    lasso->next = NULL;
                }
                else {
                    //oftherwise, finish up the switching process
                    lasso->next = lasso->next->next;
                }
                pointer->next->next = lasso;
                pointer = head;
                
                //this is a UI function that does pretty things
                rest();
                print_colors(head);
            }
            else {
                //if the first thing isnt triggered, move along
                pointer = pointer->next;
            }
            if ((head->value) < (head->next->value)) {
                //this is a quick swap by value
                //if I dont do this, it will seg fault when it tries to move
                //a smaller number to the first position
                int store1 = head->value;
                int store2 = head->next->value;
                
                head->value = store2;
                head->next->value = store1;
            }
        }
    }
    return head;
}

bool is_ascending(struct node *head) {
    //just the opposite of is_decending
    struct node *pointer = head;
    bool is_sorted = true;
    
    while (pointer->next != NULL) {
        if ((pointer->value) > (pointer->next->value)) {
            is_sorted = false;
        }
        pointer = pointer->next;
    }
    
    if (is_sorted == true) {
        return true;
    }
    else {
        return false;
    }
    
}
struct node * sort_ascending(struct node *head) {
    //basically the same set up for sort decending
    struct node *pointer = head;
    struct node *lasso = NULL;
    
    
    if (is_ascending(head) == true) {
        printf("\nThe list is sorted in ascending order\n");
        return head;
    }
    else {
        while (is_ascending(head) == false) {
            if ((pointer->next->value) > (pointer->next->next->value)) {
                lasso = pointer->next;
                pointer->next = lasso->next;
                if (lasso->next->next == NULL) {
                    lasso->next = NULL;
                }
                else {
                    lasso->next = lasso->next->next;
                }
                pointer->next->next = lasso;
                pointer = head;
                
                rest();
                print_colors(head);
            }
            else {
                pointer = pointer->next;
            }
            if ((head->value) > (head->next->value)) {
                int store1 = head->value;
                int store2 = head->next->value;
                
                head->value = store2;
                head->next->value = store1;
            }
        }
    }
    return head;
}

void not_random_add(struct node **head, struct node **tail, int x) {
    int add;
    printf("Enter #%d: ", (x+1));
    scanf("%d", &add);
    //if head doesnt contain anything trigger push
    if (*head == NULL) {
        *head = push(*head, x);
        *tail = *head;
    }
    else {
        //otherwise, append with tail
        *tail = append(*head, *tail, add);
    }
}
void random_add(struct node **head, struct node **tail, int x) {
    int add;
    add = rand() % 99;
    if (*head == NULL) {
        *head = push(*head, x);
        *tail = *head;
    }
    else {
        *tail = append(*head, *tail, add);
    }
}

struct node * removing_entries(struct node *head) {
    int list_number, x, number;
    char loop_again, remove;
    
    do {
        printf("How many items do you want to remove? ");
        scanf("%d", &list_number);
        for (x = 0; x < list_number; x++) {
            printf("Enter #%d: ", (x+1));
            scanf("%d", &number);
            //removes the node
            head = remove_node(head, number);
        }
        print_colors(head);
        printf("\nWould you like to remove more? (y/n) ");
        scanf("%s", &loop_again);
    } while (loop_again == 'y');
    
    return head;
}
struct node * clear(struct node *head ) {
    struct node *pointer = NULL;
    while (head->next != NULL) {
        pointer = head->next;
        free(head);
        head = pointer;
    }
    free(head);
    printf("Linked list has been deleted\n");
    
    return NULL;
}
struct node * remove_node(struct node *head, int q) {
    struct node *pointer = head;
    struct node *lasso = NULL;
    
    while (pointer->next != NULL) {
        if (pointer->next->value == q) {
            lasso = pointer->next;
            pointer->next = lasso->next;
            free(lasso);
        }
        else {
            pointer = pointer->next;
        }
    }
    
    return head;
}

struct node * insert_middle(struct node *head, int space, int number) {
    struct node *holder = head;
    struct node *insert = NULL;
    int x;
    
    for (x = 0; x < space; x++) {
        holder = holder->next;
    }
    insert = malloc(sizeof(struct node));
    insert->value = number;
    insert->next = holder->next;
    holder->next = insert;
    
    print_colors(head);
    return head;
}

void rest() {
    printf("\e[K");
    printf("\e[1A");
    usleep(60000);
}
void clear_screen(struct node *head) {
    printf("\e[2J");
    printf("\e[K");
    printf("\e[1A");
    printf("\e[K");
    printf("\e[0;0H");
    print_colors(head);
}
