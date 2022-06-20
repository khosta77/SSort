import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

START = 0  # Начальное значение массива
STEP = 500  # Шаг массива
SIZE = 1_000_000  # максимальная длина массива
TIME = 1_000_000  # Время выходы
MAX_SIZE = int(SIZE/STEP)/5  # Максимальная длина ОХ

def plt_all_sort(df):
    """
    Все сотрировки наносит на один график
    :param df: Данные
    :return: График со всеми сортировками
    """
    plt.figure(figsize=(15,10))
    plt.plot(df);
    plt.xlim(0, MAX_SIZE)
    plt.ylim(0, TIME)
    plt.ylabel('Время')
    plt.xlabel('Колличество элементов, x1000 [ед]')
    plt.grid()
    plt.legend(df.head(), prop={'size': 17})
    plt.savefig('Analysis.png')

def plt_one_sort(df, name):
    """
    Функция строит график каждой сортировки отдельно и дополнительно поверх нагладывает идеальзированные
     значения
    :param df: Данные
    :param name: Имя графика
    :return: График одной сортировки с идельными, не идеальными и средними значениями
    """
    x = np.linspace(START, SIZE, num=int(SIZE/STEP))
    y_n2 = x ** 2
    y_log = x * np.log(x)
    plt.figure(figsize=(15,10))
    plt.plot(df, "b", label=name);
    plt.plot(x, y_n2, "g--", label=r'n^2')
    plt.plot(x, y_log, "g-.", label=r'n*log(n)')
    plt.xlim(0, MAX_SIZE)
    plt.ylim(0, TIME)
    plt.title(name)
    plt.ylabel('Время, мкс')
    plt.xlabel('Колличество элементов, x1000 [ед]')
    plt.grid()
    plt.legend(prop={'size': 17})
    # plt.show()
    plt.savefig(name+'Sort.png')

def main():
    df = pd.read_csv('Test_Sort.csv', sep=';')
    plt_all_sort(df)
    for i in range(df.shape[1]):
        plt_one_sort(df[str(df.columns[i])], str(df.columns[i]))

if __name__ == "__main__":
    main()