#include "containers.h"
#include "test.h"

/* информация о контейнерах 
template <class C>
void info(C* c, const char* name){
  if(!c->size())
    std::cout << name << ": container is empty" 
            << "\n       container's address: " << (int*)c << '\n';
  else
    std::cout << name << ": 1st el-t address: " << &(*c)[0]
            << "\n      container's address: " << (int*)c  
            << " elements: " << c;
}

template <class C>
void test_copying(const char* name, C* from[2]){
  std::cout << "\n***test of copy constructors :"
            << name << " containers ***\n\n";
  C* cont[3];
  cont[0] = new C{(C&)*from[0]};
  info(from[0], "source");
  info(cont[0], "result");

  std::cout << '\n';
  cont[1] = new C{(C&&)*cont[0]};
  info(cont[0], "source");
  info(cont[1], "result");
  cont[0] = nullptr;

  std::cout << "\n***test of copy operators :"
            << name << " containers ***\n";
  info(cont[1],"\ndestination before copying");
  *cont[1] = ((C&)(*from[1]));
  info(from[1], "source");
  info(cont[1], "result");

  cont [2] = new C{};
  info(cont[2],"\ndestination before copying");
  *cont[2] = ((C&&)(*cont[1]));
  info(cont[1], "source");
  info(cont[2], "result");
  cont[2] = nullptr;

  for(std::size_t i = 0; i < 3; ++i)
    if(cont[i])
      delete cont[i];
}
*/

int main(){
  std::size_t L = 5, M = 10, del_pos[] = {3, 5, 7};
  int arr[M], add_elts[] = {10, 20, 30};
  for(int i = 0; i < M; ++i)
    arr[i] = i;

  /* создаём массив из L контейнеров*/
  IContainers<int>* cons[L];
  for(int i = 0 ; i < L; ++i){
    cons[i] = nullptr;
  }

  /* инициализируем первый контейнер типом список */
  cons[0] = new SeqContainer<int>{arr, 10};
  std::cout << "\n****testing of sequence container***\n";
  func_for_test(cons[0], del_pos, add_elts);

  cons[2] = new ListContainer<int>{arr,10};
  std::cout << "\n****testing of list container****\n";
  func_for_test(cons[2], del_pos, add_elts);

  std::cout << "\n****testing of very short sequence container***\n";
  cons[1] = new SeqContainer<int>{};
  test_very_short(cons[1],add_elts);

  std::cout << "\n****testing of very short list container***\n";
  cons[3] = new ListContainer<int>{};
  test_very_short(cons[3],add_elts);

  test_copying("sequense",(SeqContainer<int>**)cons);
  test_copying("list",(ListContainer<int>**)(cons + 2));

  for(int i = 0; i < L; ++i)
    if(cons[i])
      delete cons[i];

  return 0;
}
