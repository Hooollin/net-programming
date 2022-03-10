#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>

const int times = 1000;

int main(){
  clock_t start, end;

  start = clock();
  for(int i = 0; i < times; ++i){
    int cpid;
    cpid = fork();

    if(cpid == 0){
      return 0;
    }else{
      wait(NULL);
    }
  } 
  end = clock();

  printf("%.f s\n", (double)(end - start) / CLOCKS_PER_SEC);
  return 0;
}
