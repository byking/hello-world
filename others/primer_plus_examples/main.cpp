#include <iostream>
#include <gflags/gflags.h>

struct job {
  char name[40];
  double salary;
  int floor;
};

//general version
template <typename T> void swap(T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

//explicit specialization
template <> void swap<job>(job &j1, job &j2) {
  double t1;
  t1 = j1.salary;
  j1.salary = j2.salary;
  j2.salary = t1;
}

//general version
template <typename T1, typename T2> 
auto add (T1 x, T2 y) -> double {
  return x + y;
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  int i = 10, j = 20;
  swap(i, j); //implicit instantiation

  //swap<double>(i, j); //error because can't change type from int& to double&

  //explicit instantiation --> will change type to double of x,y 
  std::printf("%lf\n", add<double, double>(1,1));
  //implicit instantiation
  std::printf("%lf\n", add(1,1));

  job sue = {"sue", 7300, 7}; 
  job sidney = {"sidney", 7800, 8};
  swap<job>(sue, sidney); //explicit instantiation 

  return 0;
}
