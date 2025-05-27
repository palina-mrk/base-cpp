# include <iostream> 

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
