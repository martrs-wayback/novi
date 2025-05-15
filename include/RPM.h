#ifndef RPM_H
#define RPM_H

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

#include<string>

class RPM {

	private:
	/// file name of package
	std::string file_ ;

	/// internal package name (based on RPM metadata)
	std::string name_ ;

	/// package architecture (based on RPM metadata)
	std::string arch_ ;

	/// package epoch (based on RPM metadata)
	int epoch_ ;

	/// package version (based on RPM metadata)
	std::string version_ ;

	/// package release (based on RPM metadata)
	std::string release_ ;

	/// string format of RPM's  "{epoch}:{version}-{release}"
	std::string fullVersion_ ;

	/// is this a source RPM?
	bool isSourcePackage_ ;

	protected:
	/* empty */

	public:

	RPM() ;
	RPM( const RPM& other ) ;

	const std::string& getFile() const throw() ;
	void setFile( const std::string& file ) ;

	const std::string& getName() const throw() ;
	void setName( const std::string& name ) ;

	const std::string& getArch() const throw() ;
	void setArch( const std::string& arch ) ;

	int getEpoch() const throw() ;
	// sic -- no mutator (set in setFullVersion())

	const std::string& getVersion() const throw() ;
	// sic -- no mutator (set in setFullVersion())

	const std::string& getRelease() const throw() ;
	// sic -- no mutator (set in setFullVersion())

	const std::string& getFullVersion() const throw() ;
	void setFullVersion( const int epoch , const std::string& version , const std::string& release ) ;

	const bool isSourcePackage() const throw() ;

	void print( std::ostream& s ) const ;

} ; // class RPM


/**
\brief print RPM objects
*/
std::ostream& operator<<( std::ostream& s , const RPM& obj ) ;


/**
\brief used to compare two RPMs, by version
*/

#include<functional>

struct RPMLess
	: public std::binary_function< const RPM& , const RPM& , bool>
{

	public:
	/*
	Code equivalent of the question:
			rpmLeft < rpmRight
	result of "true" => rpmLeft is older
	result of "false" => rpmLeft is newer
	*/
	bool operator()( const RPM* rpmLeft , const RPM* rpmRight ) const throw() ;

	/*
	The key comparison function, a Strict Weak Ordering whose argument type is
	key_type; it returns true if its first argument is less than its second
	argument, and false otherwise.
	*/

	private:
	static const bool LEFT_IS_NEWER_ = false ;
	static const bool LEFT_IS_OLDER_ = true ;

} ; // struct RPMLess



// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef RPM_H
