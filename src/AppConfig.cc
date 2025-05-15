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
#include<string>
#include<list>
#include<cstdlib>

extern "C" {
	#include<popt.h>
}

#include<AppConfig.h>

// QQQ - use a string in main(), pass to popt to
// set defaults
const std::string AppConfig::DEFAULT_OUTPUT_TYPE = "list" ;

AppConfig AppConfig::instance_ ;


AppConfig& AppConfig::getInstance()
	throw()
{

	return( instance_ ) ;

} // AppConfig::getInstance()

AppConfig::AppConfig()
	:
	ctx_() ,
	sourceDirs_() ,
	targetDir_() ,
	isTargetDirSet_( false ) ,
	actionType_( DEFAULT_OUTPUT_TYPE ) ,
	showHelp_( false ) ,
	showVersion_( false ) ,
	isVerbose_( false )
{

	return ;

} // AppConfig::ctor

AppConfig::~AppConfig()
	throw()
{

	poptFreeContext( ctx_ ) ;
	return ;

} // AppConfig::dtor

void AppConfig::load( int argc , const char** argv , const struct poptOption* optArgs )
	throw( /* exception */ )
{

	// clean up the old context, since it is never used
	// (we require default initialization since we're loading
	//  the context object outside of the ctor)
	poptFreeContext( ctx_ ) ;

	ctx_ = poptContext( poptGetContext( NULL , argc , argv , optArgs , 0 ) ) ;
	initpopt() ;
	return ;

} // AppConfig::load

poptContext AppConfig::getContext() const
	throw()
{
	return( ctx_ ) ;
} // AppConfig::getContext()

bool AppConfig::showHelp() const
	throw()
{
	return( showHelp_ ) ;
} // AppConfig::showHelp()

bool AppConfig::showVersion() const
	throw()
{
	return( showVersion_ ) ;
} // AppConfig::showVersion()

const PathList& AppConfig::getSourceDirs() const
	throw()
{
	return( sourceDirs_ ) ;
} // AppConfig::getSourceDirs()

const std::string& AppConfig::getTargetDir() const
	throw()
{
	return( targetDir_ ) ;
} // AppConfig::getTargetDir()

bool AppConfig::isTargetDirSet() const
	throw()
{
	return( isTargetDirSet_ ) ;
} // AppConfig::isTargetDirSet()

const std::string& AppConfig::getActionType() const
	throw()
{
	return( actionType_ ) ;
} // AppConfig::getActionType()

void AppConfig::initpopt()
	throw( /* exception */ )
{


	int rc ; 

	while( -1 != ( rc = poptGetNextOpt( ctx_ ) ) ){

		switch( rc ){

			case FLAG_HELP :
				showHelp_ = true ;
				break ;

			case FLAG_TARGET_DIR:
				targetDir_ = poptGetOptArg( ctx_ ) ;
				isTargetDirSet_ = true ;
				break ;

			case FLAG_ACTION:
				actionType_ = poptGetOptArg( ctx_ ) ;
				break ;

			case FLAG_VERBOSE:
				isVerbose_ = true ;
				break ;
			
			case FLAG_VERSION:
				showVersion_ = true ;
				break ;

			default:
				if( rc < -1 ){

					std::cerr << "popt error: " << poptBadOption( ctx_ , POPT_BADOPTION_NOALIAS )
						<< ": " << poptStrerror( rc )
 						<< std::endl
					;

				} else {
					std::cerr << "unknown flag passed to popt " << rc << std::endl ;
				}

		} // switch( rc )

	} // while( -1 != ( rc = poptGetNextOpt( ctx_ ) ) ){

	// leftover args are source dirs
	
	// NOTE: could have used poptPeekArg here to see whether there were any more
	// args (source dirs); but validation is deferred to another component

	const char* nextArg = NULL ;
	while( NULL != ( nextArg = poptGetArg( ctx_ ) ) ){
		sourceDirs_.push_back( RPMSourceDescription( nextArg ) ) ;
	}


	return ;

} // AppConfig::initpopt()

bool AppConfig::isVerbose() const
	throw()
{
	return( isVerbose_ ) ;
} // AppConfig::isVerbose()


// - - - - - - - - - - - - - - - - - - - -

// EOF AppConfig.cc
