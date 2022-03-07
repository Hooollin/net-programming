#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/select.h>
#include <vector>

int main(){
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);  

  if(sockfd < 0){
    std::cout << errno << std::endl;
    return -1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(6981);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(-1 == bind(sockfd, (struct sockaddr*) &addr, sizeof(addr))){
    std::cout << errno << std::endl;
    return -1;
  }
  
  if(-1 == listen(sockfd, 10)){
    std::cout << errno << std::endl;
    return -1;
  }
  
  int maxfd = sockfd;

  fd_set rfds;

  std::vector<int> clientfds;

  while(true){
    FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);

    for(auto &fd : clientfds){
      FD_SET(fd, &rfds);
    }

    for(auto &clientfd : clientfds){
      FD_SET(clientfd, &rfds);
    }

    struct timeval tv{100000, 0};
    int retval;
    retval = select(maxfd + 1, &rfds, nullptr, nullptr, &tv);
    //std::cout << "retval: " << retval << std::endl;

    if(retval == -1){
      std::cout << errno << std::endl;
    }

    if(retval == 0){
      // do nothing
    }

    if(retval > 0){
      if(FD_ISSET(sockfd, &rfds)){
        socklen_t len = sizeof(addr);
        int clientfd = accept(sockfd, (struct sockaddr*)&addr, &len);
        clientfds.push_back(clientfd);
        maxfd = std::max(clientfd, maxfd);
      }
      for(int i = 0; i < clientfds.size(); ++i){
        if(FD_ISSET(clientfds[i], &rfds)){
          char buf[1024];
          size_t bytes_read = read(clientfds[i], buf, 1023);
          buf[bytes_read] = '\0';
          std::cout << buf;
        }
      }
    }
    //std::cout << "client size: " << clientfds.size() << std::endl;
  }
  

  return 0;
}
