#ifndef PROJECT_INCLUDE_STEPANSORT_H_
#define PROJECT_INCLUDE_STEPANSORT_H_

#include <iostream>
#include <exception>
#include <fstream>
#include <memory>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

namespace stepan_sort {
/** \class - Содержит в себе различные сортировки
 * P. s. Реализованы как оффициальные, так и не оффицальные(то есть не эффективные сортировки - за чем? \
 *    \ В учебных целях и просто было интересно.)
 * */
    class StepanSort {
    private:
        /** \brief Меняет местами a и b
         * \param a параметр а
         * \param b параметр b
         * */
        template<typename T>
        static inline void swap (T &a, T &b) {
            T temp = a;
            a = b;
            b = temp;
        }
    public:
//============================================================================================================
/*                                Алгоритмы устойчивой сортировки                                           */
//------------------------------------------------------------------------------------------------------------
        /** \brief Сортировка пузырьком - Проходит по массиву, сравнивает последовательные пары элементов и
         * меняет их местами, если они расположены в неправильном порядке.
         * \param mas массив
         * \param N размер массива
         *
         * В худшем случае: О(n^2)
         * В лучшем случае: О(1)
         * В среднем: О(n^2)
         * */
        template<typename T1, typename T2>
        void Bubble (T1 *mas, const T2 N) {
            for (T2 i = 0; i < N; i++) {
                for (T2 j = 0; j < N; j++) {
                    if (mas[i] < mas[j]) {
                        swap(mas[i], mas[j]);
                    }
                }
            }
        }
//------------------------------------------------------------------------------------------------------------
        /** \brief Сортировка перемешиванием - Двунаправленный, оптимизированный вариант сортировки пузырьком
         * \param mas массив
         * \param N размер массива
         * В худшем случае: О(n^2)
         * В лучшем случае: О(1)
         * В среднем: О(n^2)
         * */
        template<typename T1, typename T2>
        void Cocktail (T1 *mas, const T2 N) {
            T2 control = N - 1;
            T2 left = 0;
            T2 right = N - 1;
            do {
                for (T2 i = left; i < right; i++) {
                    if (mas[i] > mas[i + 1]) {
                        swap(mas[i], mas[i + 1]);
                        control = i;
                    }
                }
                right = control;
                for (T2 i = right; i > left; i--) {
                    if (mas[i] < mas[i - 1]) {
                        swap(mas[i], mas[i - 1]);
                        control = i;
                    }
                }
                left = control;
            } while (left < right);
        }
//------------------------------------------------------------------------------------------------------------
        /** \brief Сортировка вставками - Элементы входной последовательности просматриваются по одному, и
         * каждый новый поступивший элемент размещается в подходящее место среди ранее упорядоченных
         * элементов
         * \param mas массив
         * \param N размер массива
         * В худшем случае: О(n^2)
         * В лучшем случае: О(1)
         * В среднем: О(n^2)
         * */
        template<typename T1, typename T2>
        void Insertion (T1 *mas, const T2 N) {
            T2 i;
            T1 buffer;
            for (T2 j = 1; j < N; j++) {
                buffer = mas[j];
                i = j - 1;
                while (i >= 0 && mas[i] > buffer) {
                    mas[i + 1] = mas[i];
                    mas[i] = buffer;
                    i--;
                }

            }
        }
//------------------------------------------------------------------------------------------------------------
        /** \brief Гномья сортировка - Гибрид сортировок вставками и пузырьком
         * \param mas массив
         * \param N размер массива
         * В худшем случае: О(n^2)
         * В лучшем случае: О(1)
         * В среднем: О(n^2)
         * */
        template<typename T1, typename T2>
        void Gnome (T1 *mas, const T2 N) {
            T2 i = 1;
            T2 j = 2;
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
//------------------------------------------------------------------------------------------------------------
        /** \brief Сортировка слиянием - Рекурсивно сортирует половины массива, а затем комбинирует их в один
         * \param mas массив
         * \param N размер массива
         * В худшем случае: O(n*log(n))
         * В лучшем случае: О(n)
         * В среднем: O(n*log(n))
         * */
        template<typename T1, typename T2>
        void Merge(T1 *mas, const T2 N) {
            if (N > 1) {
                const T2 left_size = N / 2;
                const T2 right_size = N - left_size;

                Merge(&mas[0], left_size);
                Merge(&mas[left_size], right_size);

                T1 lidx = 0, ridx = left_size, idx = 0;
                static T1 *aux = new T1[N];

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
//------------------------------------------------------------------------------------------------------------
        /** \brief Сортировка с помощью двоичного дерева - На основе исходных данных строится двоичное дерево
         * поиска, в котором последовательно собираются минимальные значения
         * \param mas массив
         * \param N размер массива
         * В худшем случае: O(n^2)
         * В лучшем случае: О(n)
         * В среднем: O(n*log(n))
         * */
        template<typename T1, typename T2>
        void Tree(T1 *mas, const T2 N) {
            BinaryTree tree;
            for (T2 i = 0; i < N; i++) {
                tree.insert(mas[i]);
            }
            tree.visit([](int visited_key) {
                ofstream fileout;
                fileout.open("tree.txt", std::ios::app);
                fileout << visited_key << " ";
                fileout.close();
            });
            // Это костыль за который мне очень стыдно. Человек который это читает - не читай!
            // Его надо переделать. Но мне было лень. И красиво не очень выходило. оставил как есть
            ifstream fin;
            fin.open("tree.txt");
            if (!fin.is_open()) {
                return;
            }
            char str[255]; char sym = ' '; size_t counter = 0; T2 i = 0;
            do {
                char ch = fin.get();
                if (ch == sym ) {
                    mas[i] = atoi(str);
                    i++;
                    str[0] = '\0';
                    counter = 0;
                }
                str[counter++] = ch;
            } while( !fin.eof() );
            fin.close();
            remove("tree.txt");
        }

    private:
        // класс, представляющий бинарное дерево - взят с википедии
        class BinaryTree {
        protected:
            // узел бинарного дерева
            struct BinaryTreeNode {
                shared_ptr<BinaryTreeNode> left, right; // левое и правое поддерево
                double key; // ключ
            };

            shared_ptr<BinaryTreeNode> m_root; // корень дерева
        protected:
            // рекурсивная процедура вставки ключа
            // cur_node - текущий узел дерева, с которым сравнивается вставляемый узел
            // node_to_insert - вставляемый узел
            void insert_recursive (const shared_ptr<BinaryTreeNode>& cur_node,
                                   const shared_ptr<BinaryTreeNode>& node_to_insert) {
                assert(cur_node != nullptr);
                // сравнение
                bool insertIsLess = node_to_insert->key < cur_node->key;
                if (insertIsLess) {
                    // вставка в левое поддерево
                    if (cur_node->left == nullptr) {
                        cur_node->left = node_to_insert;
                    } else {
                        insert_recursive(cur_node->left, node_to_insert);
                    }
                }
                else {
                    // вставка в правое поддерево
                    if (cur_node->right == nullptr) {
                        cur_node->right = node_to_insert;
                    } else {
                        insert_recursive(cur_node->right, node_to_insert);
                    }
                }
            }
        public:
            void insert (double key) {
                shared_ptr<BinaryTreeNode> node_to_insert(new BinaryTreeNode);
                node_to_insert->key = key;

                if(m_root == nullptr) {
                    m_root = node_to_insert;
                    return;
                }

                insert_recursive(m_root, node_to_insert);
            }

            public:
                typedef function <void(double key)> Visitor;

        protected:
            // рекурсивная процедура обхода дерева
            // cur_node - посещаемый в данный момент узел
            void visit_recursive (const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor) {
                assert(cur_node != nullptr);

                // сначала посещаем левое поддерево
                if(cur_node->left != nullptr)
                    visit_recursive(cur_node->left, visitor);

                // посещаем текущий элемент
                visitor(cur_node->key);

                // посещаем правое поддерево
                if(cur_node->right != nullptr)
                    visit_recursive(cur_node->right, visitor);
            }

        public:
            void visit(const Visitor& visitor) {
                if(m_root == nullptr)
                    return;
                visit_recursive(m_root, visitor);
            }
        };
    public:
//------------------------------------------------------------------------------------------------------------
        const static auto RUN = 32; /* Шаг в битах */

        /** \brief Сортировка Timsort - Гибрид сортировок вставками и слиянием. Основан на предположении,
         * что при решении практических задач входной массив зачастую состоит из отсортированных подмассивов
         * \param mas массив
         * \param N размер массива
         * В худшем случае: O(n*log(n))
         * В лучшем случае: О(1)
         * В среднем: O(n*log(n))
         * */
        template<typename T1, typename T2>
        void Tim(T1 *mas, const T2 N) {
            for (T2 i = 0; i < N; i+=RUN) {
                insertionSort(mas, i, min((i + RUN - 1), (N - 1)));
            }
            for (T2 size = RUN; size < N; size = 2*size) {
                for (T2 left = 0; left < N; left += 2*size) {
                    T2 mid = left + size - 1;
                    T2 right = min((left + 2*size - 1), (N-1));
                    if(mid < right) {
                        merge(mas, left, mid, right);
                    }
                }
            }
        }

    private:
        template<typename T1, typename T2>
        static void insertionSort(T1 *arr, T2 left, T2 right) {
            for (T2 i = left + 1; i <= right; i++) {
                T1 temp = arr[i];
                T2 j = i - 1;
                while (j >= left && arr[j] > temp) {
                    arr[j+1] = arr[j];
                    j--;
                }
                arr[j+1] = temp;
            }
        }

        template<typename T1, typename T2>
        static void merge(T1 *arr, T2 l, T2 m, T2 r) {
            T2 len1 = m - l + 1, len2 = r - m;
            T1 left[len1], right[len2];
            for (T2 i = 0; i < len1; i++) {
                left[i] = arr[l + i];
            }
            for (T2 i = 0; i < len2; i++) {
                right[i] = arr[m + 1 + i];
            }

            T2 i = 0;
            T2 j = 0;
            T2 k = l;
            while (i < len1 && j < len2) {
                if (left[i] <= right[j]){
                    arr[k] = left[i];
                    i++;
                } else {
                    arr[k] = right[j];
                    j++;
                }
                k++;
            }
            while (i < len1) {
                arr[k] = left[i];
                k++;
                i++;
            }
            while (j < len2) {
                arr[k] = right[j];
                k++;
                j++;
            }
        }
    public:
//============================================================================================================
/*                                Алгоритмы неустойчивой сортировки                                         */
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Selection (T1 *mas, const T2 N) {
        for (T2 i = 0; i < N; i++) {
            T2 min = i;
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
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Comb(T1 *mas, const T2 N) {
            double factor = 1.2473309;
            T2 step = N - 1;
            while (step >= 1) {
                for (T2 i = 0; i + step < N; i++) {
                    if (mas[i] > mas[i + step]) {
                        swap(mas[i], mas[i + step]);
                    }
                }
                step /= factor;
            }
        }
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Shell (T1 *mas, const T2 N) {
            for (T2 s = N / 2; s > 0; s /= 2) {
                for (T2 i = s; i < N; ++i) {
                    for (T2 j = i - s; (j >= 0) && (mas[j] > mas[j + s]); j -= s) {
                        swap(mas[j], mas[j + s]);
                    }
                }
            }
        }
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Heap(T1 *mas, const T2 N) {
            // Формируем нижний ряд пирамиды
            for (T2 i = (N / 2); i >= 0; i--)
                siftDown(mas, i, N - 1);
            // Просеиваем через пирамиду остальные элементы
            for (T2 i = N - 1; i >= 1; i--) {
                swap(mas[0], mas[i]);
                siftDown(mas, 0, i - 1);
            }
        }

    private:
        template<typename T1, typename T2>
        static void siftDown(T1 *numbers, T2 root, T2 bottom) {
            T2 maxChild; // индекс максимального потомка
            T2 done = 0; // флаг того, что куча сформирована
            // Пока не дошли до последнего ряда
            while ((root * 2 <= bottom) && (!done)) {
                if (root * 2 == bottom) {    // если мы в последнем ряду,
                    maxChild = root * 2;    // запоминаем левый потомок
                    // иначе запоминаем больший потомок из двух
                } else if (numbers[root * 2] > numbers[root * 2 + 1]) {
                    maxChild = root * 2;
                } else {
                    maxChild = root * 2 + 1;
                }
                // если элемент вершины меньше максимального потомка
                if (numbers[root] < numbers[maxChild]) {
                    swap(numbers[root], numbers[maxChild]);
                    root = maxChild;
                } else {
                    done = 1; // пирамида сформирована
                }
            }
        }
    public:
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Smooth(T1 *mas, const T2 N);
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Quick(T1 *mas, const T2 N) {
            T2 left = 0;
            T2 right = N - 1;
            T1 central_element = mas[N / 2];
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
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Intro(T1 *mas, const T2 N);
//------------------------------------------------------------------------------------------------------------
        template<typename T1, typename T2>
        void Stooge (T1 *mas, const T2 N) {
            Stooge(mas, 0, N);
        }

        template<typename T1, typename T2>
        void Stooge (T1 *mas, const T2 l, const T2 r) {
            if (l >= r) {
                return;
            }
            if (mas[l] > mas[r]) {
                swap(mas[l], mas[r]);
            }
            if (r - l + 1 > 2) {
                T2 t = (r - l + 1) / 3;
                Stooge(mas, l, r - t);
                Stooge(mas, l + t, r);
                Stooge(mas, l, r - t);
            }
        }
//============================================================================================================
/*                                Непрактичные алгоритмы сортировки                                         */
//------------------------------------------------------------------------------------------------------------
    } m;
};

using namespace stepan_sort;

/* Mетоды должны быть все статьические чтобы можно было комангду ниже сделать. */
//using ss = stepan_sort::StepanSort;

#endif  // PROJECT_INCLUDE_STEPANSORT_H_
