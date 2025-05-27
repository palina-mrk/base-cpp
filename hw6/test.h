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


/* информация о контейнерах */
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


/* проверка всевозможных копирований */
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
















