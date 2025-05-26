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

/* тестирует добавление и удаление в очень короткий список
 * принимает желательно, пустой список */
template <typename T>
void test_very_short(IContainers<T>* obj, T elts[3]) {
  std::cout << "Initial container: \n" << obj;
  obj->push_back(elts[0]);
  obj->push_back(elts[1]);
  std::cout << "Push back 2 elements:\n " << obj;
  std::cout << "Erasing all + attemption to erase out of container:\n";
  obj->erase(0);
  std::cout << "After erasing first:\n" << obj;
  obj->erase(1);
  obj->erase(0);
  obj->erase(0);
  std::cout << "After erasing:\n" << obj;
  std::cout << "Now one attemption to insert out of arr + correct insert three: \n";
  obj->insert(elts[3],1);
  obj->insert(elts[3],0);
  obj->insert(elts[2],1);
  obj->insert(elts[1],1);
  std::cout << obj;
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
  std::cout << "****testing of sequence container***\n";
  func_for_test(cons[0], del_pos, add_elts);

  cons[1] = new ListContainer<int>{arr,10};
  std::cout << "****testing of list container****\n";
  func_for_test(cons[1], del_pos, add_elts);


  std::cout << "****testing of very short list container***\n";
  cons[2] = new ListContainer<int>{};
  test_very_short(cons[2],add_elts);

  cons[3] = new SeqContainer<int>((SeqContainer<int>&)*cons[0]);
  std::cout << "***test of  copies***\n" 
            << "copy constructor sequence:\n"
            << cons[3];

  cons[4] = new SeqContainer<int>{add_elts,3};
  ((SeqContainer<int>&)*cons[3]) = ((SeqContainer<int>&)*cons[4]);
  std::cout << "operator = :\n"
            << cons[3];

  cons[5] = new ListContainer<int>((ListContainer<int>&)*cons[1]);
  std::cout << "copy constructor list:\n"
            << cons[1];

  ((ListContainer<int>&)*cons[5]) = ((ListContainer<int>&)*cons[2]);
  std::cout << "operator = :\n"
            << cons[5];

  for(int i = 0; i < L; ++i)
    if(cons[i])
      delete cons[i];
  return 0;
}
