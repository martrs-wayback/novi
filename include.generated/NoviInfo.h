#ifndef NOVIINFO_H
#define NOVIINFO_H

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
see the License for the specific language governing permissions and
Limitations under the License.
*/
/*
 *
 *novi
 *2.1.2
 *20120729
 *
 */

#include<string>

#define NOVI__PRODUCT__NAME "novi"
#define NOVI__PRODUCT__VERSION "2.1.2"
#define NOVI__PRODUCT__RELEASE_DATE "20120729"
#define NOVI__PRODUCT__FULL_DESCRIPTION "This is novi release 2.1.2, released 20120729"

class NoviInfo {
    
    public:
    
   	NoviInfo() ;
	~NoviInfo() throw() ;

        const std::string& getProductName() const ;
        const std::string& getProductVersion() const ;
        const std::string& getProductReleaseDate() const ;
        const std::string& getProductFullDescription() const ;

    protected:
        // sic -- empty

    private:
        const std::string productName_ ;
        const std::string productVersion_ ;
        const std::string productReleaseDate_ ;
        const std::string productFullDescription_ ;

}; // class NoviInfo

#endif // #ifndef NOVIINFO_H
