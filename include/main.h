#ifndef MAIN_H
#define MAIN_H

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

#include<AppConfig.h>
#include<NoviInfo.h>


/// popt options

const struct poptOption optArgs[] = {

	{
		"action" ,
		'a' ,
		POPT_ARG_STRING ,
		NULL ,
		AppConfig::FLAG_ACTION ,
		"output type: list (default), hardlink, softlink, copy. (All but \"list\" require a target dir).\n" ,
		"{type}"
	} ,

	{
		"target" ,
		't' ,
		POPT_ARG_STRING ,
		NULL ,
		AppConfig::FLAG_TARGET_DIR ,
		"target dir (used for action == hardlink or softlink)\n" ,
		"/another/path"
	} ,

	{
		"verbose" ,
		'v' ,
		POPT_ARG_NONE ,
		NULL ,
		AppConfig::FLAG_VERBOSE ,
		"enable verbose output\n" ,
		NULL
	} ,

	{
		"version" ,
		'\0' ,
		POPT_ARG_NONE ,
		NULL ,
		AppConfig::FLAG_VERSION ,
		"show program version\n" ,
		NULL
	} ,

	{
		"help" ,
		'h' ,
		POPT_ARG_NONE ,
		NULL ,
		AppConfig::FLAG_HELP ,
		"show a brief help message\n" ,
		NULL
	} ,

	/*
		QQQ: how to have popt include "{list of files}"
		in the auto-generated help output?
	*/

	/* terminal member of popt arg structure */
	// { NULL, 0, 0, NULL, 0 }
	POPT_TABLEEND

} ; 

// EOF main.h

#endif // #ifndef MAIN_H
