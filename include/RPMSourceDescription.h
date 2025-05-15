#ifndef RPMRESOURCEDESCRIPTION_H
#define RPMRESOURCEDESCRIPTION_H

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

#include<AppException.h>
#include<string>

// - - - - - - - - - - - - - - - - - - - - 

class RPMSourceDescription {

	public:
	enum SourceType {
		TYPE_UNKNOWN ,
		TYPE_DIRECTORY ,
		TYPE_REPO_XML
	} ;

	RPMSourceDescription( const std::string& name ) throw( AppException ) ;

	const std::string& getSource() const throw() ;
	const std::string& getPath() const throw() ;
	SourceType getType() const throw() ;

	protected:
	// empty 

	private:
	std::string source_ ;
	std::string path_ ;
	SourceType type_ ;

} ; // class RPMSourceDescription

// - - - - - - - - - - - - - - - - - - - - 

#endif // #ifndef RPMRESOURCEDESCRIPTION_H
