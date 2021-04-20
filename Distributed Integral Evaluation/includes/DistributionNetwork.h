#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>

enum {BROADCAST_PORT = 8333, TCP_PORT = 8334, SIZE_BUFF = 1024, BACKLOG_LEN = 10};

void GetCurrentIpAddr(char* buff);
void SendBroadCast_();
void ListenBroadCast_();