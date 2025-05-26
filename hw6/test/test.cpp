#include "containers.h"

/* принимает указатель на существующий заполненный объект контейнера 
 * три индекса для удаления из контейнера
 * и три элемента для добавления в начало, середину и конец контейнера*/
template <typename T>
void func_for_test(IContainers<T>* obj, std::size_t del_ind[3], T add_elts[3]){
  std::cout << "container with " <<  obj->size() << " elts:\n"
    << obj
    << "size: " <<  obj->size() << '\n';

  obj->erase(del_ind[0]);
  obj->erase(del_ind[1]);
  obj->erase(del_ind[2]);
  std::cout << "erased elts with indexes "  
            << del_ind[0] << ", " 
            << del_ind[1] << ", " 
            << del_ind[2] << ":\n"
            << obj;

  obj->insert(add_elts[0],0);
  std::cout << "inserted "<< add_elts[0] << " to the beginning:\n"
            << obj;

  obj->insert(add_elts[1],obj->size()/2);
  std::cout << "inserted "<< add_elts[1] << " to the half:\n"
            << obj;

  obj->push_back(add_elts[2]);
  std::cout << "inserted "<< add_elts[2] << " to the end:\n"
            << obj;
}

int main(){
  std::size_t L = 5, M = 10, del_pos[] = {3, 5, 7};
  int arr[M], add_elts[] = {10, 20, 30};
  for(int i = 0; i < M; ++i)
    arr[i] = i;

  /* создаём массив из L контейнеров*/
  IContainers<int>* cons[L];
  for(int i = 0 ; i < L; ++i)
    cons[i] = nullptr;

  /* инициализируем первый контейнер типом список */
  cons[0] = new SeqContainer<int>{arr, 10};
  func_for_test(cons[0], del_pos, add_elts);

  cons[1] = new ListContainer<int>{arr,10};
  func_for_test(cons[1], del_pos, add_elts);

  cons[2] = new ListContainer<int>{};
  std::cout << cons[2];
  cons[2]->push_back(5);
  std::cout << cons[2];
  cons[2]->push_back(4);
  std::cout << cons[2];
  cons[2]->erase(0);
  std::cout << cons[2];
  cons[2]->erase(1);
  std::cout << cons[2];
  cons[2]->insert(1,1);
  std::cout << cons[2];
  cons[2]->insert(100,1);
  std::cout << cons[2] << (*cons[2])[0];

  for(int i = 0; i < L; ++i)
    if(cons[i])
      delete cons[i];
  return 0;
}
