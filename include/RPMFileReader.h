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

#ifndef RPMFILEREADER_H_
#define RPMFILEREADER_H_

#include<AppException.h>
#include<RPM.h>

#include <rpm/rpmts.h>

class RPMFileReader {

	public:

	RPMFileReader() ;
	~RPMFileReader() ;
	const RPM* load( const std::string& path ) throw( AppException ) ;

	private:
	rpmts rpmTransactionSet_ ;

};

#endif /* RPMFILEREADER_H_ */
