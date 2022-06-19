import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math

START = 0
STEP = 500
SIZE = 1000000

def plt_all_sort(df):
    plt.figure(figsize=(15,10))
    plt.plot(df);
    plt.xlim(0)
    plt.ylim(0)
    plt.ylabel('Время')
    plt.xlabel('Колличество элементов, x1000 [ед]')
    plt.grid()
    plt.legend(df.head(), prop={'size': 17})
    # plt.show()
    plt.savefig('Analysis.png')

def plt_one_sort(df, name):
    x = np.linspace(START, SIZE, num=int(SIZE/STEP))
    y_n2 = x ** 2
    y_log = x * np.log(x)
    #
    plt.figure(figsize=(15,10))
    plt.plot(df, "b", label=name);
    plt.plot(x, y_n2, "g--", label=r'n^2')
    plt.plot(x, y_log, "g-.", label=r'n*log(n)')
    plt.xlim(0)
    plt.ylim(0)
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