#include <iostream> 

using namespace std;

class A {
public:
    void func1() {}
    virtual void vfunc() {}
 
private:
    int m_a;
};

int main() {
    A a;
    cout << sizeof(a);  
}
