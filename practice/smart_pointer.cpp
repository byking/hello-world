#include <iostream>
#include <utility>

using namespace std;

enum class shape_type {
  circle,
  triangle,
};

class shape {
public:
    shape() : type(0) {
    }
    virtual void get_type() {
	std::cout << "shape=" << type << std::endl;
    }
    virtual ~shape() {}
private:
    int type;
};

class circle : public shape {
public:
    circle() : type(1) {}
    virtual void get_type() {
	std::cout << "shape=" << type << std::endl;
    }
    ~circle() { puts("~circle()"); }
private:
    int type;
};

class triangle : public shape {
public:
    triangle() : type(2) {}
    virtual void get_type() {
	std::cout << "shape=" << type << std::endl;
    }
    ~triangle() { puts("~triangle()"); }
private:
    int type;
};

shape* create_shape(shape_type type)
{
  switch (type) {
  case shape_type::circle:
    return new circle();
  case shape_type::triangle:
    return new triangle();
  }
}

class shared_count {
public:
  shared_count() noexcept
    : count_(1) {}
  void add_count() noexcept
  {
    ++count_;
  }
  long reduce_count() noexcept
  {
    return --count_;
  }
  long get_count() const noexcept
  {
    return count_;
  }

private:
  long count_;
};

template <typename T>
class smart_ptr {
public:
  explicit smart_ptr(T* ptr = nullptr)
    : ptr_(ptr)
  {
    if (ptr) {
      shared_count_ =
        new shared_count();
    }
  }
  ~smart_ptr()
  {
    if (ptr_ &&
      !shared_count_
         ->reduce_count()) {
      delete ptr_;
      delete shared_count_;
    }
  }
  smart_ptr(const smart_ptr& other)
  {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_
        ->add_count();
      shared_count_ =
        other.shared_count_;
    }
  }
  smart_ptr(smart_ptr&& other) noexcept
  {
    ptr_ = other.ptr_;
    if (ptr_) {
      shared_count_ =
        other.shared_count_;
      other.ptr_ = nullptr;
    }
  }
  smart_ptr&
  operator=(smart_ptr rhs) noexcept
  {
    rhs.swap(*this);
    return *this;
  }

  T* get() const noexcept
  {
    return ptr_;
  }
  long use_count() const noexcept
  {
    if (ptr_) {
      return shared_count_
        ->get_count();
    } else {
      return 0;
    }
  }
  void swap(smart_ptr& rhs) noexcept
  {
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(shared_count_,
         rhs.shared_count_);
  }

  T& operator*() const noexcept
  {
    return *ptr_;
  }
  T* operator->() const noexcept
  {
    return ptr_;
  }
  operator bool() const noexcept
  {
    return ptr_;
  }

private:
  T* ptr_;
  shared_count* shared_count_;
};

int main() {
    smart_ptr<shape> ptr1(new circle()); 
    printf("use count of ptr1 is %ld\n", ptr1.use_count()); 

    //smart_ptr<shape> ptr2((ptr1)); 
    //printf("use count of ptr2 was %ld\n", ptr2.use_count()); 
    
    smart_ptr<shape> ptr3;
    ptr3 = ptr1; 
    //printf("use count of ptr2 was %ld\n", ptr2.use_count()); 
    printf("use count of ptr3 is now %ld\n", ptr3.use_count()); 
    //if (ptr1) { puts("ptr1 is not empty"); printf("use of ptr1 is now %ld\n", ptr1.use_count());}; 
    return 0;
}

