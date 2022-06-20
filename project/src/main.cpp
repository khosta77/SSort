#include "../include/testsort.h"
#include <ctime>

int main(int argc, char **argv) {
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << dt;
    testsort tstsrt;
    dt = ctime(&now);
    cout << dt;
    return 0;
}

