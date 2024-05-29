#include <iostream>

// ============================================================
template<typename Tag>
struct result {
  /* export it ... */
  typedef typename Tag::type type;
  static type ptr;
};

template<typename Tag>
typename result<Tag>::type result<Tag>::ptr;

template<typename Tag, typename Tag::type p>
struct rob : result<Tag> {
  /* fill it ... */
  struct filler {
    filler() { result<Tag>::ptr = p; }
  };
  static filler filler_obj;
};

template<typename Tag, typename Tag::type p>
typename rob<Tag, p>::filler rob<Tag, p>::filler_obj;


//
// EXAMPLE
//

class A 
{
private:
  void f() {
    std::cout << "proof!" << std::endl;
  }
};

struct Af { typedef void(A::*type)(); };
template struct rob<Af, &A::f>;


int main() 
{
  A a;
  (a.*result<Af>::ptr)();
}

