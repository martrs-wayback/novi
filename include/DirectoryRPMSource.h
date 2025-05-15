#ifndef DIRECTORYRPMSOURCE_H
#define DIRECTORYRPMSOURCE_H

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

#include<AppException.h>
#include<GlobObj.h>
#include<ProductList.h>
#include<RPMSource.h>
#include<RPMFileReader.h>

class DirectoryRPMSource : public RPMSource {

	public:
	DirectoryRPMSource( const std::string& dir ) throw( AppException ) ;
	virtual ~DirectoryRPMSource() throw() {} 

	void load( ProductList& pl ) throw( AppException ) ;

	protected:
	// empty

	private:
	GlobObj glob_ ;
	RPMFileReader fileReader_ ;

} ; // class DirectoryRPMSource

// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef DIRECTORYRPMSOURCE_H
