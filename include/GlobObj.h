#ifndef GLOB_TYPE_H
#define GLOB_TYPE_H

/*
Copyright 2005 Ethan McCallum (ethanqm -at- penguinmail.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

or in the file

	LICENSE

which is distributed with this package.

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
Limitations under the License.
*/


#include<iostream>
#include<cstdio>
#include<string>
#include<list>
#include<iterator>

extern "C" {
	#include<glob.h>
}

/**
\brief an STL-style iterator for the GlobObj class
*/
class GlobObjIterator
	: public std::iterator< std::string , std::string >
	// : public std::iterator< std::string , std::ptrdiff_t >
{

	public:

	typedef GlobObjIterator self_type ;
	typedef self_type& self_reference ;
	typedef std::iterator_traits< GlobObjIterator >::value_type value_type ;
	typedef std::iterator_traits< GlobObjIterator >::reference reference ;
	typedef std::iterator_traits< GlobObjIterator >::difference_type difference_type ;
	typedef std::iterator_traits< GlobObjIterator >::pointer pointer ;
	// typedef std::iterator_traits< GlobObjIterator >::value_type* pointer ;

	explicit GlobObjIterator() ; // builds default "end" object
	explicit GlobObjIterator( char** list ) ; // beginning or middle of a glob's range

	/*
	NOTE:
	no dtor -- do NOT free() the char** passed in the ctor!
	it belongs to the glob_t from the parent GlobObj object
	*/

	/// move forward one item, pre-increment
	self_reference operator++() ;

	/// move forward one item, post-increment
	self_type operator++(int) ;

	/// test whether this iterator is the same as another
	bool operator==( const self_reference other ) ;


	/// test whether this iterator is not the same as another
	bool operator!=( const self_reference other ) ;

	/// dereference the iterator: returns the current path as a std::string
	reference operator*() ;

	/// access the underlying object, in this case a std::string
	reference operator->() ;


	protected:
	/* empty */


	private:
	/// the list from the parent GlobObj's underlying glob_t
	char** list_ ;

	/// the current item in the list
	std::string current_ ;


} ; // class GlobObjIterator


/**
\brief C++ wrapper around the glob() system call.

It works similar to an STL container:
Pass it a list<> of paths and use the iterators to
touch each item, as expanded by the system call.

This class is named "GlobObj" because the name "Glob"
conflicted with an existing class somewhere (but not
within this project).

*/


class GlobObj {

	public:
	/// STL-style iterator for this container
	typedef GlobObjIterator iterator ;

	/// prints an error message when there's a problem expanding a pattern
	static int globErrorHandler( const char* epath , int eerno ) ;

	/// empty ctor -- requires that you call push_back() to add some patterns
	GlobObj() ;

	/// create an object with one pattern.  You can still call push_back() to add more.
	GlobObj( const std::string& inPattern ) ;

	/// basic dtor -- destroys the underlying glob_t
	~GlobObj() throw() ;

	/**
	\brief adds a pattern to the list

	Calling this invalidates any existing iterators.
	*/
	void push_back( const std::string& inPattern ) ;

	/// returns an iterator to the beginning of the collection
	iterator begin() ;

	/// returns an iterator signaling <I>one past the end</I> of the collection
	const iterator end() ;

	/// reports number of items (files) thus far matched 
	size_t size() const throw() ;
	
	/// does the container have 0 elements?
	bool empty() const throw() ;

	protected:
	/* empty */

	private:
	/// holds the expanded paths in a char**
	glob_t glob_ ;

} ; // class GlobObj

#endif // #ifndef GLOB-TYPE_H
