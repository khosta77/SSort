#include "../include/stepansort.h"

template<typename T1, typename T2>
void fprintf(T1 *mas, const T2 N) {
    for (size_t i = 0; i < N; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

template<typename T1, typename T2>
void randmass(T1 *mas, const T2 N) {
    int buf_mass[] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
    for (size_t i = 0; i < N; i++) {
        mas[i] = buf_mass[i];
    }
}

// Нельзя создать массив функция, чтобы шаблоны принемали?
//template <typename T>

typedef void (StepanSort::*srt) (int *mass, const int N);

const size_t SIZE_ARRAYS = 13;
srt trs[] = {
        &StepanSort::Bubble,
        &StepanSort::Cocktail,
        &StepanSort::Insertion,
        &StepanSort::Gnome,
        &StepanSort::Merge,
        &StepanSort::Tree,
        &StepanSort::Tim,
        &StepanSort::Selection,
        &StepanSort::Comb,
        &StepanSort::Shell,
        &StepanSort::Heap,
        &StepanSort::Quick,
        &StepanSort::Stooge
};


int main(int argc, char **argv) {
    const int SIZE = 10;
    int mass[SIZE] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
    fprintf(mass, SIZE);
    cout << "-=====================-" << endl;
//    StepanSort::Bubble(mass, SIZE);
//    fprintf(mass, SIZE);
//    randmass(mass, SIZE);
//    cout << "!==================!" << endl;
    for (size_t i = 0; i < SIZE_ARRAYS; i++) {
        (m.*trs[0])(mass, SIZE);
        cout << i << "|";
        fprintf(mass, SIZE);
        randmass(mass, SIZE);
    }
    return 0;
}

