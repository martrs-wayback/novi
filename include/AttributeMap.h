#ifndef ATTRIBUTEMAP_H
#define ATTRIBUTEMAP_H

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

#include<map>
#include<string>

/*
NOTE: using std::string because we'd otherwise have
to strdup() the const char* passed in by Expat.  Who's
to say that Expat isn't (or won't ever) recycle a char
buf for attr values?  
*/

typedef std::map< const std::string , const std::string > AttributeMapType ;
typedef AttributeMapType::value_type AttributeMapEntry ;

class AttributeMap {

	private:
	AttributeMapType map_ ;

	protected:
	// none

	public:

	AttributeMap( const char** values ) throw() ;

	const char* getValue( const char* key ) throw() ;

	bool hasKey( const char* key ) ;

} ; // class AttributeMap


// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef ATTRIBUTEMAP_H
