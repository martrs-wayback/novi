#ifndef REPOMDPARSER_H
#define REPOMDPARSER_H

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

#include<string>

class RepoMDItem {

	public:

	RepoMDItem() ;

	const std::string& getChecksumType() const ;
    void setChecksumType( const std::string& checksumType );

    const std::string& getChecksumValue() const ;
    void setChecksumValue( const std::string& checksumValue );

    long getDatabaseVersion() const ;
    void setDatabaseVersion(long  databaseVersion ) ;


    const std::string& getOpenChecksumType() const ;
    void setOpenChecksumType( const std::string& openChecksumType ) ;

    const std::string& getOpenChecksumValue() const ;
    void setOpenChecksumValue( const std::string& openChecksumValue ) ;

    const std::string& getLocation() const ;
    void setLocation( const std::string& location ) ;

    long getTimestamp() const ;
    void setTimestamp(long  timestamp ) ;


    const std::string& getType() const ;
    void setType( const std::string& type ) ;


	protected:
	// sic -- empty

	private:

    std::string type_;
    std::string checksumType_;
    std::string checksumValue_;
    std::string openChecksumType_;
    std::string openChecksumValue_;
    std::string location_ ;
    long timestamp_;
    long databaseVersion_;

} ; // class RepoMDItem

// - - - - - - - - - - - - - - - - - - - -

#include<map>
#include<string>

class RepoMDSet {

	public:

	RepoMDSet() ;

	bool isDefined( const std::string key ) const ;

	const RepoMDItem& getValue( const std::string key ) const ;

	void addValue( const RepoMDItem& item ) ;

	protected:
	// sic -- empty


	private:
	typedef std::map< std::string , RepoMDItem > InternalMap ;
	InternalMap values_ ;

} ;


// - - - - - - - - - - - - - - - - - - - -

#include<sstream>
#include<string>

#include<TagStack.h>

extern "C" {
	#include<expat.h>
}

class RepoMDHandler {

	public:
	RepoMDHandler( RepoMDSet& set ) ;

	~RepoMDHandler() throw() ;

	void startElement( const XML_Char* name , const XML_Char** attrs ) ;

	void endElement( const XML_Char* name ) ;

	void characters( const XML_Char* buf , int len ) ;


	protected:

	// empty


	private:
	RepoMDSet& set_ ;
	TagStack tags_ ;
	std::ostringstream buf_ ;
	RepoMDItem* currentItem_ ;

} ; // struct RepoMDHandler
// - - - - - - - - - - - - - - - - - - - -


#include<AppException.h>

#include<string>

extern "C" {
	#include<expat.h>
}


class RepoMDParser {

	public:

	const RepoMDSet read( const std::string& file ) throw( AppException ) ;


	protected:
	// empty


	private:

	enum { NOT_DONE_YET = 0 } ;

} ; // class RepoMDParser


// - - - - - - - - - - - - - - - - - - - -

#endif // #ifndef REPOMDPARSER_H
