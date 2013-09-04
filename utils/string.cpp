/*
 *  string.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "string.h"

#include <stdio.h>
#include <stdlib.h>


int StringUtil::ToInt(const Wt::WString& s)
{
	if (s.empty())
		return 0;

	return atoi(s.toUTF8().data());
}

Wt::WString StringUtil::Round(double value)
{
	int precision = 4;
	if (1000.0<=value)
		precision = 1;
	else if (100.0<=value)
		precision = 2;
	else if (10.0<=value)
		precision = 3;
	else if (0.001>value)
		precision = 5;

	char buf[32];
	snprintf(buf, 32, "%.*f", precision, value);
	return Wt::WString(buf);
}
