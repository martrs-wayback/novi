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

#include<RepodataRPMSource.h>
#include<RPMInfoHandler.h>
#include<GzipInputStream.h>
#include<RepoMDParser.h>

#include<sstream>
#include<string>

extern "C" {
	#include<expat.h>
}

// catching differences in Expat lib versions
// (pulled from note in expat.h)

#ifndef XML_STATUS_OK
   #define XML_STATUS_OK    1
   #define XML_STATUS_ERROR 0
#endif

// - - - - - - - - - - - - - - - - - - - -

RepodataRPMSource::RepodataRPMSource( const std::string& basePath )
	:
	basePath_( basePath )
{

	return ;

} // RepodataRPMSource::ctor


// TEMP
#include<iostream>
void RepodataRPMSource::load( ProductList& pl ) throw( AppException ) {

	// first, parse "repodata/repomd.xml" to find location of primary file
	// (sometimes it is just "primary.xml.gz"; but the name may also include
	//  the files checksum.  Using repomd.xml, we don't have to guess)
	std::ostringstream repoMDPath ;
	repoMDPath << basePath_ << "/repodata/repomd.xml" ;


	RepoMDSet mdSet = RepoMDParser().read( repoMDPath.str() ) ;
	RepoMDItem primaryItem = mdSet.getValue( "primary" ) ;

	std::ostringstream sourceFile ;
	sourceFile << basePath_ << "/" << primaryItem.getLocation() ;

	// then, load the data from the "primary" file specified in repomd.xml

	// QQQ: check that sourceFile_ is readable here
	GzipInputStream xml( sourceFile.str() ) ;

	if( ! xml.good() ){

		std::ostringstream message ;
		message << "Problem loading file \""
			<< sourceFile
			<< "\""
		;
		throw( AppException( message.str() ) ) ;

	}


	const int BUFFER_SIZE = 20480 ;
	char readBuf[ BUFFER_SIZE ] ;

	XML_Parser parser = XML_ParserCreateNS( "UTF-8" , ':' );

	RPMInfoHandler* state = new RPMInfoHandler( basePath_ , pl ) ;
	XML_SetUserData( parser , state );

	XML_SetStartElementHandler( parser , HandlerFrame< RPMInfoHandler >::startElement ) ;
	XML_SetEndElementHandler( parser , HandlerFrame< RPMInfoHandler >::endElement ) ;
	XML_SetCharacterDataHandler( parser , HandlerFrame< RPMInfoHandler >::characters ) ;

	int charsRead ;

	do {

		charsRead = xml.readsome( readBuf , BUFFER_SIZE ) ;

		// QQQ: log
		// std::cout << "{read: " << charsRead << " chars}" << std::endl ;

		if ( XML_STATUS_OK != XML_Parse( parser , readBuf , charsRead , NOT_DONE_YET ) ){

			std::ostringstream error ;

			error << "XML parse problem: line " << XML_GetCurrentLineNumber( parser ) << ", "
				<< "column " << XML_GetCurrentColumnNumber( parser )
				<< " (character index " << XML_GetCurrentByteIndex( parser ) << "): "
				<< XML_ErrorString( XML_GetErrorCode( parser ) )
				<< std::flush 
			;

			throw( AppException( error.str() ) ) ;
      		break ;

		}

	} while(
		BUFFER_SIZE == charsRead
			&&
		xml.good()
	) ;


	XML_ParserFree( parser ) ;

} // RepodataRPMSource::load()




