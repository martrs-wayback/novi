#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

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

// - - - - - - - - - - - - - - - - - - - -

#include<AppException.h>
#include<GlobObj.h>
#include<Product.h>


#include<map>
#include<string>
#include<sstream>
#include<vector>

typedef std::map< std::string , Product > ProductListInternalMap ;

/**
\brief encapsulates the logic of handling Products

Think of it as a std::map<> with some extra intelligence.
*/

class ProductListIterator
	: public std::iterator< Product , Product >
	// : public std::iterator< Product , std::ptrdiff_t >
{

	public:

	typedef ProductListIterator self_type ;
	typedef self_type& self_reference ;
	typedef std::iterator_traits< ProductListIterator >::value_type value_type ;
	typedef std::iterator_traits< ProductListIterator >::reference reference ;
	typedef std::iterator_traits< ProductListIterator >::difference_type difference_type ;
	typedef std::iterator_traits< ProductListIterator >::pointer pointer ;
	// typedef std::iterator_traits< ProductListIterator >::value_type* pointer ;


	/**
	\brief builds default "end" object

	\param stop end of the range; should be the end of the ProductList's internal map
	*/
	explicit ProductListIterator( ProductListInternalMap::iterator stop ) ;

	/**
	\brief beginning or middle of a ProductList map range
	\param start start of range; should be the beginning of the ProductList's internal map
	\param stop end of the range; should be the end of the ProductList's internal map
	*/
	explicit ProductListIterator( ProductListInternalMap::iterator start , ProductListInternalMap::iterator stop ) ;


	self_reference operator++() ;
	self_type operator++(int) ;

	bool operator==( const self_reference other ) ;
	bool operator!=( const self_reference other ) ;

	reference operator*() ;

	reference operator->() ;


	protected:
	/* empty */


	private:
	ProductListInternalMap::iterator current_ ;
	ProductListInternalMap::iterator stop_ ;

} ; // class ProductListIterator


/**
\brief a pseudo-STL-type container that holds Products

Think of it as an STL map<> with some app-specific tweaks.

For example, a map<> is used to store the underlying Product
objects (such that they are searchable, for when a new RPM
is to be added) but the iterators permit algorithms to operate
on the Product objects directly. Otherwise, algorithms would
have to deal with the specifics of the underlying map<> and call
"map<>::iterator<>::second"...
*/

class ProductList {

	public:
	typedef ProductListIterator iterator ;
	typedef ProductListInternalMap::value_type value_type ;

	ProductList( bool ignoreSourceRPMS = false ) ;

	void add( const RPM* rpm ) ;

	bool empty() const throw() ;
	iterator begin() ;
	iterator end() ;
	int size() const throw() ;
	int getRPMCount() const throw() ;


	private:

	ProductListInternalMap map_ ;
	const bool ignoreSourceRPMS_ ;
        int rpmCount_ ;

} ; // ProductList


// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef PRODUCTLIST_H
