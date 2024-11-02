#include "door_struct.h"

#ifndef LIST_H
#define LIST_H

struct node;

struct node* init(const struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
// struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);
// void output(struct node* n);
// void check_test(int result, const char* test_name) {

#endif