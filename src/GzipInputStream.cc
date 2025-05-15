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

#include<GzipInputStream.h>
#include<AppException.h>

#include<string>
#include<cstring> // strerror()
#include<sstream>

// - - - - - - - - - - - - - - - - - - - -

GzipInputStream::GzipInputStream( const std::string& inSource ) throw( AppException )
	:
	source_( inSource ) ,
	archive_() ,
	eof_( false ) ,
	goodState_( true )
{

	archive_ = gzopen( inSource.c_str() , "rb" ) ;

	if( NULL == archive_ ){

		std::ostringstream buf ;

		if( 0 == errno ){ // zlib problem

			buf << "zlib reports a memory error for file \"" << inSource << "\"" << std::flush ;

			throw( AppException( buf.str() ) ) ;

		} else {

			buf << "\"" << inSource << "\": " << strerror( errno ) << std::flush ;
			throw( AppException( buf.str() ) ) ;

		}

	}
	
} // GzipInputStream::ctor


GzipInputStream::~GzipInputStream() throw() {

	if( NULL != archive_ ){
		gzclose( archive_ ) ;
	}

} // GzipInputStream::dtor


std::streamsize GzipInputStream::readsome( char* buf , std::streamsize len ){

	// QQQ: check good() and eof()

	/*  int gzread (gzFile file, voidp buf, unsigned len); */
	std::streamsize result = gzread( archive_ , buf , len ) ;

	switch( result ){

		case -1:	// error
			eof_ = true ;
			goodState_ = false ;
			/*  const char * gzerror (gzFile file, int *errnum); */
			break ;

		case 0:	// EOF
			eof_ = true ;
			break ;

		default:	// successful read
			// QQQ: log
			// std::cout << "read " << readThisTime << " bytes" << std::endl ;
		
			break ;

	} // switch( result )

	return( result ) ;

} // GzipInputStream::readSome()

bool GzipInputStream::good(){
	return( goodState_ ) ; // QQQ: rework so logic flows better
} // GzipInputStream::good()

bool GzipInputStream::eof(){
	return( eof_ ) ;
} // GzipInputStream::eof()

// - - - - - - - - - - - - - - - - - - - -

