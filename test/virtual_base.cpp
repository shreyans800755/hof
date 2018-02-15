#include <boost/hof/flip.hpp>
#include <boost/hof/proj.hpp>
#include <boost/hof/construct.hpp>
#include <boost/hof/pipable.hpp>
#include <boost/hof/rotate.hpp>
#include "test.hpp"

struct base { 
    base(int) {} 
    base(const base&) {}
    virtual ~base();
};

base::~base() {}

struct derived : virtual base {
    derived() : base(1) {}
    derived(const derived&) : base(1) {}
    int operator()(int i, void *) const {
        return i;
    }
    ~derived();
};
derived::~derived() {}

BOOST_HOF_TEST_CASE()
{
    BOOST_HOF_TEST_CHECK(boost::hof::flip(derived())(nullptr, 2) == 2);
    BOOST_HOF_TEST_CHECK(boost::hof::rotate(derived())(nullptr, 2) == 2);
    BOOST_HOF_TEST_CHECK((2 | boost::hof::pipable(derived())(nullptr)) == 2);
}
