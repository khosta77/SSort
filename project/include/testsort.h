#ifndef SSORT_TESTSORT_H
#define SSORT_TESTSORT_H

#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <ctime>
#include "stepansort.h"

using namespace std;


class testsort {
private:
//    template<typename T1, typename T2>
    vector<function<void(int *arr, const int N, string &name)>> foo = {
            testsort::test_bubble,
            testsort::test_cocktail,
            testsort::test_insertion,
            testsort::test_gnome,
//            testsort::test_merge, // не работает с большими массивами
//            testsort::test_tree, // не работает с большими массивами
            testsort::test_tim,
            testsort::test_selection,
            testsort::test_comb,
            testsort::test_shell,
            testsort::test_heap,
            testsort::test_quick,
//            testsort::test_stooge // Очень медлянная
    };

    const size_t TEST = 10;

public:

    testsort() {
        string name;

        for (int size = 1000; size <= 30000;  size+=1000) {
            int mass[size] = {};
            cout << "===================================================" << endl;
            for (size_t i = 0; i < TEST; i++) {
                randmass(mass, size);
                srand(time(0));
                unsigned int start_time = clock(); // начальное время
                foo[i](mass, size, name);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = (end_time - start_time); // искомое время
                cout << name
                     << " | time = " << search_time
                     << " | SIZE = " << size << endl;
            }
        }
    }

private:
    template<typename T1, typename T2>
    void fprintf(T1 *mas, const T2 N) {
        for (size_t i = 0; i < N; i++) {
            cout << mas[i] << " ";
        }
        cout << endl;
    }

    template<typename T1, typename T2>
    void randmass(T1 *mas, const T2 N) {
//        int buf_mass[] = {10, 1, 2, 3, 9, 8, 7, 5, 6, 4};
        for (size_t i = 0; i < N; i++) {
            mas[i] = rand() % N;
        }
    }

private:
//============================================================================================================
    /** \БЛОК - прослойка для тестов, ничего более.
     * */

    static void test_bubble(int *array, const int SIZE, string &str) {
        ss::Bubble(array, SIZE);
        str = "Bubble";
    }

    static void test_cocktail(int *array, const int SIZE, string &str) {
        ss::Cocktail(array, SIZE);
        str = "Cocktail";
    }

    static void test_insertion(int *array, const int SIZE, string &str) {
        ss::Insertion(array, SIZE);
        str = "Insertion";
    }

    static void test_gnome(int *array, const int SIZE, string &str) {
        ss::Gnome(array, SIZE);
        str = "Gnome";
    }

    static void test_merge(int *array, const int SIZE, string &str) {
        ss::Merge(array, SIZE);
        str = "Merge";
    }

    static void test_tree(int *array, const int SIZE, string &str) {
        ss::Tree(array, SIZE);
        str = "Tree";
    }

    static void test_tim(int *array, const int SIZE, string &str) {
        ss::Tim(array, SIZE);
        str = "Tim";
    }

    static void test_selection(int *array, const int SIZE, string &str) {
        ss::Selection(array, SIZE);
        str = "Selection";
    }

    static void test_comb(int *array, const int SIZE, string &str) {
        ss::Comb(array, SIZE);
        str = "Comb";
    }

    static void test_shell(int *array, const int SIZE, string &str) {
        ss::Shell(array, SIZE);
        str = "Shell";
    }

    static void test_heap(int *array, const int SIZE, string &str) {
        ss::Heap(array, SIZE);
        str = "Heap";
    }

    static void test_quick(int *array, const int SIZE, string &str) {
        ss::Quick(array, SIZE);
        str = "Quick";
    }

    static void test_stooge(int *array, const int SIZE, string &str) {
        ss::Stooge(array, SIZE);
        str = "Stooge";
    }
//============================================================================================================
};

#endif //SSORT_TESTSORT_H
