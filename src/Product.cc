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

#include<Product.h>
#include<RPM.h>
#include<AppException.h>
#include<CommonUtil.h>

#include<string>
#include<iostream>
#include<algorithm>

// - - - - - - - - - - - - - - - - - - - -

Product::Product( const std::string& inId )
	:
	id_( inId ) ,
	list_() ,
	latest_( NULL )
{
	return ;
} // Product::ctor


void Product::push( const RPM* obj ){

	// ... sorting is now handled by set<>
	list_.insert( obj ) ;

	// set<> sorting puts newest RPM in front
	// latest_ = *( list_.rbegin() ) ;

	return ;

} // Product::push


Product::~Product()
	throw()
{

	std::for_each(
		list_.begin() ,
		list_.end() ,
		CommonUtil::CleanPointerObjects< RPM >()
	) ;

	return ;

} // Product dtor

const std::string& Product::getId() const
	throw()
{
	return( id_ ) ;
} // Product::getFile()


bool Product::empty() const
	throw()
{
	return( list_.empty() ) ;
} // Product::empty()

int Product::size() const
	throw()
{
	return( list_.size() ) ;
} // Product::size()

const RPM* Product::latestVersion() const
	throw()
{

	// std::cout << "size = " << size() << std::endl ;

	const RPM* result = *( list_.rbegin() ) ;
	if( NULL == result ){
		// QQQ - throw exception
		std::cerr << "no entry for " << getId() << std::endl ;
		std::exit( 1 ) ;
	}

	return( result ) ;

} // Product::latestVersion()

// - - - - - - - - - - - - - - - - - - - -
