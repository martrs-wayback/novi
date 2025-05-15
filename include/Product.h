#ifndef PRODUCT_H
#define PRODUCT_H

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
#include<RPM.h>
#include<set>
#include<string>

typedef std::set< const RPM* , RPMLess > RPMList ;

class Product {

	private:
	const std::string id_ ; // name + architecture
	RPMList list_ ;
	const RPM* latest_ ;

	protected:
	/* empty */

	public:
	Product( const std::string& inId ) ;
	~Product() throw() ;

	void push( const RPM* obj ) ;

	const std::string& getId() const throw() ;

	int size() const throw() ;

	bool empty() const throw() ;

	const RPM* latestVersion() const throw() ;

} ; // class Product

// - - - - - - - - - - - - - - - - - - - - 

#endif // #ifndef PRODUCT_H
