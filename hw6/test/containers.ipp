# include <iostream> 

template <typename T>
class IContainers {
  public:
    virtual ~IContainers() = 0;
    IContainers() : N{0} = 0;
    IContainers(T* arr, size_t len) = 0;
    virtual void push_back(const T& next) = 0;
    virtual T pop() = 0;
    virtual void insert(const T& obj, std::size_t i) = 0;
    virtual void erase(std::size_t i) = 0;
    std::size_t size {return N;}
    T& operator[](std::size_t i) = 0;
  protected:
    std::size_t N;
};

/* контейнер с последовательным расположением в памяти */
template <typename T>
class SeqContainer: public IContainers<T>{
  public: 
    override ~SeqContainer();
    override SeqContainer();
    override SeqContainer(T* arr, size_t len);
    override void push_back() = 0;
    override void insert(std::size_t i);
    override void erase(std::size_t i);
    override T& operator[](std::size_t i);
  private:
    void resize(std::size_t new_size);
    std::size_t real_size;
    T* first;
    T* last;
};

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

# include <containres.ipp>
