#include "../include/stepansort.h"

template <typename T>
void fprintf(T *mas, const T N) {
    for (size_t i = 0; i < N; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

template <typename T>
void randmass(T *mas, const T N) {
    int buf_mass[] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
    for (size_t i = 0; i < N; i++) {
        mas[i] = buf_mass[i];
    }
}

int main(int argc, char **argv) {
    StepanSort srt;
    const int SIZE = 10;
    int mass[SIZE] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
    fprintf(mass, SIZE);
    srt.Bubble(mass, SIZE);
    fprintf(mass, SIZE);
    randmass(mass, SIZE);
    fprintf(mass, SIZE);
    return 0;
}

