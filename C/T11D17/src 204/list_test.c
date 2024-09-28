#include "list.h"

#include "door_struct.h"

void output(struct node *n);

int main() {
    door d, d2;

    d.id = 1;
    d2.id = 2;
    d.status = 1;
    d2.status = 2;

    struct node *list = init(&d);

    struct node *test = add_door(list, &d2);
    if (test != NULL) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }

    find_door(3, list);
    // if (remove_door(test, list) != NULL) {
    //     printf("SUCCESS");
    // } else {
    //     printf("FAIL");
    // }

    destroy(list);

    return 0;
}
