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

typedef std::set<string> TagSetT;

class IntervalMap {
    public:
      IntervalMap(interval_map<int, TagSetT> map) {
        this->map = map;
      }
      IntervalMap() {
      }
      void addOpenInterval(int start, int stop, string tag) {
        TagSetT tag_set;
        tag_set.insert(tag);
        map += make_pair(interval<int>::open(start, stop), tag_set);
      }
      void addClosedInterval(int start, int stop, string tag) {
        TagSetT tag_set;
        tag_set.insert(tag);
        map += make_pair(interval<int>::closed(start, stop), tag_set);
      }
      void removeOpenInterval(int start, int stop, string tag) {
        TagSetT tag_set;
        tag_set.insert(tag);
        map -= make_pair(interval<int>::open(start, stop), tag_set);
      }
      void removeClosedInterval(int start, int stop, string tag) {
        TagSetT tag_set;
        tag_set.insert(tag);
        map -= make_pair(interval<int>::closed(start, stop), tag_set);
      }
      IntervalMap addAll(IntervalMap *otherMap) {
        return IntervalMap(this->map + otherMap->map);
      }
      IntervalMap intersects(IntervalMap *otherMap) {
        return IntervalMap(this->map & otherMap->map);
      }
      Array getIntervals() {
        Array rubyIntervals;
        interval_map<int, TagSetT>::iterator it = map.begin();
        while(it != map.end())
        {
            Hash rubyInterval;
            interval<int>::type interval = it->first; // was discrete_interval in set and interval in map examples, why?
            rubyInterval[Symbol("lower")] = interval.lower();
            rubyInterval[Symbol("upper")] = interval.upper();
            rubyInterval[Symbol("lowerType")] = is_left_closed(interval.bounds()) ? Symbol("closed") : Symbol("open");
            rubyInterval[Symbol("upperType")] = is_right_closed(interval.bounds()) ? Symbol("closed") : Symbol("open");
            TagSetT tag_set = it->second;
            Array tags;
            std::set<string>::iterator tag_it;
            for (tag_it = tag_set.begin(); tag_it != tag_set.end(); ++tag_it)
            {
              string tag = *tag_it;
              tags.push(tag);
            }
            rubyInterval[Symbol("tags")] = tags;
            rubyIntervals.push(rubyInterval);
            *it++;
        }
        return rubyIntervals;
      }
    private:
      interval_map<int, TagSetT> map;
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

  Data_Type<IntervalMap> rb_cIntervalMap =
    define_class<IntervalMap>("IntervalMap")
    .define_constructor(Constructor<IntervalMap>())
    .define_method("addOpenInterval", &IntervalMap::addOpenInterval)
    .define_method("addClosedInterval", &IntervalMap::addClosedInterval)
    .define_method("removeOpenInterval", &IntervalMap::removeOpenInterval)
    .define_method("removeClosedInterval", &IntervalMap::removeClosedInterval)
    .define_method("addAll", &IntervalMap::addAll)
    .define_method("intersects", &IntervalMap::intersects)
    .define_method("getIntervals", &IntervalMap::getIntervals);
}
