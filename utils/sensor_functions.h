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
	SensorFunction(const Wt::WString& title, Wt::WString (*fptr)(int value), bool ratiometric, int min_value, int max_value);

public:
	Wt::WString GetFunctionTitle() const {return m_title;}
	Wt::WString ConvertSensorValue(int value);
	bool IsRatiometric() const {return m_ratiometric;}

private:
	const Wt::WString m_title;
	Wt::WString (CCONV* m_function)(int value);
	bool m_ratiometric;
	int m_min_value;
	int m_max_value;
};

class SensorFunctions
{
public:
  SensorFunctions();
  ~SensorFunctions();
	
public:
	Wt::WString GetFunctionTitle(int index, bool ratiometric) const;
	Wt::WString ConvertSensorValue(int index, int value, bool ratiometric);

public:
	void PopulateDropdown(Wt::WComboBox* dropdown, bool ratiometric);

private:
	int GetFunctionCount(bool ratiometric) const {return ratiometric ? m_ratiometric_count : m_non_ratiometric_count;}
	SensorFunction* GetFunction(int index, bool ratiometric) const;
	
private:
	int m_ratiometric_count;
	int m_non_ratiometric_count;
	SensorFunction** m_functions;
};

#endif // _SENSOR_FUNCTIONS_H_
