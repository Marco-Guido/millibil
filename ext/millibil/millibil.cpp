#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"
#include "rice/Hash.hpp"
#include "rice/Symbol.hpp"

#include "boost/icl/interval.hpp"
#include "boost/icl/interval_map.hpp"

#include <iostream>

using namespace Rice;
using namespace std;
using namespace boost::icl;

class IntervalSet {
    public:
      IntervalSet(interval_set<int> set) {
        this->set = set;
      }
      IntervalSet() {
      }
      void addOpenInterval(int start, int stop) {
        set += interval<int>::open(start, stop);
      }
      void addClosedInterval(int start, int stop) {
        set += interval<int>::closed(start, stop);
      }
      void removeOpenInterval(int start, int stop) {
        set -= interval<int>::open(start, stop);
      }
      void removeClosedInterval(int start, int stop) {
        set -= interval<int>::closed(start, stop);
      }
      IntervalSet addAll(IntervalSet *otherSet) {
        return IntervalSet(this->set + otherSet->set);
      }
      IntervalSet intersects(IntervalSet *otherSet) {
        return IntervalSet(this->set & otherSet->set);
      }
      Array getIntervals() {
        Array rubyIntervals;
        interval_set<int>::iterator it = set.begin();
        while(it != set.end())
        {
            Hash rubyInterval;
            discrete_interval<int> interval = *it;
            rubyInterval[Symbol("lower")] = interval.lower();
            rubyInterval[Symbol("upper")] = interval.upper();
            rubyInterval[Symbol("lowerType")] = is_left_closed(interval.bounds()) ? Symbol("closed") : Symbol("open");
            rubyInterval[Symbol("upperType")] = is_right_closed(interval.bounds()) ? Symbol("closed") : Symbol("open");
            rubyIntervals.push(rubyInterval);
            *it++;
        }
        return rubyIntervals;
      }
    private:
      interval_set<int> set;
};

extern "C"
void Init_millibil()
{
  Data_Type<IntervalSet> rb_cIntervalSet =
    define_class<IntervalSet>("IntervalSet")
    .define_constructor(Constructor<IntervalSet>())
    .define_method("addOpenInterval", &IntervalSet::addOpenInterval)
    .define_method("addClosedInterval", &IntervalSet::addClosedInterval)
    .define_method("removeOpenInterval", &IntervalSet::removeOpenInterval)
    .define_method("removeClosedInterval", &IntervalSet::removeClosedInterval)
    .define_method("addAll", &IntervalSet::addAll)
    .define_method("intersects", &IntervalSet::intersects)
    .define_method("getIntervals", &IntervalSet::getIntervals);
}
