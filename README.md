# Millibil

Millibil is a Ruby library that helps manipulating intervals, in particular interval sets and maps. It is based on the C++ library Boost and is basically a binding to its most useful interval manipulation functions.

## How to use the library

Millibil defines two Ruby classes, IntervalSet and IntervalMap. Maps and Sets work in a very similar way and can both be used to add or remove some intervals and compute the remaining intervals. Those intervals can be open or closed. For example :  
`[4,8] - [5,6] => [4,5[ ; ]6,8]`

IntervalMap can also work with tags, for example :  
`[1,5](tags: A) + [3,7](tags: B) => [1,3[(tags: A) ; [3,5](tags: A,B) ; ]5,7](tags: B)`

This last example coded in Ruby using Millibil would become the following :

    map = IntervalMap.new()
    map.addClosedInterval(1, 5, "A")
    map.addClosedInterval(3, 7, "B")
    map.getIntervals

A complete documentation of the underlying functions can be found on Boost's documentation page for interval manipulation : https://www.boost.org/doc/libs/1_64_0/libs/icl/doc/html/index.html

## How to build the library

Execute the following commands :

`gem build millibil.gemspec`  
`gem install <filename>`
