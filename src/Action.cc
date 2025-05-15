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
#include<Action.h>

#include<string>
#include<iostream>
#include<cstring> // strerror()

extern "C" {
	#include<unistd.h>
	#include<errno.h>
	#include<sys/types.h>	// defs: mode_t
	#include<sys/stat.h>	// stat() , mkdir()

}

#include<iostream>

// extern int errno ;

bool Action::createDir( const char* path )
	throw()
{

	bool result = true ;
	struct stat st ;

	if( 0 == stat( path , &st ) ){

		if( ! S_ISDIR( st.st_mode ) ){
			std::cerr << "path \"" << path << "\" exists, but is not a directory" << std::endl ;
			result = false ;
		}

	} else {

		if( 0 != mkdir( path , 0777 ) ){
			std::cerr << "unable to create directory \"" << path << "\": " << strerror( errno ) << std::endl ;
			result = false ;
		}

	}

	return( result ) ;
	
} // Action::createDir()


/*
messy, but preferable to calling C-level strdup()
*/

std::string Action::basename( const std::string& in ){

	// reverse-find "/" and return a new string based on
	// substr( found , end )

	// if "/" not found, return the original string

	std::string::size_type found = in.rfind( "/" ) ;

	if( std::string::npos == found ){

		return( in ) ;

	} else {

		std::string result( in.substr( found + 1 , std::string::npos ) ) ;
		return( result ) ;

	}

} // Action::basename()

// - - - - - - - - - - - - - - - - - - - -
