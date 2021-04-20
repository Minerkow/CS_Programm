#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <assert.h>

enum {BROADCAST_PORT = 8333, SIZE_BUFF = 1024};

void GetCurrentIpAddr(char* buff);
void SendBroadCast_();
void ListenBroadCast_();