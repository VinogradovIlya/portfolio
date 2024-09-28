#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void bublesort(struct door* doors);
void door_close(door* doors);
void output(door* doors);

int main() {
    door doors[DOORS_COUNT];

    initialize_doors(doors);
    bublesort(doors);
    door_close(doors);
    output(doors);

    return 0;
}

/*----------------------------
Doors initialization function
ATTENTION!!!
DO NOT CHANGE!
----------------------------*/
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void bublesort(struct door* doors) {
    int temp;
    for (int i = 0; i < DOORS_COUNT; i++) {
        for (int j = 0; j < DOORS_COUNT; j++) {
            if (doors[j].id > doors[i].id) {
                temp = doors[i].id;
                doors[i].id = doors[j].id;
                doors[j].id = temp;
            }
        }
    }
}

void door_close(door* doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
    }
}

void output(door* doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i < DOORS_COUNT - 1) {
            printf("\n");
        }
    }
}