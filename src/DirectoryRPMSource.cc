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

#include<DirectoryRPMSource.h>
#include<ProductList.h>
#include<RPMFileReader.h>

#include<functional>
#include<algorithm>

DirectoryRPMSource::DirectoryRPMSource( const std::string& dir )
	throw( AppException )
	:
	glob_() ,
	fileReader_()
{

	std::ostringstream buf ;

	// QQQ: catch exception
	buf << dir << "/*.rpm" << std::flush ;
	glob_.push_back( buf.str() ) ;

	// QQQ: log size of glob expansion list
	return ;

} // DirectoryRPMSource::ctor

void DirectoryRPMSource::load( ProductList& pl )
	throw( AppException )
{

//	std::for_each(
//		glob_.begin() ,
//		glob_.end() ,
//		std::bind1st(
//			std::mem_fun< void , ProductList , std::string >( &ProductList::add ) ,
//			&pl
//		)
//	) ;

	for(
		GlobObj::iterator
			ix = glob_.begin() ,
			stop = glob_.end()
		;
		ix != stop ;
		++ix
	){
		// QQQ: LOG -- std::cout << "Glob item: " << (*ix) << std::endl ;

		/*
		QQQ: take a "fail-on-any-error" flag from commandline?
		The exception doesn't leave this function...

		Perhaps this exception should be propogated up the stack
		such that something closer to main() (ergo, something closer
		to AppConfig) can find it.
		*/



		try{
			const RPM* rpm = fileReader_.load( (*ix) ) ;
			pl.add( rpm ) ;
		}catch( AppException& e ){
			std::cerr << "  ** problem loading \"" << (*ix) << "\": " << e.what() << std::endl ;

			// sic -- we swallow the exception here because we shouldn't let one
			// bad file throw off the entire operation
		}

}

	return ;

} // DirectoryRPMSource::load()

// - - - - - - - - - - - - - - - - - - - -
