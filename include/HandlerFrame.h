#ifndef HANDLERFRAME_H
#define HANDLERFRAME_H

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

extern "C" {
	#include<expat.h>	// QQQ: autoconf
}

/*
We can't set non-static member functions as handlers,
so we don't get all the benefits of a true, intelligent
object; but to group all related handler functions into
a single struct makes for easy reference and prevents
name clashes.
*/

template< typename T >
struct HandlerFrame {

	static void startElement( void* userData , const XML_Char* name , const XML_Char** attrs ) {

		T* realHandler = static_cast< T* >( userData ) ;
		realHandler->startElement( name , attrs ) ;
		return ;

	} // startElement()


	static void endElement( void* userData , const XML_Char* name ) {

		T* realHandler = static_cast< T* >( userData ) ;
		realHandler->endElement( name ) ;
		return ;

	} // endElement()


	static void characters( void* userData , const XML_Char* buf , int len ) {

		T* realHandler = static_cast< T* >( userData ) ;
		realHandler->characters( buf , len ) ;
		return ;

	} // characters()

} ; // class HandlerFrame

// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef HANDLERFRAME_H
