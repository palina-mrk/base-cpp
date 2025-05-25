#include "containers.h"

int main(){
  int a[]={0,1,2,3};
  SeqContainer<int> list{a,4};
  for(int i = 4; i < 10; ++i)
    list.push_back(i);

  std::cout << list;
  return 0;
}
