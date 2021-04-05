#pragma once

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

struct CoreInfo_t;

struct CoreInfo_t* GetCoresInfo(size_t* size);
void FreeCoresInfo(struct CoreInfo_t* coreInfo, size_t size);
void PrintCoresInfo(const struct CoreInfo_t* coreInfo, size_t size);
