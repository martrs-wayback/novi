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

#include<TagStack.h>

#include<stack>
#include<cstring>

// - - - - - - - - - - - - - - - - - - - -

const char* const TagStack::TAGNAME_METADATA_package = "http://linux.duke.edu/metadata/common:package" ;
const char* const TagStack::TAGNAME_METADATA_name = "http://linux.duke.edu/metadata/common:name" ;
const char* const TagStack::TAGNAME_METADATA_arch = "http://linux.duke.edu/metadata/common:arch" ;
const char* const TagStack::TAGNAME_METADATA_version = "http://linux.duke.edu/metadata/common:version" ;
const char* const TagStack::TAGNAME_METADATA_location = "http://linux.duke.edu/metadata/common:location" ;

const char* const TagStack::TAGNAME_REPOMD_revision = "http://linux.duke.edu/metadata/repo:revision" ;
const char* const TagStack::TAGNAME_REPOMD_data = "http://linux.duke.edu/metadata/repo:data" ;
const char* const TagStack::TAGNAME_REPOMD_location = "http://linux.duke.edu/metadata/repo:location" ;
const char* const TagStack::TAGNAME_REPOMD_checksum = "http://linux.duke.edu/metadata/repo:checksum" ;
const char* const TagStack::TAGNAME_REPOMD_timestamp = "http://linux.duke.edu/metadata/repo:timestamp" ;
const char* const TagStack::TAGNAME_REPOMD_open_checksum = "http://linux.duke.edu/metadata/repo:open-checksum" ;
const char* const TagStack::TAGNAME_REPOMD_database_version = "http://linux.duke.edu/metadata/repo:database_version" ;


TagStack::TagStack()
	:
	validTagNames_()
{

	validTagNames_[ TAGNAME_METADATA_package ] = TAG_METADATA_package ;
	validTagNames_[ TAGNAME_METADATA_name ] = TAG_METADATA_name ;
	validTagNames_[ TAGNAME_METADATA_arch ] = TAG_METADATA_arch ;
	validTagNames_[ TAGNAME_METADATA_version ] = TAG_METADATA_version ;
	validTagNames_[ TAGNAME_METADATA_location ] = TAG_METADATA_location ;
	validTagNames_[ TAGNAME_REPOMD_data ] = TAG_REPOMD_data ;
	validTagNames_[ TAGNAME_REPOMD_location ] = TAG_REPOMD_location ;
	validTagNames_[ TAGNAME_REPOMD_checksum ] = TAG_REPOMD_checksum ;
	validTagNames_[ TAGNAME_REPOMD_timestamp ] = TAG_REPOMD_timestamp ;
	validTagNames_[ TAGNAME_REPOMD_open_checksum ] = TAG_REPOMD_open_checksum ;
	validTagNames_[ TAGNAME_REPOMD_database_version ] = TAG_REPOMD_database_version ;

}

void TagStack::pushTag( const char* name ) {

	InternalMap::iterator found = validTagNames_.find( name ) ;

	if( found != validTagNames_.end() ){
		stack_.push( found->second ) ;
	}else{
		stack_.push( UNKNOWN_TAG ) ;
	}

} // TagStack::pushTag()


void TagStack::popTag() throw() {

	stack_.pop() ;
	return ;

} // TagStack::popTag()


int TagStack::currentTag() throw() {

	return( stack_.top() ) ;

} // TagStack::currentTag()

// - - - - - - - - - - - - - - - - - - - -

