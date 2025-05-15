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

#include<RPM.h>
#include<AppException.h>

#include<string>
#include<cstring> // strcmp()
#include<iostream>

// - - - - - - - - - - - - - - - - - - - -

extern "C" {
	#include<rpm/rpmlib.h>
	#include<rpm/rpmio.h>
	#include<rpm/rpmts.h>
	#include<rpm/header.h>
}

#include<cstdio>
#include<sstream>

RPM::RPM()
	:
	file_() ,
	name_() ,
	arch_() ,
	epoch_( 0 ) ,
	version_() ,
	release_() ,
	fullVersion_() ,
	isSourcePackage_( false )
{
	// sic
} // RPM::ctor()

RPM::RPM( const RPM& other )
	:
	file_( other.getFile() ) ,
	name_( other.getName() ) ,
	arch_( other.getArch() ) ,
	epoch_( other.getEpoch() ) ,
	version_( other.getVersion() ) ,
	release_( other.getRelease() ) ,
	fullVersion_( other.getFullVersion() ) ,
	isSourcePackage_( other.isSourcePackage() )
{

} // RPM copy ctor

const std::string& RPM::getFile() const
	throw()
{
	return( file_ ) ;
} // RPM::getFile()


void RPM::setFile( const std::string& file ){
	file_ = file ;
} // RPM::setFile()


const std::string& RPM::getName() const
	throw()
{
	return( name_ ) ;
} // RPM::getName()


void RPM::setName( const std::string& name ){
	name_ = name ;
} // RPM::setName()


const std::string& RPM::getArch() const
	throw()
{
	return( arch_ ) ;
} // RPM::getArch()

void RPM::setArch( const std::string& arch ){
	arch_ = arch ;

	if( 0 == strcmp( "src" , arch_.c_str() ) ){
		isSourcePackage_ = true ;
	}


} // RPM::setArch()

int RPM::getEpoch() const
	throw()
{
	return( epoch_ ) ;
} // RPM::getEpoch()

const std::string& RPM::getVersion() const
	throw()
{
	return( version_ ) ;
} // RPM::getVersion()

const std::string& RPM::getRelease() const
	throw()
{
	return( release_ ) ;
} // RPM::getRelease()

const std::string& RPM::getFullVersion() const
	throw()
{
	return( fullVersion_ ) ;
} // RPM::getFullVersion()


void RPM::setFullVersion( int epoch , const std::string& version , const std::string& release ){

	epoch_   = epoch ;
	version_ = version ;
	release_ = release ;

	std::ostringstream verTmp ;

	verTmp << epoch_ << ":" << version_ << "-" << release_ << std::flush ;

	fullVersion_ = verTmp.str() ;

	return ;

} // RPM::setFullVersion()

const bool RPM::isSourcePackage() const
	throw()
{
	return( isSourcePackage_ ) ;
} // RPM::isSourcePackage()

void RPM::print( std::ostream& s ) const
{

	s << getName() << "-" ;

	if( isSourcePackage() ){
		s << "SRC-" ;
	}

	s << getFullVersion() ;

} // RPM::print()

// - - - - - - - - - - - - - - - - - - - -


std::ostream& operator<<( std::ostream& s , const RPM& obj ){
	obj.print( s ) ;
	return( s ) ;
}

// - - - - - - - - - - - - - - - - - - - -

bool RPMLess::operator()( const RPM* rpmLeft , const RPM* rpmRight ) const
	throw()
{

		/*
		from the API docs:
 		int rpmvercmp( const char* a, const char* b )
		Segmented string compare for version and/or release.

		Returns:
			+1 if a is "newer", 0 if equal, -1 if b is "newer"

		*/

		/*
		QQQ: double-check logic, based on STL rules for comparators
		*/

	bool result ;

	/*
	std::cerr << "comparing: "
		<< rpmLeft->getEpoch() << "  " << *rpmLeft
		<< " < "
		<< rpmRight->getEpoch() << "  " << *rpmRight
		<< std::endl ;
	*/


	const int leftEpoch = rpmLeft->getEpoch() ;
	const int rightEpoch = rpmRight->getEpoch() ;

	const int compareVersion = rpmvercmp(
		rpmLeft->getVersion().c_str() ,
		rpmRight->getVersion().c_str()
	) ;

	const int compareRelease = rpmvercmp(
		rpmLeft->getRelease().c_str() ,
		rpmRight->getRelease().c_str()
	) ;


	// QQQ: cleaner way to do this?

	if( leftEpoch < rightEpoch ){

		// "rpmLeft" is older (less than) than "rpmRight"
		result = LEFT_IS_OLDER_ ;

	}else if( leftEpoch > rightEpoch ){

		// 1 == compareEpoch
		result = LEFT_IS_NEWER_ ;

	}else{

		// "rpmLeft" and "rpmRight" are same epoch,
		// but maybe different version

		switch( compareVersion ){

			case -1: // "rpmLeft" is older (less than) "rpmRight"
				result = LEFT_IS_OLDER_ ;
				break ;

			case 1: // "rpmLeft" is newer (not less) than "rpmRight"
				result = LEFT_IS_NEWER_ ;
				break ;

			case 0: // same version, must check release

				if( -1 == compareRelease ){
					result = LEFT_IS_OLDER_ ;
				}else{
					/*
					(sic) STL comparator rules require that a "less than" operator
					return false if the two objects are "equal"
					*/
					result = LEFT_IS_NEWER_ ;
				}
				break ;

		} // switch( compareVersion )

	}


	// std::cerr << "  result: " << result << std::endl ;

	return( result ) ;

} // RPMLess::operator()

// - - - - - - - - - - - - - - - - - - - -
