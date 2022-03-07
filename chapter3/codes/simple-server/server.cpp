#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

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
  
  socklen_t len = sizeof(addr);
  int client = accept(sockfd, (struct sockaddr*)&addr, &len);

  if(client < 0){
    std::cout << errno << std::endl;
    return -1;
  }

  char buf[1024];
  while(true){
    size_t bytesRead = read(client, buf, 1023);
    buf[bytesRead] = '\0';
    std::cout << buf;
    write(client, buf, bytesRead);
  }

  return 0;
}
