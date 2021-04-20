#include <unistd.h>
#include "DistributionNetwork.h"

struct ComputerInfo_t {
    size_t numCores;
    size_t numThreadsPerCore;
};

struct Connection_t {
    struct ComputerInfo_t computerInfo;
    double res;
};

//-------------------------------------------Static functions---------------------------------------
static void FindComputers_(size_t numExpectedComputers);
static int OpenBroadCastSocket_();

static void FindComputers_(size_t numExpectedComputers) {

}

void SendBroadCast_() {
    int socketBC = OpenBroadCastSocket_();

//    char curIp[SIZE_BUFF] = {};
//    GetCurrentIpAddr(curIp);

    struct sockaddr_in broadcastAddr = {.sin_family = AF_INET,
                                        .sin_addr.s_addr = htonl(INADDR_BROADCAST),
                                        .sin_port = htons(BROADCAST_PORT)};

    if (sendto(socketBC, "IP_FOUND", strlen("IP_FOUND"), 0, (struct sockaddr*) &broadcastAddr, sizeof (broadcastAddr)) < 0) {
        perror("sendto");
        return;
    }
    close(socketBC);
}

void ListenBroadCast_() {
    int socketRc = socket(AF_INET, SOCK_DGRAM, 0);

    fd_set readFd;
    char buffer[SIZE_BUFF] = {};
    struct sockaddr_in serverAddr;
    struct sockaddr_in socketAddr = {.sin_family = AF_INET,
                                     .sin_port = htons(BROADCAST_PORT),
                                     .sin_addr.s_addr = htonl(INADDR_ANY)};

    socklen_t addrLen = sizeof(struct sockaddr_in);

    FD_ZERO(&readFd);
    FD_SET(socketRc, &readFd);

    if (select(socketRc + 1, &readFd, NULL, NULL, NULL) < 0) {
        perror("select");
        return;
    }
    if (bind(socketRc, (struct sockaddr*) &socketAddr, addrLen) < 0) {
        perror("bind");
        return;
    }

    if (FD_ISSET(socketRc, &readFd)) {
        fprintf(stderr, "kek\n");
        if (recvfrom(socketRc, buffer, SIZE_BUFF, 0, (struct sockaddr*) &serverAddr, &addrLen) < 0) {
            perror("recvfrom");
            return;
        }
        fprintf(stderr, "\tfound server IP is %s, Port is %d\n", inet_ntoa(serverAddr.sin_addr), htons(serverAddr.sin_port));
    }
}

static int OpenBroadCastSocket_() {
    int socketBC = socket(PF_INET, SOCK_DGRAM, 0);
    if (socketBC < 0) {
        perror("socket");
        return -1;
    }

    int options = 1;
    if(setsockopt(socketBC, SOL_SOCKET, SO_BROADCAST, &options, sizeof(options)) < 0) {
        perror("sotsockopt");
        return -1;
    }

    return socketBC;
}

void GetCurrentIpAddr(char* buff) {
    struct ifaddrs *addrs;
    getifaddrs(&addrs);
    struct ifaddrs *tmp = addrs;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET && strcmp(tmp->ifa_name, "lo") != 0)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            sprintf( buff, "%s", inet_ntoa(pAddr->sin_addr));
        }

        tmp = tmp->ifa_next;
    }
    freeifaddrs(addrs);
}


