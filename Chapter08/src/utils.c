#include "utils.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validate_positive_float(float value) {
    return value > 0;
}

int validate_positive_int(int value) {
    return value > 0;
}

void pause_program() {
    printf("\nPress Enter to continue...");
    getchar();
}
