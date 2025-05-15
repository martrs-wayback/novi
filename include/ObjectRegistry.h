#ifndef OBJECTREGISTRY_H_
#define OBJECTREGISTRY_H_

// QQQ:  create an object registry for oft-used, semi-temporary objects
//  (e.g. stringstream, character buf)
//        -> can use a single "rpmts" for all calls?


// this class is simply the wrapper; it relies on a
// strategy behind the scenes: basic impl; per-thread impl; etc

// use a typedef'd int (? or maybe an enum ?) for values
// all are pointers; return an object with two members:
//    1/ a void* for the object in question
//    2/ some description of said object


#endif /*OBJECTREGISTRY_H_*/
