#ifndef RPMSOURCE_H
#define RPMSOURCE_H

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
#include<ProductList.h>

// - - - - - - - - - - - - - - - - - - - - 

class RPMSource {

	public:
	virtual ~RPMSource() throw() {} 

	virtual void load( ProductList& pl ) throw( AppException ) = 0 ;

	// QQQ: coming soon...
	// virtual size_t size() const throw() = 0 ;
	//    (use "-1" to indicate size is incalculable,
	//     such as with dynamically-generated lists?
	//     or, given that possibility, is it even
	//     worth having such an operation here?)

} ; // class RPMSource

// - - - - - - - - - - - - - - - - - - - - 

#endif // #ifndef RPMSOURCE_H
