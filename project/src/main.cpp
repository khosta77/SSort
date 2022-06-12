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

// Нельзя создать массив функция, чтобы шаблоны принемали?
//template <typename T>
typedef void (StepanSort::*srt) (int *mass, const int N);

const size_t SIZE_ARRAYS = 3;
srt trs[] = {
        &StepanSort::Bubble,
        &StepanSort::Merge,
        &StepanSort::Gnome
};

int main(int argc, char **argv) {
    const int SIZE = 10;
    int mass[SIZE] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
    fprintf(mass, SIZE);
    cout << "-==================-" << endl;
    ss::Bubble(mass, SIZE);
    fprintf(mass, SIZE);
    randmass(mass, SIZE);
//    for (size_t i = 0; i < SIZE_ARRAYS; i++) {
//        (m.*trs[0])(mass, SIZE);
//        fprintf(mass, SIZE);
//        randmass(mass, SIZE);
//    }
    return 0;
}

