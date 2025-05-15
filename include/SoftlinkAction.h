#ifndef SOFTLINKACTION_H
#define SOFTLINKACTION_H

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

#include<Action.h>
#include<SoftlinkAction.h>
#include<Product.h>

#include<string>
#include<sstream>

class SoftlinkAction : public Action {

	public:
	SoftlinkAction( const std::string& path ) ;
	~SoftlinkAction() throw() {}
	bool operator()( const Product& product ) throw() ;

	protected:
	/* empty */

	private:
	const std::string path_ ;
	std::ostringstream buf_ ;

} ; // class SoftlinkAction

// - - - - - - - - - - - - - - - - - - - - 

#endif // #ifndef SOFTLINKACTION_H
