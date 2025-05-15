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
#include<RPMSourceDescription.h>
#include<AppException.h>

#include<string>
#include<cstring>

RPMSourceDescription::RPMSourceDescription( const std::string& name )
	throw( AppException )
	:
	source_( name ) ,
	path_() ,
	type_( TYPE_UNKNOWN )
{

	std::string typeString ;
	std::string pathString ;

	std::string::size_type found = std::string::npos ;

	if( std::string::npos == ( found = source_.find( ':' ) ) ){

		// no type info
		typeString = "" ;
		pathString = source_ ;

	} else {

		typeString = source_.substr( 0 , found ) ;
		pathString = source_.substr( found + 1 , source_.size() ) ;

	}

	if(
		typeString.empty()
			||
		0 == strcmp( "dir" , typeString.c_str() )
	){
		type_ = TYPE_DIRECTORY ;
		path_ = pathString ;
	}else if( 0 == strcmp( "repo" , typeString.c_str() ) ){
		type_ = TYPE_REPO_XML ;
		path_ = pathString ;
	}else{
		type_ = TYPE_UNKNOWN ;
		path_ = pathString ;
	}

	return ;

} // RPMSourceDescription ctor

const std::string& RPMSourceDescription::getSource() const
	throw()
{
	return( source_ ) ;
} // RPMSourceDescription::getSource()

const std::string& RPMSourceDescription::getPath() const
	throw()
{
	return( path_ ) ;
} // RPMSourceDescription::getPath()

RPMSourceDescription::SourceType RPMSourceDescription::getType() const
	throw()
{
	return( type_ ) ;
} // RPMSourceDescription::getType()

// - - - - - - - - - - - - - - - - - - - -

