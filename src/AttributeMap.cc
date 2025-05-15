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

#include<AttributeMap.h>

// - - - - - - - - - - - - - - - - - - - -
#include<map>
#include<string>

/*
NOTE: using std::string because we'd otherwise have
to strdup() the const char* passed in by Expat.  Who's
to say that Expat isn't (or won't ever) recycle a char
buf for attr values?  
*/

AttributeMap::AttributeMap( const char** values ) throw() {

	while( *values != NULL ){

		map_.insert( AttributeMapEntry( values[0] , values[1] ) ) ;

		values += 2 ;
	}

	return ;

} // AttributeMap::ctor

const char* AttributeMap::getValue( const char* key ) throw() {
	if( hasKey( key ) ){
		return( map_[ key ].c_str() ) ;
	} else {
		return( NULL ) ;
	}

} // getValue()

bool AttributeMap::hasKey( const char* key ){

	if( map_.find( key ) != map_.end() ){
		return( true ) ;
	} else {
		return( false ) ;
	}

} // AttributeMap::hasKey()

// - - - - - - - - - - - - - - - - - - - -
