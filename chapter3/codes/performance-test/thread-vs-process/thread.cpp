#include <thread>
#include <ctime>
constexpr int times = 1000;

void f(){
  // do nothing
}

int main(){
  clock_t start, end;

  start = clock();
  for(int i = 0; i < times; ++i){
    std::thread t(f);
    t.join();
  }
  end = clock();

  printf("%.4f s\n", (double)(end - start) / CLOCKS_PER_SEC);
  return 0;
}
