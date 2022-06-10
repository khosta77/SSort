#ifndef STEPANSORT_H
#define STEPANSORT_H

#include <iostream>

using namespace std;

class StepanSort{
private:
    void swap(int& a, int& b);
private:
    void stoogesort(int* arr, int l, int h);
private:
    int correct(int *arr, int size);
    void shuffle(int *arr, int size);
public:
    // Алгоритмы устойчивой сортировки
    void Bubble(int* mas, const int N); // О(n^2)
    void Cocktail(int *mas, const int N); // О(n^2)
    void Insertion(int *mas, const int N); // О(n^2)
    void Gnome(int *mas, const int N); // О(n^2)
    void Merge(int* mas, const int N); // O(n*log(n))
    // Алгоритмы неустойчивой сортировки
    void Selection(int* mas, const int N); // О(n^2)
    void Comb(int* mas, const int N); // О(n^2)
    void Shell(int* mas, const int N); // O(n*log2(n))
    void Quick(int* mas, const int N); // O(n*log(n))
    void Stooge(int* mas, const int N); // O(n^2.71)
    // Непрактичные алгоритмы сортировки
    void Bogo(int* mas, const int N); // не использовать после N >= 12 => t > 8 секунд

};

inline void StepanSort::swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

inline void StepanSort::stoogesort(int *mas, int l, int r){
    if (l >= r){
       return;
    }
    if (mas[l] > mas[r]){
       swap(mas[l], mas[r]);
    }
    if (r - l + 1 > 2) {
       int t = (r - l + 1) / 3;
       stoogesort(mas, l, r - t);
       stoogesort(mas, l + t, r);
       stoogesort(mas, l, r - t);
    }
}

inline int StepanSort::correct(int *arr, int size){
    while (size-- > 0){
       if (arr[size - 1] > arr[size]){
           return 0;
       }
    }
    return 1;
}

inline void StepanSort::shuffle(int *arr, int size){
    for (int i = 0; i < size; ++i){
        swap(arr[i], arr[(rand() % size)]);
    }
}

void StepanSort::Bubble(int* mas, const int N){
    for(int i = 0; i < N; i++ ){
        for(int j = 0; j < N; j++){
            if(mas[i] < mas[j]){
                swap(mas[i], mas[j]);
            }
        }
    }
}

void StepanSort::Cocktail(int *mas, const int N){
    int control = N - 1;
    int left  = 0;
    int right = N - 1;
    do {
        for (int i = left; i < right; i++) {
            if (mas[i] > mas[i + 1]) {
                swap(mas[i], mas[i + 1]);
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--) {
            if (mas[i] < mas[i - 1]) {
                swap(mas[i], mas[i - 1]);
                control = i;
            }
        }
        left = control;
    } while (left < right);
}

void StepanSort::Insertion(int *mas, const int N){
    int i, buffer;
    for(int j = 1; j < N; j++){
        buffer = mas[j];
        i = j - 1;
        while(i >= 0 && mas[i] > buffer){
            mas[i + 1] =  mas[i];
            mas[i] = buffer;
            i--;
        }

    }
}

void StepanSort::Gnome(int *mas, const int N){
    int i = 1;
    int j = 2;
    while (i < N){
        if (mas[i - 1] < mas[i]){
            i = j;
            j = j + 1;
        }
        else{
            swap(mas[i - 1], mas[i]);
            i = i - 1;
            if (i == 0){
                i = j;
                j = j + 1;
            }
        }
    }
}

inline void StepanSort::Merge(int *mas, const int N){
    if (N > 1){
        int const left_size = N / 2;
        int const right_size = N - left_size;

        Merge(&mas[0], left_size);
        Merge(&mas[left_size], right_size);

        int lidx = 0, ridx = left_size, idx = 0;
        static int *aux= new int [N];

        while (lidx < left_size || ridx < N){
            if (mas[lidx] < mas[ridx]){
                aux[idx++] = move(mas[lidx]);
                lidx++;
            }
            else{
                aux[idx++] = move(mas[ridx]);
                ridx++;
            }
            if (lidx == left_size){
                copy(make_move_iterator(&mas[ridx]), make_move_iterator(&mas[N]), &aux[idx]);
                break;
            }
            if (ridx == N){
                copy(make_move_iterator(&mas[lidx]), make_move_iterator(&mas[left_size]), &aux[idx]);
                break;
            }
        }
        copy(make_move_iterator(aux), make_move_iterator(&aux[N]), mas);
    }
}

void StepanSort::Selection(int* mas, const int N){
    for(int i = 0; i < N; i++){
        int min = i;
        for(int j = i; j < N; j++){
            if(mas[j] < mas[min]){
                min = j;
            }
        }
        if(min != i){
            swap(mas[min], mas[i]);
        }
    }
}

void StepanSort::Comb(int *mas, const int N){
    double factor = 1.2473309;
    int step = N - 1;
    while (step >= 1){
        for (int i = 0; i + step < N; i++){
            if (mas[i] > mas[i + step]){
                swap(mas[i], mas[i + step]);
            }
        }
        step /= factor;
    }
}

inline void StepanSort::Quick(int *mas, const int N){
    int left = 0;
    int right = N - 1;
    int central_element = mas[N / 2];
    do{
        while (mas[left] < central_element) {
            left++;
        }
        while (mas[right] > central_element) {
            right--;
        }
        if(left <= right){
            swap(mas[left], mas[right]);
            left++;
            right--;
        }
    }  while (left <= right);
    if(right > 0) {
        Quick(mas, right + 1);
    }
    if (left < N) {
        Quick(&mas[left], N - left);
    }
}

void StepanSort::Stooge(int *mas, const int N){
    stoogesort(mas, 0, N);
}

void StepanSort::Bogo(int *mas, const int N){
    while (!correct(mas, N)){
        shuffle(mas, N);
    }
}

void StepanSort::Shell(int *mas, const int N){
    for(int s = N / 2; s > 0; s /= 2) {
        for(int i = s; i < N; ++i) {
            for(int j = i - s; (j >= 0) && (mas[j] > mas[j + s]); j -= s) {
                swap(mas[j], mas[j + s]);
            }
        }
    }
}

#endif // STEPANSORT_H
