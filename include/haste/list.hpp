#pragma once
#include <vector>

namespace haste {

using std::vector;

namespace detail {

template <class... L> class make_list;

template <class H, class... T> class make_list<H, T...>
{
  static void call()
  {
    return ; // std::string(typeid(First).name()) + " " + Impl<Args...>::name();
  }
};

template <> class make_list<>
{
  static std::string name()
  {
    return "";
  }
};



}


template <class H, class... L> vector<H> make_list(const H& head, const L&... items) {
	return vector<H> { head, items... };
}

}
