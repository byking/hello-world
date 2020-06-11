#include <iostream>

using namespace std;

enum class shape_type {
  circle,
  triangle,
  rectangle
};

class shape {
public: 
  shape() {
    cout << "shape constructor" << endl;;
  }
  virtual ~shape() {
    cout << "shape deconstructor" << endl;
  }

};

class circle : public shape {
public:
  circle() {
    cout << "circle constructor" << endl;
  }
  ~circle() {
    cout << "circle deconstructor" << endl;
  }
};

class triangle : public shape {};
class rectangle : public shape {};

shape* create_shape(shape_type type) {
  switch(type) {
  case shape_type::circle:
    return new circle();
  case shape_type::triangle:
    return new triangle();
  case shape_type::rectangle:
    return new rectangle(); 
  }
}

class shape_wrapper {
public:
  explicit shape_wrapper(shape* ptr = nullptr) 
    : ptr_(ptr) {}
  ~shape_wrapper() {
    delete ptr_;
  }
  shape* get() const {return ptr_;}
private:
  shape* ptr_;
};

int main() {
  shape_wrapper ptr_wrapper(create_shape(shape_type::circle));
  
  //circle* c = new circle();
  //delete c;

  return 0;
}


