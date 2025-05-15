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

#include<string>
#include<RepoMDParser.h>

RepoMDItem::RepoMDItem()
	:
	type_() ,
	checksumType_() ,
	checksumValue_() ,
	openChecksumType_() ,
	openChecksumValue_() ,
	location_ () ,
	timestamp_(0) ,
	databaseVersion_(0)
{
}

const std::string& RepoMDItem::getChecksumType() const {
	return checksumType_;
}

void RepoMDItem::setChecksumType( const std::string& checksumType ){
	checksumType_ = checksumType ;
}


const std::string& RepoMDItem::getChecksumValue() const {
	return checksumValue_;
}

void RepoMDItem::setChecksumValue( const std::string& checksumValue ){
	checksumValue_ = checksumValue ;
}


long RepoMDItem::getDatabaseVersion() const {
	return databaseVersion_;
}

void RepoMDItem::setDatabaseVersion(long  databaseVersion ) {
	databaseVersion_ = databaseVersion ;
}


const std::string& RepoMDItem::getOpenChecksumValue() const {
	return openChecksumValue_;
}

void RepoMDItem::setOpenChecksumValue( const std::string& openChecksumValue ) {
	openChecksumValue_ = openChecksumValue ;
}


const std::string& RepoMDItem::getOpenChecksumType() const {
	return openChecksumType_;
}

void RepoMDItem::setOpenChecksumType( const std::string& openChecksumType ) {
	openChecksumType_ = openChecksumType ;
}

const std::string& RepoMDItem::getLocation() const {
	return location_ ;
}

void RepoMDItem::setLocation( const std::string& location ){
	location_ = location ;
}


long RepoMDItem::getTimestamp() const {
	return timestamp_;
}

void RepoMDItem::setTimestamp(long  timestamp ){
	timestamp_ = timestamp ;
}


const std::string& RepoMDItem::getType() const {
	return type_;
}

void RepoMDItem::setType( const std::string& type ){
	type_ = type ;
}

// - - - - - - - - - - - - - - - - - - - -

#include<map>
#include<string>
#include<RepoMDParser.h>
#include<sstream>

RepoMDSet::RepoMDSet()
:
values_()
{
	return ;
}

bool RepoMDSet::isDefined( const std::string key ) const {

	bool result = false ;
	InternalMap::const_iterator found = values_.find( key ) ;

	if( found != values_.end() ){
		result = true ;
	}

	return( result ) ;

}

const RepoMDItem& RepoMDSet::getValue( const std::string key ) const {

	if( ! isDefined( key ) ){
		std::ostringstream message ;
		message << "Invalid key for RepoDItem: '" << key << "'" ;
		message.flush() ;
		throw( std::invalid_argument( message.str() ) ) ;
	}

	InternalMap::const_iterator found = values_.find( key ) ;

	return( found->second ) ;

}

void RepoMDSet::addValue( const RepoMDItem& item ) {

	const std::string& key = item.getType() ;
	values_[ key ] = item ;

}

// - - - - - - - - - - - - - - - - - - - -



#include<RepoMDParser.h>
#include<AppException.h>
#include<AttributeMap.h>
#include<TagStack.h>

#include<sstream>
#include<string>
#include<cstdlib> // atol()


extern "C" {
	#include<expat.h>
}


RepoMDHandler::RepoMDHandler( RepoMDSet& set )
	:
	set_( set ),
	tags_() ,
	buf_() ,
	currentItem_( NULL )
{
	return ;
}


RepoMDHandler::~RepoMDHandler() throw() {

	return ;

} // dtor

void RepoMDHandler::startElement( const XML_Char* name , const XML_Char** attrs ) {

	tags_.pushTag( name ) ;

	switch( tags_.currentTag() ){

		case TagStack::TAG_REPOMD_data:
			{
				currentItem_ = new RepoMDItem() ;
				AttributeMap attrMap( attrs ) ;
				currentItem_->setType( attrMap.getValue( "type" ) ) ;

			}
			break ;

		case TagStack::TAG_REPOMD_location:
			{
				AttributeMap attrMap( attrs ) ;
				currentItem_->setLocation( attrMap.getValue( "href" ) ) ;
			}
			break ;

		case TagStack::TAG_REPOMD_checksum:
			{
				AttributeMap attrMap( attrs ) ;
				currentItem_->setChecksumType( attrMap.getValue( "type" ) ) ;
			}
			break ;

		case TagStack::TAG_REPOMD_timestamp:
			// nothing
			break ;

		case TagStack::TAG_REPOMD_open_checksum:
			{
				AttributeMap attrMap( attrs ) ;
				currentItem_->setOpenChecksumType( attrMap.getValue( "type" ) ) ;
			}
			break ;


		case TagStack::TAG_REPOMD_database_version:
			// nothing
			break ;

	} // switch( tags_.currentTag() )

	return ;

} // RepoMDHandler::startElement()


void RepoMDHandler::endElement( const XML_Char* name ) {

	switch( tags_.currentTag() ){

		case TagStack::TAG_REPOMD_data:
			{
				set_.addValue( *currentItem_ ) ;
				delete( currentItem_ ) ;

			}
			break ;

		case TagStack::TAG_REPOMD_location:
			// nothing
			break ;

		case TagStack::TAG_REPOMD_checksum:
			{
				currentItem_->setChecksumValue( buf_.str() ) ;
				buf_.str( "" ) ;
			}
			break ;

		case TagStack::TAG_REPOMD_timestamp:
			{

				const std::string tempString( buf_.str() ) ;
				if( "" == tempString ){
					currentItem_->setTimestamp( 0 ) ;
				}else{
					currentItem_->setTimestamp( atol( tempString.c_str() ) ) ;
				}
				buf_.str( "" ) ;

			}
			break ;

		case TagStack::TAG_REPOMD_open_checksum:

			{

				currentItem_->setOpenChecksumValue( buf_.str() ) ;
				buf_.str( "" ) ;

			}
			break ;

		case TagStack::TAG_REPOMD_database_version:

			{

				const std::string tempString( buf_.str() ) ;
				if( "" == tempString ){
					currentItem_->setDatabaseVersion( 0 ) ;
				}else{
					currentItem_->setDatabaseVersion( atol( tempString.c_str() ) ) ;
				}
				buf_.str( "" ) ;

			}
			break ;

	} // switch( tags_.currentTag() )

	tags_.popTag() ;

	return ;

} // RepoMDHandler::endElement()

void RepoMDHandler::characters( const XML_Char* buf , int len ) {

	switch( tags_.currentTag() ){

		case TagStack::TAG_REPOMD_data:
			// nothing
			break ;

		case TagStack::TAG_REPOMD_location:
			// nothing
			break ;

		case TagStack::TAG_REPOMD_checksum:
			buf_.write( buf , len ) ;
			break ;

		case TagStack::TAG_REPOMD_timestamp:
			buf_.write( buf , len ) ;
			break ;

		case TagStack::TAG_REPOMD_open_checksum:
			buf_.write( buf , len ) ;
			break ;

		case TagStack::TAG_REPOMD_database_version:
			buf_.write( buf , len ) ;
			break ;

	} // switch( tags_.currentTag() )

	return ;

} // RepoMDHandler::characters()

// - - - - - - - - - - - - - - - - - - - -

#include<HandlerFrame.h>
#include<AppException.h>
#include<RepoMDParser.h>

#include<string>
#include<sstream>
#include<fstream>
extern "C" {
	#include<expat.h>
}

// catching differences in Expat lib versions
// (pulled from note in expat.h)

#ifndef XML_STATUS_OK
   #define XML_STATUS_OK    1
   #define XML_STATUS_ERROR 0
#endif

const RepoMDSet RepoMDParser::read( const std::string& file ) throw( AppException ) {

	RepoMDSet result ;

	std::ifstream xml ;
	xml.open( file.c_str() ) ;


	if( ! xml.good() ){

		std::ostringstream message ;
		message << "Problem loading file \""
			<< file
			<< "\""
		;
		throw( AppException( message.str() ) ) ;

	}

	const int BUFFER_SIZE = 20480 ;
	char readBuf[ BUFFER_SIZE ] ;

	XML_Parser parser = XML_ParserCreateNS( "UTF-8" , ':' );

	RepoMDHandler* state = new RepoMDHandler( result ) ;
	XML_SetUserData( parser , state );

	XML_SetStartElementHandler( parser , HandlerFrame<RepoMDHandler>::startElement ) ;
	XML_SetEndElementHandler( parser , HandlerFrame<RepoMDHandler>::endElement ) ;
	XML_SetCharacterDataHandler( parser , HandlerFrame<RepoMDHandler>::characters ) ;

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
	xml.close() ;

	return( result ) ;
}


// - - - - - - - - - - - - - - - - - - - -

