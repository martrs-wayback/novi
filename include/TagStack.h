#ifndef TAGSTACK_H
#define TAGSTACK_H

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

#include<stack>
#include<cstring>
#include<map>

// because we need to compare against C-style strings, as passed in by Expat
struct CStringCompare {

	bool operator()( const char* leftSide , const char* rightSide ) const {
		bool result = strcmp(leftSide, rightSide) < 0;
		return( result ) ;
	}

};

class TagStack {

	public:

	enum Tag {

		TAG_METADATA_package = 1 ,
		TAG_METADATA_name ,
		TAG_METADATA_arch ,
		TAG_METADATA_version ,
		TAG_METADATA_location ,

		TAG_REPOMD_data ,
		TAG_REPOMD_location ,
		TAG_REPOMD_checksum ,
		TAG_REPOMD_timestamp ,
		TAG_REPOMD_open_checksum ,
		TAG_REPOMD_database_version ,

		UNKNOWN_TAG

	} ;

	TagStack() ;

	void pushTag( const char* name ) ;

	void popTag() throw() ;

	int currentTag() throw() ;


	protected:
	// empty


	private:

	std::stack< unsigned int > stack_ ;


	typedef std::map< const char* , Tag , CStringCompare > InternalMap ;
	InternalMap validTagNames_ ;

	// tags for repo "primary" metadata file
	static const char* const TAGNAME_METADATA_package ;
	static const char* const TAGNAME_METADATA_name ;
	static const char* const TAGNAME_METADATA_arch ;
	static const char* const TAGNAME_METADATA_version ;
	static const char* const TAGNAME_METADATA_location ;

	// tags for "repomd" file
	static const char* const TAGNAME_REPOMD_revision ;
	static const char* const TAGNAME_REPOMD_data ;
	static const char* const TAGNAME_REPOMD_location ;
	static const char* const TAGNAME_REPOMD_checksum ;
	static const char* const TAGNAME_REPOMD_timestamp ;
	static const char* const TAGNAME_REPOMD_open_checksum ;
	static const char* const TAGNAME_REPOMD_database_version ;


} ; // class TagStack

// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef TAGSTACK_H
