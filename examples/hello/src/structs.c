#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct Person Person;
typedef struct Company Company;

struct Person {
    char name[50];
    Company *employer;  // company ref before full definition
};

struct Company {
    char name[100];
    Person *employees[100];
    int employee_count;
};

void print_point(Point p);
void print_point_new(Point *p);
void print_employee(Person *p);

int main(void) {
    // struct using tag (required for self-reference)
    // structs are used to copy arrays as = does not work
    struct arr { int a[4]; };
    struct arr m = {{1, 2, 3, 4}};
    struct arr n = {{}};
    printf("%d == %d\n", m.a[2], n.a[2]);
    m.a[3] = 100;
    n = m;
    printf("%d == %d\n", m.a[2], n.a[2]);

    // struct using typedef
    typedef struct { int x; int y; } Point;
    Point a = {1, 1};
    printf("point (%d, %d)\n", a.x, a.y);

    // nested structures and function call
    Company google = {"Google Inc.", {NULL}, 0};
    Person john = {"John Smith", &google};
    Person jane = {"Jane Doe", &google};

    print_employee(&john);
    print_employee(&jane);

    // enum using tag
    enum weekday {
        MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
    };
    enum weekday today = WEDNESDAY;
    printf("today = %d\n", today);

    enum status {
        INACTIVE = 0,
        ACTIVE = 1,
        PENDING = 5,
        SUSPENDED = 10
    };
    enum status user_status = ACTIVE;
    printf("user_status = %d\n", user_status);

    // enum using typedef
    typedef enum {
        FILE_SUCCESS = 100,
        FILE_NOT_FOUND = 404,
        FILE_PERMISSION_DENIED = 403,
        FILE_CORRUPTED = 500
    } FileError;
    FileError errors[] = {FILE_SUCCESS, FILE_NOT_FOUND, FILE_PERMISSION_DENIED, FILE_CORRUPTED};
    printf("error = %d\n", errors[1]);

    return 0;
}

// pass by pointer to avoid struct copy
void print_employee(Person *p) {
    printf("employee: %s\n", p->name);
    if (p->employer) {
        printf("works at: %s\n", p->employer->name);
    }
}

