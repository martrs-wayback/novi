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


#include<iostream>
#include<cstdio> // fflush()
#include<string>
#include<sstream>
#include<list>
#include<algorithm>
#include<functional>

#include<NoviInfo.h>
#include<AppConfig.h>
#include<GlobObj.h>
#include<RPMSource.h>
#include<RPM.h>
#include<DirectoryRPMSource.h>
#include<RepodataRPMSource.h>
#include<ProductList.h>
#include<Action.h>
#include<HardlinkAction.h>
#include<SoftlinkAction.h>
#include<PrintAction.h>
#include<Product.h>
#include<main.h>

// - - - - - - - - - - - - - - - - - - - -

AppConfig& conf = AppConfig::getInstance() ;

Action* action = NULL ;

// program info
const NoviInfo noviInfo ;

enum {
	SUCCESS ,
	ERROR_CHECK_CONFIG ,
	ERROR_NO_FILES
} ;

// QQQ - enum of return values

// - - - - - - - - - - - - - - - - - - - -

void showVersion(){
    
    std::cout << noviInfo.getProductFullDescription() << std::endl ;
    return ;
    
}
// - - - - - - - - - - - - - - - - - - - -

void showUsage(){

        std::cout << noviInfo.getProductFullDescription() << "\n\n" ;

       	std::fflush( stdout ) ;

	poptPrintHelp( conf.getContext() , stdout , 0 );

	std::fflush( stdout ) ;

	std::cout << "Pass a list of RPM source directories as the last arguments." << '\n'
		<< "For example:" << '\n'
		<< '\t' << "novi -a hardlink -t /some/dir dir1 dir2 dir3 ..." << '\n'
		<< std::endl
	;
	
	return ;

} // showUsage()

// - - - - - - - - - - - - - - - - - - - -

bool sanityCheck() {

	bool result = true ;

	const std::string actionType = conf.getActionType() ;

	if( conf.getSourceDirs().empty() ){
		std::cerr << "Must specify at least one source directory" << std::endl ;
		result = false ;
	}

	if(
		( actionType == "hardlink" || actionType == "softlink" || actionType == "copy" )
			&&
		! conf.isTargetDirSet()
	){

		std::cerr << "Action type \"" << actionType << "\" requires a target directory" << std::endl ;
		result = false ;
	}

	if( actionType == "list" ){

		action = new PrintAction() ;

	} else if( actionType == "hardlink" ){

		action = new HardlinkAction( conf.getTargetDir() ) ;

	} else if( actionType == "softlink" ){

		action = new SoftlinkAction( conf.getTargetDir() ) ;

	} else if( actionType == "copy" ){

		std::cerr << "Action type \"copy\" hasn't yet been implemented." << std::endl ;
		result = false ;

	} else {
		std::cerr << "Unknown action type: \"" << actionType << "\"" << std::endl ;
		result = false ;
	}

	return( result ) ;

} // sanityCheck()


// - - - - - - - - - - - - - - - - - - - -

/*
wrapper for the Action object.

I could pull the

	bind1st( mem_fun( &Action::operator() ) , action )

trick, but Action::operator() takes references... which leads to the
reference-to-reference problem... which means that's not an option.
*/

void callAction( const Product& product ){

	/*
	QQQ: place the empty() logic here, or
	inside the Action class? 

	Under what circumstances would an Action want
	to report/handle an empty Product container?
	*/

	if( ! product.empty() ){
		(*action)( product ) ;
	}

	return ;
} // callAction()


// - - - - - - - - - - - - - - - - - - - -

extern "C" {
	#include<rpm/rpmlib.h>
}


int main( const int argc , const char **argv ){

	rpmReadConfigFiles( NULL , NULL ) ;

	/*
 	QQQ: turn this into a unit test

	// - - - - - - - - - -

	if( 2 != argc ){
		std::cout << "Usage: " << argv[0] << " {RPM file}" << std::endl ;
		return( 1 ) ;
	}

	RPM testing( argv[1] ) ;

	std::cout << "the roundup: " << std::endl ;
	std::cout << "\t" << testing.getName() << std::endl ;
	std::cout << "\t" << testing.getFullVersion() << std::endl ;
	std::cout << "\t" << testing.getArch() << std::endl ;
	std::cout << "--------------------" << "\n\n" << std::endl ;

	return( 0 ) ;

	// - - - - - - - - - -
	*/

	// extern struct poptOption optArgs[] ;

	conf.load( argc , argv , optArgs ) ;

	if( conf.showHelp() ){
		showUsage() ;
		return( 0 ) ;
	}

	if( conf.showVersion() ){
		showVersion() ;
		return( 0 ) ;
	}


	if( ! sanityCheck() ){
		std::cerr << "\n\n" ;
		showUsage() ;
		return( ERROR_CHECK_CONFIG ) ;
	}

	// load up the ProductList
	ProductList pl ;


	// create the list of target paths..

	for(
		PathList::const_iterator
			ix = conf.getSourceDirs().begin() ,
			stop = conf.getSourceDirs().end() ;
		ix != stop ;
		++ix
	){

		try{

			// QQQ: clean up logic, so we don't have all the duplicate code

			const RPMSourceDescription& sourceDescription( (*ix) ) ;

			std::cout << "Loading RPMs from source " << sourceDescription.getSource() << std::endl ;

			switch( sourceDescription.getType() ){

				// QQQ: rework logic such that we don't have to repeat
				//      blocks of code for valid RPMSource types
				//      (pass RPMSourceDescription to a factory)

				case RPMSourceDescription::TYPE_DIRECTORY:
					{
						DirectoryRPMSource source( sourceDescription.getPath() ) ;
						source.load( pl ) ;
						std::cout << "  Now " << pl.size() << " products loaded" 
							<< " (" << pl.getRPMCount() << " RPMs)" 
							<< std::endl
						;
					}
					break ;

				case RPMSourceDescription::TYPE_REPO_XML:
					{
						RepodataRPMSource source( sourceDescription.getPath() ) ;
						source.load( pl ) ;
						std::cout << "  Now " << pl.size() << " products loaded" 
							<< " (" << pl.getRPMCount() << " RPMs)" 
							<< std::endl
						;

					}
					break ;

				default:
					{
						std::cerr << "Unknown source type for \"" << sourceDescription.getSource() << "\"" << std::endl ;
					}
					break ;

			} // switch( sourceDescription.getType() )
		}catch( const AppException& swallowed ){
			// QQQ: cancel the entire operation because one source fails?
			std::cerr << "error: " << swallowed.what() << std::endl ;
		}

	}

	if( pl.empty() ){
		std::cerr << "No files to process -- nothing to do." << std::endl ;
		return( ERROR_NO_FILES ) ;
	}


	// QQQ: rework to use a custom Status object:
	// - NullStatus: just call ProductList::add()
	// - LineStatus: print one RPM per line
	// - TermStatus: fancy one-line "cycle through" like "createrepo"

	std::cout << "Total " << pl.size() << " products to process, "
		<< "from " << pl.getRPMCount() << " RPMs"
		<< std::endl
	;

	// extract the newest RPM of each product
	std::for_each(
		pl.begin() ,
		pl.end() ,
		callAction
	) ;

	return( 0 ) ;

} // main()

// - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - -

// EOF main.cc
