#include "DistributionNetwork.h"
#include "ParseInfo.h"
#include "IntegralCalculator.h"


struct ComputerInfo_t {
    size_t numCores;
    size_t numCPU;
};

struct Connection_t {
    int socket;
    struct ComputerInfo_t computerInfo;
};

struct CalculateInfo_t {
    struct Integral_t integral;
    size_t numUsedThreads;
};

//-------------------------------------------Static Functions---------------------------------------
static void FindAndConnectComputers_(struct Connection_t* connections, size_t numComputers);
static int OpenBroadCastSocket_();
static void SendBroadCast_();
static int ListenBroadCast_(struct sockaddr_in* serverAddr);
//------------------------------------------------Debug Functions------------------------------------------
static void PrintConnections_(struct Connection_t* connection, size_t numConnections);


//-------------------------------------------API----------------------------------------------------

void StartMainNode(size_t numThreads, size_t numComputers) {
    struct Connection_t* connections = calloc(numComputers, sizeof(struct Connection_t));
    FindAndConnectComputers_(connections, numComputers);
    PrintConnections_(connections, numComputers);


}

void StartSideNode() {
    struct sockaddr_in serverAddr;
    ListenBroadCast_(&serverAddr);

    fprintf(stderr, "found server IP is %s, Port is %d\n", inet_ntoa(serverAddr.sin_addr),
            htons(serverAddr.sin_port));

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t socklen = sizeof(struct sockaddr_in);

    if (connect(socketServer, (const struct sockaddr*) &serverAddr, socklen) < 0) {
        perror("connect");
        return; //TODO: ERROR
    }

    struct ComputerInfo_t computerInfo = {};
    struct CoreInfo_t* coresInfo = GetCoresInfo(&computerInfo);

    if (send(socketServer, &computerInfo, sizeof(computerInfo), 0) < 0) {
        perror("send");
        return; //TODO: ERROR
    }

    struct CalculateInfo_t calculateInfo = {};
    if (recv(socketServer, &calculateInfo, sizeof(calculateInfo), 0) < 0) {
        perror("recv");
        return; //TODO: ERROR
    }

    double res = 0.0;
    IntegralCalculate(coresInfo, &computerInfo, calculateInfo.integral, calculateInfo.numUsedThreads, &res);

    if (send(socketServer, &res, sizeof(res), 0) < 0) {
        perror("send");
        return; //TODO: ERROR
    }
}

//-------------------------------------------Static Functions---------------------------------------
static void FindAndConnectComputers_(struct Connection_t* connections, size_t numComputers) {
    assert(connections);

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr = {.sin_family = AF_INET,
            .sin_port = htons(TCP_PORT),
            .sin_addr.s_addr = htonl(INADDR_ANY)};
    socklen_t socklen = sizeof(struct sockaddr_in);

    if(bind(socketServer, (const struct sockaddr *) &serverAddr, socklen) < 0) {
        perror("bind");
        return; //TODO: ERROR
    }

    SendBroadCast_();

    if(listen(socketServer, numComputers + 1) < 0) {
        perror("listen");
        return; //TODO: ERROR
    }

    for (int itSockets = 0 ; itSockets < numComputers; ++itSockets) {
        int clientSock = accept(socketServer, (struct sockaddr *) &serverAddr, &socklen);
        if (clientSock < 0) {
            perror ("accept");
            return; //TODO: ERROR
        }
        connections[itSockets].socket = clientSock;
        if (recv(clientSock, &connections->computerInfo, sizeof(struct ComputerInfo_t), 0) < 0) {
            perror("recv");
            return; //TODO: ERROR
        }
    }

    for (int itSockets = 0; itSockets < numComputers; ++itSockets) {
        close(connections[itSockets].socket);
    }
}

static void SendBroadCast_() {
    int socketBC = OpenBroadCastSocket_();

    struct sockaddr_in broadcastAddr = {.sin_family = AF_INET,
                                        .sin_addr.s_addr = htonl(INADDR_BROADCAST),
                                        .sin_port = htons(BROADCAST_PORT)};

    if (sendto(socketBC, "IP_FOUND", strlen("IP_FOUND"), 0, (struct sockaddr*) &broadcastAddr, sizeof (broadcastAddr)) < 0) {
        perror("sendto");
        return;
    }
    close(socketBC);
}

static int ListenBroadCast_(struct sockaddr_in* serverAddr) {
    int socketRc = socket(AF_INET, SOCK_DGRAM, 0);

    char buffer[SIZE_BUFF] = {};
    struct sockaddr_in socketAddr = {.sin_family = AF_INET,
                                     .sin_port = htons(BROADCAST_PORT),
                                     .sin_addr.s_addr = htonl(INADDR_ANY)};

    socklen_t addrLen = sizeof(struct sockaddr_in);

    if (bind(socketRc, (struct sockaddr*) &socketAddr, addrLen) < 0) {
        perror("bind");
        return -1;
    }
    if (recvfrom(socketRc, buffer, SIZE_BUFF, 0, (struct sockaddr *) serverAddr, &addrLen) < 0) {
        perror("recvfrom");
        return -1;
    }
    serverAddr->sin_port = htons(TCP_PORT);
    fprintf(stderr, "found server IP is %s, Port is %d\n", inet_ntoa(serverAddr->sin_addr),
            htons(serverAddr->sin_port));
    return 1;
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

//------------------------------------------------Debug Functions------------------------------------------
static void PrintConnections_(struct Connection_t* connection, size_t numConnections) {
    assert(connection);
    for (int i = 0; i < numConnections; ++i) {
        printf("Comp%d: numCores - %zu, numCPUByCore - %zu, res - %f\n",
               i, connection[i].computerInfo.numCores, connection[i].computerInfo.numCores, connection[i].res);
    }
}
