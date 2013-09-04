#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

/*
 *  string.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WString>


class StringUtil
{
public:
	static int ToInt(const Wt::WString& s);
	static Wt::WString Round(double value);
};

#endif // _STRING_UTIL_H_
