/*
 *  sensor_functions.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "sensor_functions.h"

#include <Wt/WComboBox>


Wt::WString DefaultFunction(int value) {return Wt::WString::tr("FunctionDefaultFormat").arg(value);}
Wt::WString Function1142(int value) {return Wt::WString::tr("FunctionLUXFormat").arg(1.478777*value+33.67076);}
Wt::WString Function1143(int value) {return Wt::WString::tr("FunctionLUXFormat").arg(pow(M_E, 0.02385*value-0.56905));}
Wt::WString Function1146(int value) {return Wt::WString::tr("FunctionMMFormat").arg(value);} //What is its function?
Wt::WString Function3120(int value) {return Wt::WString::tr("FunctionLBFormat").arg(value/70.0-10.0/7.0);}
Wt::WString Function3121(int value) {return Wt::WString::tr("FunctionLBFormat").arg(value/28.0-25.0/7.0);}
Wt::WString Function3122(int value) {return Wt::WString::tr("FunctionLBFormat").arg(value/14.0-50.0/7.0);}
Wt::WString Function3123(int value) {return Wt::WString::tr("FunctionLBFormat").arg(value/7.0-100.0/7.0);}
Wt::WString Function3130(int value) {return Wt::WString::tr("FunctionRHFormat").arg((value*0.1906)-40.2);}
Wt::WString Function3500(int value) {return Wt::WString::tr("FunctionAFormat").arg(value/100.0);}
Wt::WString Function3501(int value) {return Wt::WString::tr("FunctionAFormat").arg(value/40.0);}
Wt::WString Function3502(int value) {return Wt::WString::tr("FunctionAFormat").arg(value/20.0);}
Wt::WString Function3503(int value) {return Wt::WString::tr("FunctionAFormat").arg(value/10.0);}
Wt::WString Function3507(int value) {return Wt::WString::tr("FunctionVFormat").arg(value*0.25);}
Wt::WString Function3508(int value) {return Wt::WString::tr("FunctionVFormat").arg(value*0.25);}
Wt::WString Function3509(int value) {return Wt::WString::tr("FunctionVFormat").arg(value*0.2);}
Wt::WString Function3510(int value) {return Wt::WString::tr("FunctionVFormat").arg(value*0.075);}
Wt::WString Function3511(int value) {return Wt::WString::tr("FunctionMAFormat").arg(value*0.01);}
Wt::WString Function3512(int value) {return Wt::WString::tr("FunctionMAFormat").arg(value*0.1);}
Wt::WString Function3513(int value) {return Wt::WString::tr("FunctionMAFormat").arg(value);}
Wt::WString Function3514(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*7.5);} //Using 0.0 for offset
Wt::WString Function3515(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*7.5);} //Using 0.0 for offset
Wt::WString Function3516(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*1.25);} //Using 0.0 for offset
Wt::WString Function3517(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*1.25);} //Using 0.0 for offset
Wt::WString Function3518(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*0.55);} //Using 0.0 for offset
Wt::WString Function3519(int value) {return Wt::WString::tr("FunctionWFormat").arg((value-0.0)*1.65);} //Using 0.0 for offset
Wt::WString Function3520(int value) {return Wt::WString::tr("FunctionCmFormat").arg(2076/(value-11.0));}
Wt::WString Function3521(int value) {return Wt::WString::tr("FunctionCmFormat").arg(4800/(value-20.0));}
Wt::WString Function3522(int value) {return Wt::WString::tr("FunctionCmFormat").arg(9462/(value-16.92));}


SensorFunction::SensorFunction(const Wt::WString& title, Wt::WString (*fptr)(int value), bool ratiometric, int min_value, int max_value)
: m_title(title),
  m_function(fptr),
  m_ratiometric(ratiometric),
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
	m_function_count = 2;
	m_functions = new SensorFunction*[m_function_count];
	m_functions[0] = new SensorFunction(Wt::WString::tr("FunctionDefault"), &DefaultFunction, true, 0, 1000);
	m_functions[1] = new SensorFunction(Wt::WString::tr("Function1142"), &Function1142, false, 0, 950);
	m_functions[1] = new SensorFunction(Wt::WString::tr("Function1143"), &Function1143, false, 0, 500);
	m_functions[2] = new SensorFunction(Wt::WString::tr("Function1146"), &Function1146, true, 30, 900);
	m_functions[3] = new SensorFunction(Wt::WString::tr("Function3120"), &Function3120, true, 0, 1000);
	m_functions[4] = new SensorFunction(Wt::WString::tr("Function3121"), &Function3121, true, 0, 1000);
	m_functions[5] = new SensorFunction(Wt::WString::tr("Function3122"), &Function3122, true, 0, 1000);
	m_functions[6] = new SensorFunction(Wt::WString::tr("Function3123"), &Function3123, true, 0, 1000);
	m_functions[7] = new SensorFunction(Wt::WString::tr("Function3130"), &Function3130, true, 0, 1000);
	m_functions[8] = new SensorFunction(Wt::WString::tr("Function3500"), &Function3500, false, 0, 1000);
	m_functions[9] = new SensorFunction(Wt::WString::tr("Function3501"), &Function3501, false, 0, 1000);
	m_functions[10] = new SensorFunction(Wt::WString::tr("Function3502"), &Function3502, false, 0, 1000);
	m_functions[11] = new SensorFunction(Wt::WString::tr("Function3503"), &Function3503, false, 0, 1000);
	m_functions[12] = new SensorFunction(Wt::WString::tr("Function3507"), &Function3507, false, 0, 1000);
	m_functions[13] = new SensorFunction(Wt::WString::tr("Function3508"), &Function3508, false, 0, 1000);
	m_functions[14] = new SensorFunction(Wt::WString::tr("Function3509"), &Function3509, false, 0, 1000); //I guess this is non-ratiometric?
	m_functions[15] = new SensorFunction(Wt::WString::tr("Function3510"), &Function3510, false, 0, 1000);
	m_functions[16] = new SensorFunction(Wt::WString::tr("Function3511"), &Function3511, false, 0, 1000);
	m_functions[17] = new SensorFunction(Wt::WString::tr("Function3512"), &Function3512, false, 0, 1000);
	m_functions[18] = new SensorFunction(Wt::WString::tr("Function3513"), &Function3513, false, 0, 1000);
	m_functions[19] = new SensorFunction(Wt::WString::tr("Function3514"), &Function3514, false, 0, 1000);
	m_functions[20] = new SensorFunction(Wt::WString::tr("Function3515"), &Function3515, false, 0, 1000);
	m_functions[21] = new SensorFunction(Wt::WString::tr("Function3516"), &Function3516, false, 0, 1000);
	m_functions[22] = new SensorFunction(Wt::WString::tr("Function3517"), &Function3517, false, 0, 1000);
	m_functions[23] = new SensorFunction(Wt::WString::tr("Function3518"), &Function3518, false, 0, 1000);
	m_functions[24] = new SensorFunction(Wt::WString::tr("Function3519"), &Function3519, false, 0, 1000);
	m_functions[25] = new SensorFunction(Wt::WString::tr("Function3520"), &Function3520, true, 80, 530);
	m_functions[26] = new SensorFunction(Wt::WString::tr("Function3521"), &Function3521, true, 80, 500);
	m_functions[27] = new SensorFunction(Wt::WString::tr("Function3522"), &Function3522, true, 80, 490);
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
