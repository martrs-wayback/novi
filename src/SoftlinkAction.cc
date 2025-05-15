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

#include<Action.h>
#include<SoftlinkAction.h>
#include<RPM.h>

#include<string>
#include<cstring> // strerror()
#include<iostream>

extern "C" {
	#include<errno.h>
	#include<unistd.h> // link() and variants
}


// - - - - - - - - - - - - - - - - - - - -

SoftlinkAction::SoftlinkAction( const std::string& path )
	:
	path_( path )
{
} // SoftlinkAction::ctor

bool SoftlinkAction::operator()( const Product& product )
	throw()
{

	const RPM* rpm = product.latestVersion() ;
	bool result = true ;

	if( ! Action::createDir( path_.c_str() ) ){
		std::cerr << "not copying \"" << rpm->getFile() << "\"" << std::endl ;
		return( false ) ;
	}

	std::string justFile = basename( rpm->getFile().c_str() ) ;

	buf_.str( "" ) ;
	buf_ << path_ << "/" << justFile << std::flush ;

	if( 0 != symlink( rpm->getFile().c_str() , buf_.str().c_str() ) ){
		std::cerr << "unable to link \"" << rpm->getFile() << "\" => \"" << buf_.str() << ": " << strerror( errno ) << std::endl ;
		result = false ;
	}

	return( result ) ;

} // SoftlinkAction::operator()

// - - - - - - - - - - - - - - - - - - - -
