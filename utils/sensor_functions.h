#ifndef _SENSOR_FUNCTIONS_H_
#define _SENSOR_FUNCTIONS_H_

/*
 *  sensor_functions.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WString>
#include "phidget21.h"


class SensorFunction
{
public:
	SensorFunction(const Wt::WString& title, Wt::WString (*fptr)(int value));

public:
	Wt::WString GetFunctionTitle() {return m_title;}
	Wt::WString ConvertSensorValue(int value) {return m_function(value);}

private:
	const Wt::WString m_title;
	Wt::WString (CCONV* m_function)(int value);
};

class SensorFunctions
{
public:
  SensorFunctions();
  ~SensorFunctions();
	
public:
	int GetFunctionCount() const {return m_function_count;}
	Wt::WString GetFunctionTitle(int index);
	Wt::WString ConvertSensorValue(int index, int value);

public:
	void PopulateDropdown(Wt::WComboBox* dropdown);
	
private:
	int m_function_count;
	SensorFunction** m_functions;
};

#endif // _SENSOR_FUNCTIONS_H_
