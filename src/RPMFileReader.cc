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

#include<RPMFileReader.h>
#include<AppException.h>
#include<RPM.h>

#include<string>
#include<iostream>

#include <rpm/rpmlib.h>
#include <rpm/rpmlog.h>
#include <rpm/rpmtag.h>
#include <rpm/rpmio.h>
#include <rpm/rpmpgp.h>
#include <rpm/rpmts.h>
#include <rpm/rpmtd.h>

// include these constants since they don't appear to be defined in rpmtd.h
static const int LOCAL_HEADER_GET_OK = 1 ;
static const int LOCAL_HEADER_GET_FAIL = 0 ;

RPMFileReader::RPMFileReader() {

	rpmSetVerbosity( RPMLOG_ERR ) ;
	rpmTransactionSet_ = rpmtsCreate() ;

}

RPMFileReader::~RPMFileReader() {

	rpmtsFree( rpmTransactionSet_ ) ;
}


const RPM* RPMFileReader::load( const std::string& path )  throw( AppException ) {

	// QQQ: log std::cout << "Operating on file " << fileName << std::endl ;

	FD_t fileHandle = Fopen( path.c_str() , "r.ufdio" ) ;

	if( Ferror( fileHandle ) ){
		throw( AppException( Fstrerror( fileHandle ) ) ) ;
	}


	// QQQ: set rpmVSFlags -- don't check sigs, etc -- must wait until code base
	// stabalizes and Fedora build trees catch up (right now sample code from
	// 4.6 mainline does not build against version that ships with Fedora 10)

	Header header ;

	rpmRC rc = rpmReadPackageFile( rpmTransactionSet_ , fileHandle , path.c_str() , &header ) ;
	switch( rc ){

		case RPMRC_NOTFOUND:  // likely, not a real RPM file; (confirm with "rpm -Vp {file}" or "file {file}")
		case RPMRC_FAIL: // some other RPM error
			{
				std::cerr << "error loading " << path << ": " << rpmlogMessage() << std::endl ;
				throw( AppException( rpmlogMessage() ) ) ;
			}

		// the other cases are:
		//    RPMRC_OK (good),
		//    RPMRC_NOTTRUSTED (we don't care),
		//    RPMRC_NOKEY (we don't care)

	} // switch( retval )


	rpmtd tagData = rpmtdNew() ;

	RPM result ;

	result.setFile( path ) ;

	if( LOCAL_HEADER_GET_OK == headerGet( header , RPMTAG_ARCH , tagData , HEADERGET_DEFAULT ) ){
		result.setArch( rpmtdGetString( tagData ) ) ;
	}else{
		throw( AppException( "unable to fetch RPM arch from header" ) ) ;
	}

	if( LOCAL_HEADER_GET_OK == headerGet( header , RPMTAG_NAME , tagData , HEADERGET_DEFAULT ) ){
		result.setName( rpmtdGetString( tagData ) ) ;
	}else{
		throw( AppException( "unable to fetch RPM name from header" ) ) ;
	}

	int epoch = 0 ;
	std::string version ;
	std::string release ;

	if( LOCAL_HEADER_GET_OK == headerGet( header , RPMTAG_EPOCH , tagData , HEADERGET_DEFAULT ) ){
		// sic -- rpmtdGetUint32 returns a pointer, not a scalar
		epoch = *( rpmtdGetUint32( tagData ) ) ;
	}


	if( LOCAL_HEADER_GET_OK == headerGet( header , RPMTAG_VERSION , tagData , HEADERGET_DEFAULT ) ){
		version = rpmtdGetString( tagData ) ;
	}else{
		throw( AppException( "Unable to fetch RPM version from header" ) ) ;
	}

	if( LOCAL_HEADER_GET_OK == headerGet( header , RPMTAG_RELEASE , tagData , HEADERGET_DEFAULT ) ){
		release = rpmtdGetString( tagData ) ;
	}else{
		throw( AppException( "Unable to fetch RPM release from header" ) ) ;
	}

	result.setFullVersion( epoch , version , release ) ;

	rpmtdFree( tagData ) ;
	Fclose( fileHandle ) ;


	return( new RPM( result ) ) ;

}
