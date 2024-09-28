#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int y;
    int mo;
    int d;
    int h;
    int mi;
    int s;
    int st;
    int p;
} data;

int read_file(char *path, FILE **f, int *err);
void print_arr(FILE *f, int size);
void my_sort_year(FILE *f, int size);
void write_record_in_file(FILE *pfile, data *record_to_write, int index);
data read_record_from_file(FILE *pfile, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int compare(data i, data j);
void add_record_to_file(FILE *f, int *err);

int main() {
    FILE *f = NULL;
    char path[256];
    int move = 0, error = 0;
    int valid = scanf(" %[^\n]", path);
    if (valid != 1) {
        error = 1;
        // printf("0001: Error in path input");
    }
    valid = scanf("%d", &move);
    if (valid != 1) {
        error = 1;
        // printf("0002: Error in move input");
    }
    if (error == 0) {
        int size;
        if ((size = read_file(path, &f, &error)) == 0 && (move == 0 || move == 1)) {
            error = 1;
            // printf("0004: size file == 0");
        }
        if (move == 0 && error == 0) {
            print_arr(f, size);
        } else if (move == 1 && error == 0) {
            my_sort_year(f, size);
            print_arr(f, size);
        } else if (move == 2 && error == 0) {
            add_record_to_file(f, &error);
            if (!error) {
                fclose(f);
                int new_size = read_file(path, &f, &error);
                fseek(f, new_size, SEEK_SET);
                my_sort_year(f, new_size);
                // my_sort_year(f, size);
                fclose(f);
                new_size = read_file(path, &f, &error);
                my_sort_year(f, new_size);
                print_arr(f, size);
            }
        }
    }
    if (error == 1) {
        printf("n/a");
    }
    if (f != NULL) {
        fclose(f);
    }
    return 0;
}
// ../datasets/door_state_1

int read_file(char *path, FILE **f, int *err) {
    if ((*f = fopen(path, "r+b")) == NULL) {
        *err = 1;
        // printf("0003: Error in open file");
    }
    fseek(*f, 0, SEEK_END);
    int size = ftell(*f);
    rewind(*f);

    return size;
}

void print_arr(FILE *f, int size) {
    int line = size / sizeof(data);
    for (int i = 0; i < line; i++) {
        data arr = read_record_from_file(f, i);
        printf("%d %d %d ", arr.y, arr.mo, arr.d);
        printf("%d %d %d ", arr.h, arr.mi, arr.s);
        printf("%d %d", arr.st, arr.p);
        if (i < line - 1) {
            printf("\n");
        }
    }
}

void my_sort_year(FILE *f, int size) {
    int line = size / sizeof(data);
    for (int i = 0; i < line; i++) {
        for (int j = i + 1; j < line; j++) {
            // fseek(f, i*sizeof(data), SEEK_SET);
            data start = read_record_from_file(f, i);
            data now = read_record_from_file(f, j);
            if (compare(start, now) > 0) {
                // printf("swap");
                swap_records_in_file(f, i, j);
            }
        }
    }
}
int compare(data i, data j) {
    int res = 0;
    if (i.y != j.y) {
        return i.y - j.y;
    }
    if (i.mo != j.mo) {
        return i.mo - j.mo;
    }
    if (i.d != j.d) {
        return i.d - j.d;
    }
    if (i.h != j.h) {
        return i.h - j.h;
    }
    if (i.mi != j.mi) {
        return i.mi - j.mi;
    }
    if (i.s != j.s) {
        return i.s - j.s;
    }
    return res;
}

// Function of mutual transfer of two records in the file by their indexes.
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    // Read both records from file to variables
    data record1 = read_record_from_file(pfile, record_index1);
    data record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
    // printf("swap");
}

// Function of reading a record of a given type from a file by its serial number.
data read_record_from_file(FILE *pfile, int index) {
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(data);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    data record;
    fread(&record, sizeof(data), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, data *record_to_write, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the
    // file.
    int offset = index * sizeof(data);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(data), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

void add_record_to_file(FILE *f, int *err) {
    if (f != NULL) {
        data new_record;
        scanf("%d", &new_record.y);
        scanf("%d", &new_record.mo);
        scanf("%d", &new_record.d);
        scanf("%d", &new_record.h);
        scanf("%d", &new_record.mi);
        scanf("%d", &new_record.s);
        scanf("%d", &new_record.st);
        scanf("%d", &new_record.p);
        fseek(f, 0, SEEK_END);
        fwrite(&new_record, sizeof(data), 1, f);
        fflush(f);
    } else {
        *err = 1;
    }
}