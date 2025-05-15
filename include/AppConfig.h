#ifndef APPCONFIG_H
#define APPCONFIG_H

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


#include<string>
#include<vector>

extern "C" {
	#include<popt.h>
}

#include<GlobObj.h>
#include<RPMSourceDescription.h>
#include<list>

// QQQ: const
typedef std::list< RPMSourceDescription > PathList ;
class AppConfig {

	public:

	enum { FLAG_TARGET_DIR = 1 , FLAG_ACTION , FLAG_HELP , FLAG_VERBOSE , FLAG_VERSION } ;

	/// fetch a reference to the singleton instance
	static AppConfig& getInstance() throw() ;

	static const std::string DEFAULT_OUTPUT_TYPE ;

	/// basic constructor -- real work is done by load()
	AppConfig() ;

	/// basic dtor
	~AppConfig() throw() ;

	/**
	\brief loads the object with commandline args, to pass to popt

	\param argc argument count
	\param argv list of arguments
	\param optArgs array of poptOption structures to be passed to popt functions
	*/
	void load( int argc , const char** argv , const struct poptOption* optArgs ) throw( /* exception */ ) ;


	/// return the popt context, for use with popt helper functions
	poptContext getContext() const throw() ;

	/// was the "help" flag passed on the commandline?
	bool showHelp() const throw() ;

	/// was the "version" flag passed on the commandline?
	bool showVersion() const throw() ;

	/// return the list of source directories (which contain RPMs)
	const PathList& getSourceDirs() const throw() ;

	/// return the target directory
	const std::string& getTargetDir() const throw() ;

	/// was the target dir set? (it has no default)
	bool isTargetDirSet() const throw() ;

	/// show verbose output?
	bool isVerbose() const throw() ;
	
	/// return the output type
	const std::string& getActionType () const throw() ;

	protected:
	/* empty */

	private:
	static AppConfig instance_ ;

	poptContext ctx_ ;
	PathList sourceDirs_ ;
	std::string targetDir_ ;
	bool isTargetDirSet_ ;
	std::string actionType_ ;
	bool showHelp_ ;
	bool showVersion_ ;
	bool isVerbose_ ;

	/// calls popt processing
	void initpopt() throw( /* exception */ ) ;

	AppConfig( const AppConfig& ) ; // not implemented
	AppConfig& operator=( const AppConfig& ) ; // not implemented

} ; // class AppConfig

// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef APPCONFIG_H
