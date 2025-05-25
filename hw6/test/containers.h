# include <iostream> 

template <typename T>
class IContainers {
  public:
    virtual ~IContainers() {}
    IContainers() {}
    virtual void push_back(const T& obj) = 0;
    virtual void insert(const T& obj, std::size_t ind) = 0;
    virtual void erase(std::size_t ind) = 0;
    virtual std::size_t size() = 0;
    virtual T& operator[](std::size_t i) = 0;
};

class Err{
  public:
    static void mem_all(){
      std::cout << "Memory allocation failed\n";
      exit(1);
    }
    static void indx() {
      std::cout << "Error: invalid index\n";
    }
    static void arr_siz() {
      std::cout << "Error: attemption to set invalid array length\n";
    }
};

/* контейнер с последовательным расположением в памяти */

template <typename T>
class SeqContainer: public IContainers<T>{
  private:
    T* real_first;
    std::size_t real_size;
    std::size_t N;

    void resize(std::size_t new_size) {
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
  public: 
    ~SeqContainer() {
      delete []real_first;
      real_first = nullptr;
      N = 0;
      real_size = 0;
    }
    SeqContainer() {
      N = 0;
      real_size = 8;
      real_first = new T[real_size];
      if(!real_first)
        Err::mem_all();
    }
    SeqContainer(const T* arr, std::size_t len) {
      real_size = (len > 4 ? 2*len : 8);
      real_first = new T[real_size];
      if(!real_first)
        Err::mem_all();
      N = len;
      for(int i = 0; i < N; ++i)
        real_first[i] = arr[i];
    }
    std::size_t size() override {return N; }
    void push_back(const T& obj) override  {
      if(N == real_size)
        resize(2*N);
      real_first[N] = obj;
      ++N;
    }
    void insert(const T& obj, std::size_t ind) override {
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
    void erase(std::size_t ind) override  {
      if(ind > N || ind < 0){
        Err::indx();
        return;
      }
      --N;
      for(int j = ind; j < N; ++j)
        real_first[j] = real_first[j + 1];
    }
    T& operator[](std::size_t ind)  override {
      if(ind > N || ind < 0){
        Err::indx();
        return *real_first;
      }
      return real_first[ind];
    }

  template <typename U>
  friend std::ostream& 
  operator<<(std::ostream& stream, SeqContainer<U>& cont);
};

template <typename T>
std::ostream& 
operator<<(std::ostream& stream, SeqContainer<T>& cont){
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

/*
template<typename T>
struct Node {
  Node* next = nullptr;
  T data;
  T& operator*{ return *data; } 
}

template<typename T>{
struct DoubleNode {
  Node* next = nullptr;
  Node* prev = nullptr;
  T data;
  T& operator*{ return *data; } 
}

template <typename T>
class ListContainer: public IContainers<T>{
  public: 
    override ~ListContainer();
    override ListContainer();
    override void push_back() = 0;
    override void insert(std::size_t i);
    override void erase(std::size_t i);
    override T& operator[](std::size_t i);
  private:
    Node<T>* top;
    Node<T>* tail;
};

template <typename T>
class DoubleListContainer: public IContainers<T>{
  public: 
    override ~ListContainer();
    override ListContainer();
    override void push_back() = 0;
    override void insert(std::size_t i);
    override void erase(std::size_t i);
    override T& operator[](std::size_t i);
  private:
    DoubleNode<T>* top;
    DoubleNode<T>* tail;
};
*/
//# include <containres.ipp>
