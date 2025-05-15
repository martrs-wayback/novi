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

#include<RPMInfoHandler.h>
#include<AppException.h>
#include<AttributeMap.h>
#include<TagStack.h>

#include<string>
#include<cstdlib> // atoi()

#include<sstream>

// - - - - - - - - - - - - - - - - - - - -

RPMInfoHandler::RPMInfoHandler( const std::string basePath , ProductList& products )
	:
	basePath_( basePath ) ,
	products_( products ) ,
	tags_() ,
	buf_() ,
	currentRPM_( NULL )
{

	return ;

} // ctor


RPMInfoHandler::~RPMInfoHandler() throw() {

	return ;

} // dtor


void RPMInfoHandler::startElement( const XML_Char* name , const XML_Char** attrs ) {

	tags_.pushTag( name ) ;

	switch( tags_.currentTag() ){

		case TagStack::TAG_METADATA_package:
			{
				currentRPM_ = new RPM() ;
			}
			break ;

		case TagStack::TAG_METADATA_name:
			// do nothing
			break ;

		case TagStack::TAG_METADATA_version:
			{

				AttributeMap attrMap( attrs ) ;

				int epoch ;
				if( NULL == attrMap.getValue( "epoch" ) ){
					epoch = 0 ;
				}else{
					epoch = atoi( attrMap.getValue( "epoch" ) ) ;
				}

				currentRPM_->setFullVersion(
					epoch ,
					attrMap.getValue( "ver" ) ,
					attrMap.getValue( "rel" )
				) ;

			}
			break ;

		case TagStack::TAG_METADATA_location:
			{

				AttributeMap attrMap( attrs ) ;

				// QQQ: create shared version of the stringstream
				std::ostringstream locationBuf ;
				locationBuf << basePath_ << "/" << attrMap.getValue( "href" ) ;
				currentRPM_->setFile( locationBuf.str() ) ;

			}
			break ;

	} // switch( tags_.currentTag() )

	return ;

} // RPMInfoHandler::startElement()



void RPMInfoHandler::endElement( const XML_Char* name ) {

	switch( tags_.currentTag() ){

		case TagStack::TAG_METADATA_package:
			{
				products_.add( currentRPM_ ) ;
				currentRPM_ = NULL ;
			}
			break ;

		case TagStack::TAG_METADATA_version:
		case TagStack::TAG_METADATA_location:
			// nothing
			break ;

		case TagStack::TAG_METADATA_name:
			{
				currentRPM_->setName( buf_.str() ) ;
				buf_.str( "" ) ;
			}
			break ;

		case TagStack::TAG_METADATA_arch:
			{
				currentRPM_->setArch( buf_.str() ) ;
				buf_.str( "" ) ;
			}
			break ;

	} // switch( tags_.currentTag() )

	tags_.popTag() ;

	return ;

} // RPMInfoHandler::endElement()

void RPMInfoHandler::characters( const XML_Char* buf , int len ) {

	switch( tags_.currentTag() ){

		case TagStack::TAG_METADATA_package:
		case TagStack::TAG_METADATA_version:
		case TagStack::TAG_METADATA_location:
			// nothing
			break ;


		case TagStack::TAG_METADATA_arch:
			buf_.write( buf , len ) ;
		break ;

		case TagStack::TAG_METADATA_name:
			buf_.write( buf , len ) ;
		break ;

	} // switch( tags_.currentTag() )

	return ;

} // RPMInfoHandler::characters()


// - - - - - - - - - - - - - - - - - - - -

