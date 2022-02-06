#include "MyServer.hpp"

MyServer::MyServer(int port)
{
    memset(&serv_addr, 0x00, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if ((server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        std::cout << "socket create error" << std::endl;
    }

    int flags = fcntl(server_sock, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(server_sock, F_SETFL, flags) < 0)
    {
        std::cout << "server_fd fcntl() error" << std::endl;
        close(server_sock);
        _exit(1);
    }

    int on = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        std::cout << "socket option set error" << std::endl;
        close(server_sock);
        _exit(1);
    }

    if (bind(server_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "bind error" << std::endl;
        close(server_sock);
        _exit(1);
    }

    if (listen(server_sock, 5) < 0) // 대기큐 5라고 써서 대기큐가 모지랄수도(?)
    {
        std::cout << "listen error" << std::endl;
        close(server_sock);
        _exit(1);
    }

    epfd = epoll_create(EPOLL_SIZE);                         // epoll 인스턴스 생성
    ep_events_buf = new epoll_event[EPOLL_SIZE];             // 버퍼 동적할당
    userevent.events = EPOLLIN | EPOLLET;                    // 수신관련한 이벤트를 보고싶다.
    userevent.data.fd = server_sock;                         // 서버 fd를 등록할 것이다.
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_sock, &userevent); // ADD로 등록, 서버fd, 원하는 이벤트
}
MyServer::~MyServer()
{

}

std::string MyServer::ReadSocket(int socket, int bufSize)
{
    std::string tmp;
    char buf[bufSize];
    int strLen;

    while (true)
    {
        strLen = read(socket, buf, bufSize);
        if (strLen < 0)    
        {
            if (errno == EAGAIN)
                break;
        }
        else if (strLen == 0)
        {
            std::cout << "all data receive" << std::endl;
            break;
        }
        else
        {
            tmp.append(buf, strLen);
        }
    }
    return tmp;
}

void MyServer::start()
{
    while (1)
    {
        // 무한 대기하며 epfd중에 변화가 있는 fd 확인. 확인 후 event 버퍼에 넣음.
        event_cnt = epoll_wait(epfd, ep_events_buf, EPOLL_SIZE, -1);

        if (event_cnt == -1)
        {
            // puts("wait() error!\n");
            std::cout << "wait() error!" << std::endl;
            break;
        }

        // 확인된 변화의 갯수만큼 for문
        for (int i = 0; i < event_cnt; i++)
        {
            // 만약 이벤트가 생겼고 그 fd가 서버라면 -> 연결요청임!
            if (ep_events_buf[i].data.fd == server_sock)
            {
                addr_sz = sizeof(clnt_addr);
                client_sock = accept(server_sock, (struct sockaddr *)&clnt_addr, &addr_sz); // 이때 accept!!

                int flags = fcntl(client_sock, F_GETFL);
                flags |= O_NONBLOCK;
                if (fcntl(client_sock, F_SETFL, flags) < 0)
                {
                    std::cout << "server_fd fcntl() error" << std::endl;
                    close(client_sock);
                    _exit(1);
                }

                // 클라이언트의 fd를 등록해주는 과정
                userevent.events = EPOLLIN | EPOLLET;
                userevent.data.fd = client_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_sock, &userevent);
                std::cout << "connected client : " << client_sock << std::endl;
            }
            // 서버가 아니라면 -> 클라이언트의 변화
            else
            {
                std::cout << ReadSocket(ep_events_buf[i].data.fd, BUF_SIZE) << std::endl;
                //ReadSocket() 하면 ET신호가 발생하면 텅빌때까지 쭈욱 읽음 (데이터를 receive 완료함)
            }
        }
    }
}