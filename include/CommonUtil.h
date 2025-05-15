#ifndef COMMONUTIL_H
#define COMMONUTIL_H

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

#include<AppException.h>
#include<GlobObj.h>

// - - - - - - - - - - - - - - - - - - - - 

#include<functional>


/**
\brief miscellaneous appwide utilties

Some of these are borrowed from my Petal project...

This is a struct, not a class, because it's expected to contain just static
functions or functor objects.  For that same reason, the ctor and copy ctor
are locked off and unimplemented.


*/

class CommonUtil {

	public:

	/// functor to delete pointers of any type...
	
	struct CleanPointerObjects2 {
		template< typename T >
		void operator()( const T* object ) const
			throw()
		{

			if( NULL != object ){
				delete( object ) ;
			}

			return ;

		}

	} ; // struct CleanPointerObjects


	template< typename T >
	struct CleanPointerObjects : public std::unary_function< T , void > {

		void operator()( const T* object ) const
			throw()
		{

			if( NULL != object ){
				delete( object ) ;
			}

			return ;

		}

	} ; // struct CleanPointerObjects


	protected:
	// empty

	private:

	/// unimplemented
	CommonUtil() ;

	CommonUtil( const CommonUtil& ) ;

} ; // class CommonUtil

// - - - - - - - - - - - - - - - - - - - - 

#endif // #ifndef COMMONUTIL_H
