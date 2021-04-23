#include <stdio.h>
#include <string.h>
#include "DistributionNetwork.h"
#include "ParseInfo.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Input Error");
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        StartSideNode();
    } else {
        if (argc != 4) {
            fprintf(stderr, "Input Error");
            return 0;
        }
        double res = 0;
        struct Integral_t integral = {.begin = 0,
                                      .end = 10,
                                      .func = func};

        StartMainNode(Read_Number_from_Text(argv[3]), Read_Number_from_Text(argv[2]), integral, &res);
        printf("\n[  %f  ]\n", res);
    }
}
