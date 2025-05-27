/* контейнер с последовательным расположением в памяти - реализация */
template <typename T>
void SeqContainer<T>::resize(std::size_t new_size) {
      if(!new_size){
        Err::arr_siz();
        return;
      }
      T* tmp_first = new T[new_size];
      if(!tmp_first)
        Err::mem_all();
      if(N > new_size)
        N = new_size;
      for(std::size_t i = 0; i < N; ++i)
        tmp_first[i] = real_first[i];
      delete []real_first;
      real_first = tmp_first;
      tmp_first = nullptr;
      real_size = new_size;
    }
    
template <typename T>
SeqContainer<T>::~SeqContainer() {
      delete []real_first;
      real_first = nullptr;
      N = 0;
      real_size = 0;
    }
    

template <typename T>
SeqContainer<T>::SeqContainer() {
      N = 0;
      real_size = 8;
      real_first = new T[real_size];
      if(!real_first)
        Err::mem_all();
    }

template <typename T>
SeqContainer<T>::SeqContainer(const T* arr, std::size_t len) {
      real_size = (len > 4 ? 2*len : 8);
      real_first = new T[real_size];
      if(!real_first)
        Err::mem_all();
      N = len;
      for(int i = 0; i < N; ++i)
        real_first[i] = arr[i];
    }

template <typename T>
SeqContainer<T>::SeqContainer(const SeqContainer<T>& cont) {
      std::cout << "SeqContainer(const SeqContainer<T>& cont):\n" ;
      real_size = (cont.N < 4 ? 8 : 2*cont.N);
      N = cont.N;
      real_first = new T[real_size];
      for(int i = 0; i < N; ++i)
        real_first[i] = cont.real_first[i];
    }

template <typename T>
SeqContainer<T>::SeqContainer(SeqContainer<T>&& cont) {
      std::cout << "SeqContainer(SeqContainer<T>&& cont):\n";
      real_size = cont.real_size;
      N = cont.N;
      real_first = cont.real_first;
    }

template <typename T>
SeqContainer<T>& SeqContainer<T>::operator=(const SeqContainer<T>& cont){
      std::cout << "SeqContainer& operator=(const SeqContainer<T>& cont):\n";
      if(real_size < cont.N)
        resize(cont.N < 4 ? 8 : 2*cont.N);
      N = cont.N;
      for(int i = 0; i < N; ++i)
        real_first[i] = cont.real_first[i];
      return *this;
    }

template <typename T>
SeqContainer<T>& SeqContainer<T>::operator=(SeqContainer<T>&& cont) {
      std::cout << "SeqContainer& operator=(SeqContainer<T>&& cont):\n";
      real_size = cont.real_size;
      N = cont.N;
      delete[] real_first;
      real_first = cont. real_first;
      return *this;
    }

template <typename T>
std::size_t SeqContainer<T>::size() {return N; }

template <typename T>
void SeqContainer<T>::push_back(const T& obj) {
      if(N == real_size)
        resize(2*N);
      real_first[N] = obj;
      ++N;
    }

template <typename T>
void SeqContainer<T>::insert(const T& obj, std::size_t ind) {
      if(ind > N || ind < 0){
        Err::indx();
        return;
      }
      if(N == real_size)
        resize(2*N);
      for(int j = N; j > ind; --j)
        real_first[j] = real_first[j - 1];
      real_first[ind] = obj;
      ++N;
    }

template <typename T>
void SeqContainer<T>::erase(std::size_t ind)   {
      if(ind >= N || ind < 0){
        Err::indx();
        return;
      }
      --N;
      for(int j = ind; j < N; ++j)
        real_first[j] = real_first[j + 1];
    }

template <typename T>
T& SeqContainer<T>::operator[](std::size_t ind){
      if(ind >= N || ind < 0){
        Err::indx();
        return *real_first;
      }
      return real_first[ind];
    }


template <typename T>
std::ostream& operator<<(std::ostream& stream, IContainers<T>& cont){
      std::size_t N = cont.size();
      if(!N)
        stream << "Empty container!\n";
      else{
        for(int i = 0; i < N; ++i)
          stream << cont[i] << ' ';
        stream <<'\n';
      }
      return stream;
   }

template <typename T>
std::ostream& operator<<(std::ostream& stream, IContainers<T>* cont){
      std::size_t N = cont->size();
      if(!N)
        stream << "Empty container!\n";
      else{
        for(int i = 0; i < N; ++i)
          stream << (*cont)[i] << ' ';
        stream <<'\n';
      }
      return stream;
   }


/* списковый контейнер в одну сторону - реализация */
template <typename T>
ListContainer<T>::~ListContainer(){
      while (top) {
        tail = top->next;
        delete top;
        top = tail;
      }
      N = 0;
    };
 
template <typename T>
ListContainer<T>::ListContainer(): N{0}, top{nullptr}, tail{nullptr} {}

template <typename T>
ListContainer<T>::ListContainer(const T* arr, std::size_t len){
      if(len <= 0){
        Err::arr_siz();
        N = 0;
        top = nullptr;
        tail = nullptr;
        return;
      }
      top = new Node<T>;
      tail = top;
      for(std::size_t i = 0; i < len - 1; ++i){
        tail->data = arr[i];
        tail->next = new Node<T>;
        tail = tail->next;
      }
      tail->data = arr[len - 1];
      tail->next = nullptr;
      N = len;
    }

template <typename T>
ListContainer<T>::ListContainer(const ListContainer<T>& cont){
      std::cout << "ListContainer(const ListContainer<T>& cont):\n";
      N = cont.N;
      if(!N){
        tail = nullptr;
        top  = nullptr;
        return;
      }
      top = new Node<T>;
      tail = top;
      Node<T>* tmp = cont.top;
      while(tmp->next){
        tail->data = tmp->data;
        tail->next = new Node<T>;
        tail = tail->next;
        tmp = tmp->next;
      }
      tail->data = tmp->data;
      tail->next = nullptr;
    }

template <typename T>
ListContainer<T>::ListContainer(ListContainer<T>&& cont){
      std::cout << "ListContainer(ListContainer<T>&& cont):\n";
      N = cont.N;
      top = cont.top;
      tail = cont.tail;
    }

template <typename T>
ListContainer<T>& ListContainer<T>::operator=(const ListContainer<T>& cont){
      std::cout << "ListContainer& operator=(const ListContainer<T>& cont):\n";
      while (top) {
        tail = top->next;
        delete top;
        top = tail;
      }
      N = cont.N;
      if(!N){
        tail = nullptr;
        top  = nullptr;
        return *this;
      }
      top = new Node<T>;
      tail = top;
      Node<T>* tmp = cont.top;
      while(tmp->next){
        tail->data = tmp->data;
        tail->next = new Node<T>;
        tail = tail->next;
        tmp = tmp->next;
      }
      tail->data = tmp->data;
      tail->next = nullptr;
      return *this;
    }

template <typename T>
ListContainer<T>& ListContainer<T>::operator=(ListContainer<T>&& cont){
      std::cout << "ListContainer& operator=(ListContainer<T>&& cont):\n";
      while (top) {
        tail = top->next;
        delete top;
        top = tail;
      }
      N = cont.N;
      top = cont.top;
      tail = cont.tail;
      return *this;
    }
    
template <typename T>
std::size_t ListContainer<T>::size() {return N; }

template <typename T>
void ListContainer<T>::push_back(const T& obj) {
      if(!N) {
        top = new Node<T>;
        tail = top;
      } else {
        tail->next = new Node<T>;
        tail = tail->next;
      }
      tail->data = obj;
      tail->next = nullptr;
      ++N;
    }

template <typename T>
void ListContainer<T>::insert(const T& obj, std::size_t ind){
      if(ind > N || ind < 0){
        Err::indx();
        return;
      } else if(ind == N) {
        push_back(obj);
        return;
      } else if(!ind) {
        Node<T>* tmp = new Node<T>;
        tmp->next = top;
        tmp->data = obj;
        top = tmp;
        ++N;
        return;
      } else { 
        /* ind от 1 до N - 1 */
        Node<T> *previous = top, *p_next;
        while(--ind)
          previous = previous->next;

        p_next = previous->next;
        previous->next = new Node<T>;
        previous = previous->next;
        previous->data = obj;
        previous->next = p_next;
        ++N;
      }
    }

template <typename T>
void ListContainer<T>::erase(std::size_t ind) {
      if(ind >= N || ind < 0){
        Err::indx();
        return;
      } else if (!N) {
        Err::arr_siz();
        return;
      } else if(!ind) {
        Node<T>* tmp = top->next;
        delete top;
        top = tmp;
        --N;
        if(!N)
          tail = nullptr;
        return;
      } else { 
        /* ind от 1 до N - 1 */
        Node<T> *previous = top, *p_next;
        while(--ind)
          previous = previous->next;
        /* удалиь надо previous->next == эл-т с индексом ind */
        p_next = previous->next;
        previous->next = p_next->next;
        delete p_next;
        if(!previous->next)
          tail = previous;
        --N;
      }
    }

template <typename T>
T& ListContainer<T>::operator[](std::size_t ind) {
      if(ind >= N || ind < 0){
        Err::indx();
        if(top)
          return top->data;
        exit(1);
      }
      Node<T>* tmp = top;
      while(ind--)
        tmp = tmp->next;
      return tmp->data;
    }

