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

#include<NoviInfo.h>


NoviInfo::NoviInfo()
        :
    productName_( NOVI__PRODUCT__NAME ) ,
    productVersion_( NOVI__PRODUCT__VERSION ) ,
    productReleaseDate_( NOVI__PRODUCT__VERSION ) ,
    productFullDescription_( NOVI__PRODUCT__FULL_DESCRIPTION )
{
    return ;
}


NoviInfo::~NoviInfo() throw() {
    return ;
}

const std::string& NoviInfo::getProductName() const {
    return( productName_ ) ;
}


const std::string& NoviInfo::getProductVersion() const {
    return( productVersion_ ) ;
}

const std::string& NoviInfo::getProductReleaseDate() const {
    return( productReleaseDate_ ) ;
}

const std::string& NoviInfo::getProductFullDescription() const {
    return( productFullDescription_ ) ;
}


// EOF NoviInfo.cc
