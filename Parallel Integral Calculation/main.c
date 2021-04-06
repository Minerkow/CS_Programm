#include <stdio.h>
#include "ParseInfo.h"
#include "IntegralCalculator.h"
#include <time.h>
#include <limits.h>

double Func(double x) {
    return x;
}

long long int Read_Number_from_Text(const char* text) {
    char **endptr = calloc(1, sizeof(char*));
    long long int num = strtoll(text, endptr, 10);
    if (num < 0) {
        fprintf(stderr, "Less 0");
        exit(EXIT_FAILURE);
    }
    if (num == LONG_MAX) {
        fprintf(stderr, "Big number");
        exit(EXIT_FAILURE);
    }
    if (**endptr != '\0') {
        fprintf(stderr, "Wrong format");
        exit(EXIT_FAILURE);
    }
    return num;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: few arguments");
        return -1;
    }
    struct Integral_t integral = {.func = Func,
                                  .begin = 0,
                                  .end = 100000};
    double res = 0;
    double start = clock();
    long long int k = Read_Number_from_Text(argv[1]);
    IntegralCalculate(integral, k, &res);
    fprintf(stdout, "\n%f\n", res);
    printf("\ntime : %f", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
