# include <iostream> 
# include "printerr.h"
# pragma once

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
  template <typename U>
  friend std::ostream& 
  operator<<(std::ostream& stream, IContainers<U>& cont);
  template <typename U>
  friend std::ostream& 
  operator<<(std::ostream& stream, IContainers<U>* cont);
};

/* контейнер с последовательным расположением в памяти */
template <typename T>
class SeqContainer: public IContainers<T>{
  private:
    T* real_first;
    std::size_t real_size;
    std::size_t N;

    void resize(std::size_t new_size);
  public: 
    ~SeqContainer();
    SeqContainer() ;
    SeqContainer(const T* arr, std::size_t len);
    SeqContainer(const SeqContainer<T>& cont);
    SeqContainer(SeqContainer<T>&& cont);
    SeqContainer& operator=(const SeqContainer<T>& cont);
    SeqContainer& operator=(SeqContainer<T>&& cont);
    std::size_t size() override;
    void push_back(const T& obj) override;
    void insert(const T& obj, std::size_t ind) override;
    void erase(std::size_t ind) override;
    T& operator[](std::size_t ind) override; 
};

template<typename T>
struct Node {
  Node<T>* next;
  T data;
};


/* списковый контейнер в одну сторону */
template <typename T>
class ListContainer: public IContainers<T>{
  private:
    Node<T>* top;
    Node<T>* tail;
    std::size_t N;
  public: 
    ~ListContainer();
    ListContainer();
    ListContainer(const T* arr, std::size_t len);
    ListContainer(const ListContainer<T>& cont);
    ListContainer(ListContainer<T>&& cont);
    ListContainer& operator=(const ListContainer<T>& cont);
    ListContainer& operator=(ListContainer<T>&& cont);
    std::size_t size() override;
    void push_back(const T& obj) override;
    void insert(const T& obj, std::size_t ind) override;
    void erase(std::size_t ind) override;
    T& operator[](std::size_t ind) override;
};

#include "containers.ipp"
