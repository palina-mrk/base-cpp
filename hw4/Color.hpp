#pragma once
#include <istream>
class Color {
  private:
    double r{};
    double g{};
    double b{};
  public:
    Color();
    ~Color() = default;
    Color(const Color& c) : r{c.r}, g{c.g}, b{c.b} {}
    Color& operator=(const Color& c) {
      r = c.red(); 
      g = c.green(); 
      b = c.blue(); 
      return *this;
    }
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    friend inline std::istream& operator>>(std::istream& stream, Color& c);

};


inline std::istream& operator>>(std::istream& stream, Color& c){
    stream >> c.r;
    stream >> c.g;
    stream >> c.b;
    return stream;
}
