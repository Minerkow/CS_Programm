#pragma once

#define _GNU_SOURCE

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>


#include "IntegralCalculator.h"
#include "ParseInfo.h"


enum {BROADCAST_PORT = 8337, TCP_PORT = 8338, SIZE_BUFF = 1024, BACKLOG_LEN = 10};

void StartSideNode();
void StartMainNode(size_t numThreads, size_t numComputers, struct Integral_t integral, double* res);