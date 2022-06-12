#ifndef PROJECT_INCLUDE_STEPANSORT_H_
#define PROJECT_INCLUDE_STEPANSORT_H_

#include <iostream>
#include <exception>

using namespace std;

namespace stepan_sort {

    class StepanSort {
    private:
        /** \brief Меняет местами a и b
         * \param a параметр а
         * \param b параметр b
         * */
        template<typename T>
        inline void swap (T &a, T &b) {
            int temp = a;
            a = b;
            b = temp;
        }

//// Это какая то сортировка пока что не понятно, что она делает.
//    private:
//        // Что это?
//        template<typename T>
//        void stoogesort(T *arr, T l, T r)  {
//            if (l >= r) {
//                return;
//            }
//            if (arr[l] > arr[r]) {
//                swap(arr[l], arr[r]);
//            }
//            if (r - l + 1 > 2) {
//                int t = (r - l + 1) / 3;
//                stoogesort(arr, l, r - t);
//                stoogesort(arr, l + t, r);
//                stoogesort(arr, l, r - t);
//            }
//        }

//// Часть Bogo сортировки - она не эффективная имет смысл удалить.
//    private:
//        // Что это?
//        template<typename T>
//        int correct(T *arr, T size);
//
//        // Что это?
//        template<typename T>
//        void shuffle(T *arr, T size);

    public:
        // Алгоритмы устойчивой сортировки
        template<typename T>
        void Bubble(T *mas, const T N); // О(n^2)

        template<typename T>
        void Cocktail(T *mas, const T N); // О(n^2)

        template<typename T>
        void Insertion(T *mas, const T N); // О(n^2)

        template<typename T>
        void Gnome(T *mas, const T N); // О(n^2)

        template<typename T>
        void Merge(T *mas, const T N); // O(n*log(n))

        // Алгоритмы неустойчивой сортировки
        template<typename T>
        void Selection(T *mas, const T N); // О(n^2)

        template<typename T>
        void Comb(T *mas, const T N); // О(n^2)

        template<typename T>
        void Shell(T *mas, const T N); // O(n*log2(n))

        template<typename T>
        void Quick(T *mas, const T N); // O(n*log(n))

//        template<typename T>
//        void Stooge(T *mas, const T N); // O(n^2.71)

//        // Непрактичные алгоритмы сортировки
//        template<typename T>
//        void Bogo(T *mas, const T N); // не использовать после N >= 12 => t > 8 секунд
    } m;

//    template<typename T>
//    inline void StepanSort::stoogesort(T *mas, T l, T r) {
//        if (l >= r) {
//            return;
//        }
//        if (mas[l] > mas[r]) {
//            swap(mas[l], mas[r]);
//        }
//        if (r - l + 1 > 2) {
//            int t = (r - l + 1) / 3;
//            stoogesort(mas, l, r - t);
//            stoogesort(mas, l + t, r);
//            stoogesort(mas, l, r - t);
//        }
//    }

//    template<typename T>
//    inline int StepanSort::correct(T *arr, T size) {
//        while (size-- > 0) {
//            if (arr[size - 1] > arr[size]) {
//                return 0;
//            }
//        }
//        return 1;
//    }
//
//    template<typename T>
//    inline void StepanSort::shuffle(T *arr, T size) {
//        for (int i = 0; i < size; ++i) {
//            swap(arr[i], arr[(rand() % size)]);
//        }
//    }

    template<typename T>
    void StepanSort::Bubble(T *mas, const T N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (mas[i] < mas[j]) {
                    swap(mas[i], mas[j]);
                }
            }
        }
    }

    template<typename T>
    void StepanSort::Cocktail(T *mas, const T N) {
        int control = N - 1;
        int left = 0;
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

    template<typename T>
    void StepanSort::Insertion(T *mas, const T N) {
        int i, buffer;
        for (int j = 1; j < N; j++) {
            buffer = mas[j];
            i = j - 1;
            while (i >= 0 && mas[i] > buffer) {
                mas[i + 1] = mas[i];
                mas[i] = buffer;
                i--;
            }

        }
    }

    template<typename T>
    void StepanSort::Gnome(T *mas, const T N) {
        int i = 1;
        int j = 2;
        while (i < N) {
            if (mas[i - 1] < mas[i]) {
                i = j;
                j = j + 1;
            } else {
                swap(mas[i - 1], mas[i]);
                i = i - 1;
                if (i == 0) {
                    i = j;
                    j = j + 1;
                }
            }
        }
    }

    template<typename T>
    inline void StepanSort::Merge(T *mas, const T N) {
        if (N > 1) {
            int const left_size = N / 2;
            int const right_size = N - left_size;

            Merge(&mas[0], left_size);
            Merge(&mas[left_size], right_size);

            int lidx = 0, ridx = left_size, idx = 0;
            static int *aux = new int[N];

            while (lidx < left_size || ridx < N) {
                if (mas[lidx] < mas[ridx]) {
                    aux[idx++] = move(mas[lidx]);
                    lidx++;
                } else {
                    aux[idx++] = move(mas[ridx]);
                    ridx++;
                }
                if (lidx == left_size) {
                    copy(make_move_iterator(&mas[ridx]), make_move_iterator(&mas[N]), &aux[idx]);
                    break;
                }
                if (ridx == N) {
                    copy(make_move_iterator(&mas[lidx]), make_move_iterator(&mas[left_size]), &aux[idx]);
                    break;
                }
            }
            copy(make_move_iterator(aux), make_move_iterator(&aux[N]), mas);
        }
    }

    template<typename T>
    void StepanSort::Selection(T *mas, const T N) {
        for (int i = 0; i < N; i++) {
            int min = i;
            for (int j = i; j < N; j++) {
                if (mas[j] < mas[min]) {
                    min = j;
                }
            }
            if (min != i) {
                swap(mas[min], mas[i]);
            }
        }
    }

    template<typename T>
    void StepanSort::Comb(T *mas, const T N) {
        double factor = 1.2473309;
        int step = N - 1;
        while (step >= 1) {
            for (int i = 0; i + step < N; i++) {
                if (mas[i] > mas[i + step]) {
                    swap(mas[i], mas[i + step]);
                }
            }
            step /= factor;
        }
    }

    template<typename T>
    inline void StepanSort::Quick(T *mas, const T N) {
        int left = 0;
        int right = N - 1;
        int central_element = mas[N / 2];
        do {
            while (mas[left] < central_element) {
                left++;
            }
            while (mas[right] > central_element) {
                right--;
            }
            if (left <= right) {
                swap(mas[left], mas[right]);
                left++;
                right--;
            }
        } while (left <= right);
        if (right > 0) {
            Quick(mas, right + 1);
        }
        if (left < N) {
            Quick(&mas[left], N - left);
        }
    }

//    template<typename T>
//    void StepanSort::Stooge(T *mas, const T N) {
//        stoogesort(mas, 0, N);
//    }

//    template<typename T>
//    void StepanSort::Bogo(T *mas, const T N) {
//        while (!correct(mas, N)) {
//            shuffle(mas, N);
//        }
//    }

    template<typename T>
    void StepanSort::Shell(T *mas, const T N) {
        for (int s = N / 2; s > 0; s /= 2) {
            for (int i = s; i < N; ++i) {
                for (int j = i - s; (j >= 0) && (mas[j] > mas[j + s]); j -= s) {
                    swap(mas[j], mas[j + s]);
                }
            }
        }
    }

};

using namespace stepan_sort;
//using ss = stepan_sort;

#endif  // PROJECT_INCLUDE_STEPANSORT_H_
