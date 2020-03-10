#include "hello.hpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(wrapper)
{
  using namespace boost::python;
  Py_Initialize();
  def("greet", greet);
}
