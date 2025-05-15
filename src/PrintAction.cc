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

#include<RPM.h>
#include<Action.h>
#include<PrintAction.h>

#include<iostream>

// - - - - - - - - - - - - - - - - - - - -

bool PrintAction::operator()( const Product& product )
	throw()
{

	const RPM* rpm = product.latestVersion() ;

	std::cout << rpm->getName() << "\t" <<
		*rpm << "\t"
		<< rpm->getFile() << std::endl
	;

	return( true ) ;

} // PrintAction::operator()()

// - - - - - - - - - - - - - - - - - - - -
