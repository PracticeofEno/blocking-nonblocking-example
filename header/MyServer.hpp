#ifndef MYSERVER_HPP
#define MYSERVER_HPP

#define EPOLL_SIZE 50 // 실제론 사용되지 않음
#define BUF_SIZE 10

#include "../header/total.hpp"
class MyServer
{

public:
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int server_sock, client_sock;
    socklen_t addr_sz;
    std::string recieveString;

    struct epoll_event *ep_events_buf; // 변화를 담을 버퍼의 주소!
    struct epoll_event userevent;      // 등록하기 위한 변수!
    int epfd, event_cnt;

    MyServer(int port);

    ~MyServer();

    void start();

private:
    std::string ReadSocket(int socket, int bufSize);
};
#endif