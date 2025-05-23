/*
 * Maintains a part in-memory database
 * using an ordered linked list.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NAME_LEN 50

// structure to represent a part
// which is also a linked list node
struct part {
    int number;
    char name[NAME_LEN + 1];
    int on_hand;
    struct part *next;
};

// global variables
// inventory points to the first element of the list
struct part *inventory;

// function prototypes
struct part *find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);
int read_line(char str[], int n);

int main(void) {
    char code;

    printf("Welcome to the Inventory Management System\n");
    printf("Commands: i (insert), s (search), u (update), p (print), q (quit)\n\n");

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);

        while (getchar() != '\n') // skips to end of line
            ;

        switch (code) {
            case 'i':
                insert();
                break;
            case 's':
                search();
                break;
            case 'u':
                update();
                break;
            case 'p':
                print();
                break;
            case 'q':
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Illegal code\n");
        }
        printf("\n");
    }
}

// looks up a part number in the inventory list; returns a
// pointer to the node containing the part number; if the
// part number is not found, return NULL
struct part *find_part(int number) {
    struct part *p;

    for (p = inventory;
         p != NULL && number > p->number;
         p = p->next)
        ;

    if (p != NULL && number == p->number)
        return p;

    return NULL;
}

// prompts the user for information about a new part and then
// inserts the part into the inventory sorted list; prints an
// error message and returns prematurely if the part already
// exists or space could not be allocated
void insert(void) {
    struct part *cur, *prev, *new_node;

    new_node = malloc(sizeof(struct part));
    if (new_node == NULL) {
        printf("Database is full; can't add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &new_node->number);

    for (cur = inventory, prev = NULL;
         cur != NULL && new_node->number > cur->number;
         prev = cur, cur = cur->next)
        ;

    if (cur != NULL && new_node->number == cur->number) {
        printf("Part already exists.\n");
        free(new_node);
        return;
    }

    printf("Enter part name: ");
    read_line(new_node->name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &new_node->on_hand);

    new_node->next = cur;
    if (prev == NULL)
        inventory = new_node;
    else
        prev->next = new_node;
}

// prompts the user to enter a part number, then looks up the
// part in the database; if the part exists, prints the name
// and quantity on hand; if not, prints an error message
void search(void) {
    int number;
    struct part *p;

    printf("Enter part number: ");
    scanf("%d", &number);

    p = find_part(number);
    if (p != NULL) {
        printf("Part name: %s\n", p->name);
        printf("Quantity on hand: %d\n", p->on_hand);
    } else {
        printf("Part not found.\n");
    }
}

// prompts the user to enter a part number; prints an error
// message if the part doesn't exists; otherwise, prompts
// the user to enter change in quantity on hand and updates
// the database
void update(void) {
    int number, change;
    struct part *p;

    printf("Enter part number: ");
    scanf("%d", &number);

    p = find_part(number);
    if (p != NULL) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        p->on_hand += change;
    } else {
        printf("Part not found.\n");
    }
}

// print a listing of all parts in the database, showing the part
// number, part name, and quantity on hand; part numbers will
// appear in ascending order
void print(void) {
    struct part *p;

    if (inventory == NULL) {
        printf("No parts present\n");
        return;
    }

    printf("Part Number  Part Name                    Quantity\n");
    printf("----------- ---------------------------- --------\n");
    for (p = inventory; p != NULL; p = p->next) {
        printf("%-11d %-28s %8d\n",
               p->number,
               p->name,
               p->on_hand);
    }
}

// skips leading white-space charachters, then reads the remainder
// of the input line and stores in str; truncates the line if its
// length exceeds n; returns the number of charachters stored
int read_line(char str[], int n) {
    int ch, i = 0;

    // skip leading white-space characters
    while (isspace(ch = getchar()))
        ;

    // read characters until newline or end-of-file
    while (ch != '\n' && ch != EOF) {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}
