#include "list.h"

#include "door_struct.h"

typedef struct node {
    struct door door;
    struct node* next;
} node;

struct node* init(const struct door* door) {
    node* cell = (node*)malloc(sizeof(node));
    cell->door = *door;
    cell->next = NULL;

    return cell;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (elem->next == NULL) {
        elem->next = init(door);
    } else {
        node* p_next = (node*)malloc(sizeof(node));
        p_next->next = elem->next;
        elem->next = p_next;
        p_next->door = *door;
    }
    return elem;
}

struct node* find_door(int door_id, struct node* root) {
    node* res = NULL;
    node* current = root->next;
    while (current->next) {
        if (current->door.id == door_id) {
            res = current;
        }
        current = current->next;
    }
    return res;
}

// struct node* remove_door(struct node* elem, struct node* root) {
//     node* current = root->next;
//     node* last_node = root;
//     while (current) {
//         if (elem == root) {
//             last_node->next = current->next;
//             free(elem);
//         } else if (current->next == NULL) {
//             last_node->next = NULL;
//             free(elem);
//         }
//         last_node = current;
//         current = current->next;
//     }

//     return root;
// }

void destroy(struct node* root) {
    node* go = root;
    while (go) {
        go = remove_door(go, go);
    }
    free(go);
}

// void output(struct node *n) {
//     node* current = n->next;
//     while (current)
//     {
//         printf("%d %d\n", current->door.id, current->door.status);
//         printf("%p", n->next);
//         current = current->next;
//     }
// }

// void check_test(int result, const char* test_name) {
//     if (result == SUCCESS) {
//         printf("%s: SUCCESS\n", test_name);
//     } else {
//         printf("%s: FAIL\n", test_name);
//     }
// }