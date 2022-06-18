#ifndef SSORT_TESTSORT_H
#define SSORT_TESTSORT_H

#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include "stepansort.h"

using namespace std;

#define filename "Test_Sort.csv"

class testsort {
public:
    testsort() {
        vector<pair<string, vector<int>>> df(TEST);
        for (size_t sort_num = 0; sort_num < TEST; sort_num++) {
            // Получим имя сортировки
            foo[sort_num]( 0, 0, df[sort_num].first);
            cout << df[sort_num].first << " - start"<< endl;

            // Начинаем анализ сортировок
            unsigned int start_time_all_sort = clock();

            test_sort( df, sort_num);

            unsigned int end_time_all_sort = clock();
            unsigned int search_time_all_sort = (end_time_all_sort - start_time_all_sort);

            cout << df[sort_num].first << " - end. Time: " << search_time_all_sort << endl;
        }
        cout << "---------------------------------------------------\n"
             << "End analysis" << endl;

//        output_the_result_to_cmd(df);
        output_the_result_to_csv(df);
    }

//============================================================================================================
protected:
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

    /**
     * Оптимально для тестов это
     * \SIZE = 1000000
     * \start_size = 0
     * \STEP = 500 // Будет более плавный график
     * \TIME_OUT = 5000000
     * */
    const size_t TEST = 10; // Колличество сортировок
    const int SIZE = 100000; // Максимальный размер массива
    const int start_size = 0; // Начальный размер массива
    const int STEP = 1000; // Шаг массива
    const int TIME_OUT = 142538; // Время выхода

    void test_sort(vector<pair<string, vector<int>>> &df, size_t num) {
        string buf;
        for (int size = start_size; size <= SIZE;  size+=STEP) {
            int arr[size] = {};
            randmass(arr, size);

            srand(time(0));
            unsigned int start_time = clock(); // начальное время

            foo[num](arr, size, buf);

            unsigned int end_time = clock(); // конечное время
            unsigned int search_time = (end_time - start_time); // искомое время

            df[num].second.push_back(search_time);

            if (search_time >= TIME_OUT) {
                return;
            }
        }
    }

    void output_the_result_to_cmd (vector<pair<string, vector<int>>> df) {
        cout << "===================================================" << endl;
        for (size_t i = 0; i < df.size(); i++) {
            cout << df[i].first << endl;

            for (size_t j = 0; j < df[i].second.size(); j++) {
                cout << "---> " << df[i].second[j] << endl;
            }

            cout << "===================================================" << endl;
        }
    }

    void output_the_result_to_csv (vector<pair<string, vector<int>>> df) {
        ofstream out;
        out.open(filename);
        if (!out.is_open()) {
            return;
        }

        // Запишем заголовок
        out << "#";
        for (size_t i = 0; i < TEST; i++) {
            out << df[i].first << ";";
        }
        out << endl;

        // Записываем данные
        // Первая строка может быть в нулях.
        for (size_t i = 0; i < TEST; i++) {
            out << df[i].second[0] << ";";
        }
        out << endl;

        // Вторая и тд строки
        for (size_t s_arr = 1; s_arr < (SIZE / STEP); s_arr++) {
            for (size_t i = 0; i < TEST; i++) {
                if (s_arr < df[i].second.size()) {
                    out << df[i].second[s_arr] << ";";
                } else {
                    out << ";";
                }
            }
            out << endl;
        }

        out.close();
    }

    template<typename T1, typename T2>
    void randmass (T1 *mas, const T2 N) {
        for (size_t i = 0; i < N; i++) {
            mas[i] = rand() % N;
        }
    }

//============================================================================================================
protected:
    /** \БЛОК - прослойка для тестов, ничего более. Сделан не очень красиво(
     * */

    static void test_bubble (int *array, const int SIZE, string &str) {
        str = "Bubble";
        if (SIZE == 0) {
            return;
        }
        ss::Bubble(array, SIZE);
    }

    static void test_cocktail (int *array, const int SIZE, string &str) {
        str = "Cocktail";
        if (SIZE == 0) {
            return;
        }
        ss::Cocktail(array, SIZE);
    }

    static void test_insertion (int *array, const int SIZE, string &str) {
        str = "Insertion";
        if (SIZE == 0) {
            return;
        }
        ss::Insertion(array, SIZE);
    }

    static void test_gnome (int *array, const int SIZE, string &str) {
        str = "Gnome";
        if (SIZE == 0) {
            return;
        }
        ss::Gnome(array, SIZE);
    }

    static void test_merge (int *array, const int SIZE, string &str) {
        str = "Merge";
        if (SIZE == 0) {
            return;
        }
        ss::Merge(array, SIZE);
    }

    static void test_tree (int *array, const int SIZE, string &str) {
        str = "Tree";
        if (SIZE == 0) {
            return;
        }
        ss::Tree(array, SIZE);
    }

    static void test_tim (int *array, const int SIZE, string &str) {
        str = "Tim";
        if (SIZE == 0) {
            return;
        }
        ss::Tim(array, SIZE);
    }

    static void test_selection (int *array, const int SIZE, string &str) {
        str = "Selection";
        if (SIZE == 0) {
            return;
        }
        ss::Selection(array, SIZE);
    }

    static void test_comb (int *array, const int SIZE, string &str) {
        str = "Comb";
        if (SIZE == 0) {
            return;
        }
        ss::Comb(array, SIZE);
    }

    static void test_shell (int *array, const int SIZE, string &str) {
        str = "Shell";
        if (SIZE == 0) {
            return;
        }
        ss::Shell(array, SIZE);
    }

    static void test_heap (int *array, const int SIZE, string &str) {
        str = "Heap";
        if (SIZE == 0) {
            return;
        }
        ss::Heap(array, SIZE);
    }

    static void test_quick (int *array, const int SIZE, string &str) {
        str = "Quick";
        if (SIZE == 0) {
            return;
        }
        ss::Quick(array, SIZE);
    }

    static void test_stooge (int *array, const int SIZE, string &str) {
        str = "Stooge";
        if (SIZE == 0) {
            return;
        }
        ss::Stooge(array, SIZE);
    }
//============================================================================================================
};

#endif //SSORT_TESTSORT_H
