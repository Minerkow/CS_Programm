#include <stdio.h>
#include "ParseInfo.h"
#include "IntegralCalculator.h"

double Func(double x) {
    return x;
}

int main() {
    //size_t size = 0;
    //struct CoreInfo_t* coreInfo = GetCoresInfo(&size);
    //fprintf(stderr, "\n%p\n", coreInfo);
    //PrintCoresInfo(coreInfo, size);
    struct Integral_t integral = {.func = Func,
                                  .begin = 0,
                                  .end = 1};
    double res = 0;
    IntegralCalculate(integral, 1, &res);
    fprintf(stdout, "\n%f\n", res);
    return 0;
}
