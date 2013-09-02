/*
 *  sensor_functions.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "sensor_functions.h"

#include <Wt/WComboBox>


Wt::WString DefaultFunction(int value) {return Wt::WString::tr("FunctionDefaultFormat").arg(value);}


SensorFunction::SensorFunction(const Wt::WString& title, Wt::WString (*fptr)(int value), int min_value, int max_value)
: m_title(title),
  m_function(fptr),
  m_min_value(min_value),
  m_max_value(max_value)
{
}

Wt::WString SensorFunction::ConvertSensorValue(int value)
{
	if (m_min_value>value || m_max_value<value)
		return Wt::WString::tr("Out of range");

	return m_function(value);
}



SensorFunctions::SensorFunctions()
{
	m_function_count = 1;
	m_functions = new SensorFunction*[m_function_count];
	m_functions[0] = new SensorFunction(Wt::WString::tr("FunctionDefault"), &DefaultFunction, 0, 1000);
}

SensorFunctions::~SensorFunctions()
{
	int i;
	for (i=0; m_function_count>i; i++)
	{
		delete m_functions[i];
	}
	delete[] m_functions;
}

Wt::WString SensorFunctions::GetFunctionTitle(int index)
{
	if (0>index || GetFunctionCount()<=index)
		return Wt::WString::Empty;

	return m_functions[index]->GetFunctionTitle();
}

Wt::WString SensorFunctions::ConvertSensorValue(int index, int value)
{
	if (0>index || GetFunctionCount()<=index)
		return Wt::WString::Empty;

	return m_functions[index]->ConvertSensorValue(value);
}

void SensorFunctions::PopulateDropdown(Wt::WComboBox* dropdown)
{
	int i;
	for (i=0; m_function_count>i; i++)
	{
		dropdown->addItem(GetFunctionTitle(i));
	}
}
