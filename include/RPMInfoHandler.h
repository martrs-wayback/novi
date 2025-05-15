#ifndef RPMINFOHANDLER_H
#define RPMINFOHANDLER_H

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

#include<sstream>
#include<string>

#include<TagStack.h>
#include<ProductList.h>

extern "C" {
	#include<expat.h>
}

class RPMInfoHandler {

	public:
	RPMInfoHandler( const std::string basePath , ProductList& products ) ;

	~RPMInfoHandler() throw() ;

	void startElement( const XML_Char* name , const XML_Char** attrs ) ;

	void endElement( const XML_Char* name ) ;

	void characters( const XML_Char* buf , int len ) ;


	protected:

	// empty


	private:
	const std::string basePath_ ;
	ProductList& products_ ;
	TagStack tags_ ;
	std::ostringstream buf_ ;
	RPM* currentRPM_ ;

} ; // struct RPMInfoHandler

// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef RPMINFOHANDLER_H
