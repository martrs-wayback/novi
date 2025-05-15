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

#include<GlobObj.h>

#include<iostream>
#include<cstdio>
#include<cstring>

extern "C" {
	#include<glob.h>
}

// - - - - - - - - - - - - - - - - - - - -


GlobObjIterator::GlobObjIterator()
	:
	list_( NULL ) ,
	current_()
{
	return ;
} // GlobObjIterator:: "end-range" ctor

GlobObjIterator::GlobObjIterator( char** list )
	:
	list_( list ) ,
	current_( *( list_ ) )
{

	++list_ ; // advance pointer here to simplify logic of operator++()
	return ;

} // GlobObjIterator:: "beginning-" or "mid-range" ctor


GlobObjIterator::self_type& GlobObjIterator::operator++(){


	if( NULL != *list_ ){
		current_ = *list_ ;
		++list_ ;
	}else{
		current_ = "[past the end!!]" ;
		list_ = NULL ;
	}

	return( *this ) ;

} // GlobObjIterator::operator++ (pre)

GlobObjIterator::self_type GlobObjIterator::operator++(int){

	self_type result( *this ) ;
	++( *this ) ;

	return( result ) ;

} // GlobObjIterator::operator++ (post)


bool GlobObjIterator::operator==( const self_reference other ){
	return( other.list_ == this->list_ ) ;
} // GlobObjIterator::oeprator==

bool GlobObjIterator::operator!=( const self_reference other ){
	return( ! ( (*this) == other ) ) ;
} // GlobObjIterator::operator!=


GlobObjIterator::reference GlobObjIterator::operator*(){
	return( current_ ) ;
} // GlobObjIterator::operator*()

GlobObjIterator::reference GlobObjIterator::operator->(){
	return( *( *this ) ) ;
} // GlobObjIterator::operator->

// - - - - - - - - - - - - - - - - - - - -


int GlobObj::globErrorHandler( const char* epath , int eerno ){

	// QQQ: currently a no-op... must decide whether to have this
	// do something, or just not set it
	// (since the exception propagates the error to the caller,
	//  this function serves little purpose)
	// std::cerr << "Unable to traverse directory \"" << epath << "\": " << std::strerror( eerno ) << std::endl ;

	/*
	return something nonzero to cause
	glob() to halt processing with a 
	GLOB_ABORT value
	*/
	return( 0 ) ;

} // GlobObj::globErrorHandler()


GlobObj::GlobObj()
	:
	glob_()
{

	return ;

} // GlobObj::ctor()

GlobObj::GlobObj( const std::string& inPattern )
	:
	glob_()
{

	// QQQ: throw exception
	push_back( inPattern ) ;

	/*
	std::cout << "Total " << globData->gl_pathc << " paths match expression" << std::endl ;

	char** currentPath = globData -> gl_pathv ;

	while( NULL != *currentPath ){

		std::cout << "Element: \"" << *currentPath << "\"" << std::endl ; 
		++currentPath ;

	}
	*/

	return ;

} // GlobObj::ctor( const std::string& )

GlobObj::~GlobObj()
	throw()
{

	globfree( &glob_ ) ;

	return ;

} // GlobObj::dtor


void GlobObj::push_back( const std::string& inPattern ){

	int globResult = glob(
		inPattern.c_str() ,
		GLOB_MARK | GLOB_DOOFFS | GLOB_APPEND , 
		GlobObj::globErrorHandler ,
		&glob_
	) ;

	if( 0 != globResult ){
		// QQQ -- throw exception
		std::cerr << "Encountered error expanding pattern \"" << inPattern << "\"" << std::endl ;
	}

	return ;

} // GlobObj::push_back()


GlobObj::iterator GlobObj::begin(){

	if( 0 == size() ){
		// empty, nothing to do
		GlobObj::iterator result ;
		return( result ) ;
	}else{
		return( GlobObj::iterator( glob_.gl_pathv ) ) ;
	}
	
} // GlobObj::begin()


const GlobObj::iterator GlobObj::end(){
	GlobObj::iterator result ;
	return( result ) ;
} // GlobObj::end()


size_t GlobObj::size() const throw(){
	return( glob_.gl_pathc ) ;
} // GlobObj::size()

bool GlobObj::empty() const throw(){
	return( 0 == size() ) ;
} // GlobObj::empty()

// - - - - - - - - - - - - - - - - - - - -
