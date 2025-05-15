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

#include<RPM.h>
#include<ProductList.h>
#include<AppException.h>

#include<string>
#include<map>
#include<sstream>
#include<iterator>



ProductListIterator::ProductListIterator( ProductListInternalMap::iterator stop )
	:
	current_( stop ) ,
	stop_( stop )
{

	/*
	not a typo -- current_ is used in operator==() so it should be the same for
	both current_ and stop_, since this overload of the ctor creates the "end"
	iterator
	*/

	return ;

} // ProductListIterator::ctor for "end" value

ProductListIterator::ProductListIterator( ProductListInternalMap::iterator start , ProductListInternalMap::iterator stop )
	:
	current_( start ) ,
	stop_( stop )
{
	return ;
} // ProductListIterator::ctor for "begin" value

ProductListIterator::self_type& ProductListIterator::operator++(){

	if( current_ == stop_ ){
		// QQQ - ?throw exception? or let operator shoot self in foot?
	}

	++current_ ;

	return( *this ) ;

} // ProductListIterator::operator++ (pre)

ProductListIterator::self_type ProductListIterator::operator++(int){

	self_type result( *this ) ;
	++( *this ) ;

	return( result ) ;

} // ProductListIterator::operator++ (post)


bool ProductListIterator::operator==( const self_reference other ){
	return(
		other.current_ == this->current_
	) ;
} // ProductListIterator::oeprator==

bool ProductListIterator::operator!=( const self_reference other ){
	return( ! ( (*this) == other ) ) ;
} // ProductListIterator::operator!=


ProductListIterator::reference ProductListIterator::operator*(){
	return( current_->second ) ;
} // ProductListIterator::operator*()


ProductListIterator::reference ProductListIterator::operator->(){
	return( *( *this ) ) ;
} // ProductListIterator::operator->



ProductList::ProductList( bool ignoreSourceRPMS )
	:
	map_() ,
	ignoreSourceRPMS_( ignoreSourceRPMS ),
        rpmCount_( 0 )
{
	return ;
} // ProductList::ctor


void ProductList::add( const RPM* rpm ) {

	// QQQ: BEGIN: wrap this logic in a separate filter object, loaded from object registry
	if(
		rpm->isSourcePackage()
			&&
		ignoreSourceRPMS_
	){
		return ;
	}
	// END: wrap this logic in a separate filter object


	std::ostringstream keyBuf ;
	keyBuf << rpm->getName() << ":" << rpm->getArch() ;

	if( rpm->isSourcePackage() ){
		keyBuf << ":SRC" ;
	}else{
		keyBuf << ":BIN" ;
	}

	std::string key = keyBuf.str() ;

	ProductListInternalMap::iterator found = map_.find( key ) ;

	/*
	strange insert is due to double-free of RPM* objects in Product dtor...
	must find another way around this.  (Make Product objects pointers, maybe?)
	*/

	if( map_.end() == found ){
		Product pr( key ) ;
		// pr.push( rpm ) ;
		map_.insert( ProductList::value_type( pr.getId() , pr ) ) ;

		map_.find( key )->second.push( rpm ) ;

	} else {
		found->second.push( rpm ) ;
	}

        ++rpmCount_ ;

	return ;

} // ProductList::add( const RPM* )


bool ProductList::empty() const
	throw()
{
	return( map_.empty() ) ;

} // ProductList::empty()

ProductList::iterator ProductList::begin() {

	ProductListIterator result( map_.begin() , map_.end() ) ;

	return( result ) ;

} // ProductList::begin()

ProductList::iterator ProductList::end()  {

	ProductListIterator result( map_.end() ) ;

	return( result ) ;

} // ProductList::end()

int ProductList::size() const
	throw()
{

	return( map_.size() ) ;

} // ProductList::size()

int ProductList::getRPMCount() const
    throw()
{

    return( rpmCount_ ) ;

} // ProductList::getRPMCount()

// - - - - - - - - - - - - - - - - - - - -
