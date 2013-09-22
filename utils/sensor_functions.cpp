/*
 *  sensor_functions.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "sensor_functions.h"

#include <Wt/WComboBox>
#include "./string.h"

#define VALUE(x,y) Wt::WString::tr(x).arg(StringUtil::Round(y))
#define VALUESTR(x,y) Wt::WString::tr(x).arg(y)

Wt::WString DefaultFunction(int value) {return VALUE("FunctionDefaultFormat", value);}


Wt::WString Function1101(int value) {return VALUE("FunctionDefaultFormat", value);} //See separate functions for 3520, 3521 and 3522
Wt::WString Function1102(int value) {return VALUESTR("FunctionDefaultFormat", Wt::WString::tr(400>=value ? "Detected" : "Not detected"));}
Wt::WString Function1103(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1104(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1105(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1106(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1108(int value) {return VALUE("FunctionGaussFormat", 500.0-(double)value);}
Wt::WString Function1107(int value) {return VALUE("FunctionRHFormat", (((double)value/1000.0)*190.6)-40.2);}
Wt::WString Function1109(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1110(int value) {return VALUESTR("FunctionDefaultFormat", Wt::WString::tr(500<=value ? "Touched" : "Untouched"));}
Wt::WString Function1111(int value) {return VALUESTR("FunctionDefaultFormat", Wt::WString::tr(400>=value || 600<=value ? "Motion" : "No motion"));}
Wt::WString Function1112(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1113(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1114(int value) {return VALUE("FunctionVFormat", ((double)value/4.0)-50.0);}
Wt::WString Function1115(int value) {return VALUE("FunctionKPAFormat", ((double)value/4.0)+10.0);}
Wt::WString Function1116(int value) {return VALUE("FunctionDefaultFormat", value);}
Wt::WString Function1117(int value) {return VALUE("FunctionVFormat", ((double)value*0.06)-30.0);}
Wt::WString Function1118AC(int value) {return VALUE("FunctionAFormat", (double)value*0.06938);}
Wt::WString Function1118DC(int value) {return VALUE("FunctionAFormat", ((double)value/8.0)-62.5);}
Wt::WString Function1119AC(int value) {return VALUE("FunctionAFormat", (double)value*0.02775);}
Wt::WString Function1119DC(int value) {return VALUE("FunctionAFormat", ((double)value/20.0)-25.0);}
Wt::WString Function1120(int value) {return VALUE("FunctionDefaultFormat", value);} //Needs callibration
Wt::WString Function1121(int value) {return VALUE("FunctionMVFormat", (double)value*5.0);}
Wt::WString Function1122AC(int value) {return VALUE("FunctionAFormat", (double)value*0.04204);}
Wt::WString Function1122DC(int value) {return VALUE("FunctionAFormat", (double)value/13.2-37.8787);}
Wt::WString Function1123(int value) {return VALUE("FunctionVFormat", ((double)value*0.06)-30.0);}
Wt::WString Function1124(int value) {return VALUE("FunctionCFormat", ((double)value*0.22222)-61.11);}
Wt::WString Function1125C(int value) {return VALUE("FunctionCFormat", ((double)value*0.22222)-61.11);}
Wt::WString Function1125RH(int value) {return VALUE("FunctionRHFormat", ((double)value*0.1906)-40.2);}
Wt::WString Function1126KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/18.0-27.7777);}
Wt::WString Function1126PSI(int value) {return VALUE("FunctionPSIFormat", ((double)value*0.008055)-4.0277);}
Wt::WString Function1127(int value) {return VALUE("FunctionLUXFormat", value);}
Wt::WString Function1128(int value) {return VALUE("FunctionCMFormat", (double)value*1.296);}
Wt::WString Function1129(int value) {return VALUESTR("FunctionDefaultFormat", Wt::WString::tr(500<=value ? "Touched" : "Untouched"));}
Wt::WString Function1130PH(int value) {return VALUE("FunctionPHFormat", 0.0178*(double)value-1.889);}
Wt::WString Function1130ORP(int value) {return VALUE("FunctionORPFormat", (2.5-(double)value/200.0)/1.037);}
Wt::WString Function1131(int value) {return VALUE("FunctionGFormat", 15.311*pow(M_E, 0.005199*(double)value));}
Wt::WString Function1133(int value) {return VALUE("FunctionDBFormat", 16.801*log((double)value)+9.872);}
Wt::WString Function1135(int value) {return VALUE("FunctionVFormat", ((double)value/200.0-2.5)/0.0681);}
Wt::WString Function1136KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/200.0-2.5);}
Wt::WString Function1136PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/1379.31-0.3625);}
Wt::WString Function1137KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/57.143-8.75);}
Wt::WString Function1137PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/394.09-1.269);}
Wt::WString Function1138KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/18.0-2.222);}
Wt::WString Function1138PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/124.14-0.322);}
Wt::WString Function1139KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/9.0-4.444);}
Wt::WString Function1139PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/62.07-0.6444);}
Wt::WString Function1140KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/2.421+3.478);}
Wt::WString Function1140PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/16.697+0.504);}
Wt::WString Function1141KPA(int value) {return VALUE("FunctionKPAFormat", (double)value/9.2+10.652);}
Wt::WString Function1141PSI(int value) {return VALUE("FunctionPSIFormat", (double)value/63.45+1.54);}
Wt::WString Function1142(int value) {return VALUE("FunctionLUXFormat", 1.478777*(double)value+33.67076);}
Wt::WString Function1143(int value) {return VALUE("FunctionLUXFormat", pow(M_E, 0.02385*(double)value-0.56905));}
Wt::WString Function1146(int value) {return VALUE("FunctionMMFormat", value);} //What is its function?
Wt::WString Function3120(int value) {return VALUE("FunctionLBFormat", (double)value/70.0-10.0/7.0);}
Wt::WString Function3121(int value) {return VALUE("FunctionLBFormat", (double)value/28.0-25.0/7.0);}
Wt::WString Function3122(int value) {return VALUE("FunctionLBFormat", (double)value/14.0-50.0/7.0);}
Wt::WString Function3123(int value) {return VALUE("FunctionLBFormat", (double)value/7.0-100.0/7.0);}
Wt::WString Function3130(int value) {return VALUE("FunctionRHFormat", ((double)value*0.1906)-40.2);}
Wt::WString Function3500(int value) {return VALUE("FunctionAFormat", (double)value/100.0);}
Wt::WString Function3501(int value) {return VALUE("FunctionAFormat", (double)value/40.0);}
Wt::WString Function3502(int value) {return VALUE("FunctionAFormat", (double)value/20.0);}
Wt::WString Function3503(int value) {return VALUE("FunctionAFormat", (double)value/10.0);}
Wt::WString Function3507(int value) {return VALUE("FunctionVFormat", (double)value*0.25);}
Wt::WString Function3508(int value) {return VALUE("FunctionVFormat", (double)value*0.25);}
Wt::WString Function3509(int value) {return VALUE("FunctionVFormat", (double)value*0.2);}
Wt::WString Function3510(int value) {return VALUE("FunctionVFormat", (double)value*0.075);}
Wt::WString Function3511(int value) {return VALUE("FunctionMAFormat", (double)value*0.01);}
Wt::WString Function3512(int value) {return VALUE("FunctionMAFormat", (double)value*0.1);}
Wt::WString Function3513(int value) {return VALUE("FunctionMAFormat", value);}
Wt::WString Function3514(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*7.5);} //Using 0.0 for offset
Wt::WString Function3515(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*7.5);} //Using 0.0 for offset
Wt::WString Function3516(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*1.25);} //Using 0.0 for offset
Wt::WString Function3517(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*1.25);} //Using 0.0 for offset
Wt::WString Function3518(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*0.55);} //Using 0.0 for offset
Wt::WString Function3519(int value) {return VALUE("FunctionWFormat", ((double)value-0.0)*1.65);} //Using 0.0 for offset
Wt::WString Function3520(int value) {return VALUE("FunctionCMFormat", 2076/((double)value-11.0));}
Wt::WString Function3521(int value) {return VALUE("FunctionCMFormat", 4800/((double)value-20.0));}
Wt::WString Function3522(int value) {return VALUE("FunctionCMFormat", 9462/((double)value-16.92));}


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
	m_ratiometric_count = 53;
	m_non_ratiometric_count = 28;
	m_functions = new SensorFunction*[m_ratiometric_count+m_non_ratiometric_count];
	int i=0;
	m_functions[i++] = new SensorFunction(Wt::WString::tr("FunctionDefault"), &DefaultFunction, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1101"), &Function1101, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1102"), &Function1102, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1103"), &Function1103, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1104"), &Function1104, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1105"), &Function1105, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1106"), &Function1106, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1107"), &Function1107, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1108"), &Function1108, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1109"), &Function1109, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1110"), &Function1110, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1111"), &Function1111, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1112"), &Function1112, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1113"), &Function1113, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1115"), &Function1115, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1116"), &Function1116, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1118AC"), &Function1118AC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1118DC"), &Function1118DC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1119AC"), &Function1119AC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1119DC"), &Function1119DC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1120"), &Function1120, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1121"), &Function1121, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1122AC"), &Function1122AC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1122DC"), &Function1122DC, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1124"), &Function1124, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1125C"), &Function1125C, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1125RH"), &Function1125RH, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1126KPA"), &Function1126KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1126PSI"), &Function1126PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1128"), &Function1128, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1129"), &Function1129, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1131"), &Function1131, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1136KPA"), &Function1136KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1136PSI"), &Function1136PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1137KPA"), &Function1137KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1137PSI"), &Function1137PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1138KPA"), &Function1138KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1138PSI"), &Function1138PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1139KPA"), &Function1139KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1139PSI"), &Function1139PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1140KPA"), &Function1140KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1140PSI"), &Function1140PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1141KPA"), &Function1141KPA, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1141PSI"), &Function1141PSI, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1146"), &Function1146, true, 30, 900);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3120"), &Function3120, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3121"), &Function3121, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3122"), &Function3122, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3123"), &Function3123, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3130"), &Function3130, true, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3520"), &Function3520, true, 80, 530);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3521"), &Function3521, true, 80, 500);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3522"), &Function3522, true, 80, 490);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("FunctionDefault"), &DefaultFunction, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1114"), &Function1114, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1117"), &Function1117, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1123"), &Function1123, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1127"), &Function1127, false, 0, 950);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1130PH"), &Function1130PH, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1130ORP"), &Function1130ORP, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1133"), &Function1133, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1135"), &Function1135, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1142"), &Function1142, false, 0, 950);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function1143"), &Function1143, false, 0, 500);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3500"), &Function3500, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3501"), &Function3501, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3502"), &Function3502, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3503"), &Function3503, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3507"), &Function3507, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3508"), &Function3508, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3509"), &Function3509, false, 0, 1000); //I guess this is non-ratiometric?
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3510"), &Function3510, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3511"), &Function3511, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3512"), &Function3512, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3513"), &Function3513, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3514"), &Function3514, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3515"), &Function3515, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3516"), &Function3516, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3517"), &Function3517, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3518"), &Function3518, false, 0, 1000);
	m_functions[i++] = new SensorFunction(Wt::WString::tr("Function3519"), &Function3519, false, 0, 1000);
}

SensorFunctions::~SensorFunctions()
{
	int i;
	for (i=0; (m_ratiometric_count+m_non_ratiometric_count)>i; i++)
	{
		delete m_functions[i];
	}
	delete[] m_functions;
}

Wt::WString SensorFunctions::GetFunctionTitle(int index, bool ratiometric) const
{
	SensorFunction* func = GetFunction(index, ratiometric);
	if (!func)
		return Wt::WString::Empty;

	return func->GetFunctionTitle();
}

Wt::WString SensorFunctions::ConvertSensorValue(int index, int value, bool ratiometric)
{
	SensorFunction* func = GetFunction(index, ratiometric);
	if (!func)
		return Wt::WString::Empty;

	return func->ConvertSensorValue(value);
}

void SensorFunctions::PopulateDropdown(Wt::WComboBox* dropdown, bool ratiometric)
{
	dropdown->clear();

	int i;
	for (i=0; GetFunctionCount(ratiometric)>i; i++)
	{
		dropdown->addItem(GetFunctionTitle(i, ratiometric));
	}
}

SensorFunction* SensorFunctions::GetFunction(int index, bool ratiometric) const
{
	if (0>index)
		return NULL;

	if (ratiometric)
	{
		return (m_ratiometric_count<=index) ? NULL : m_functions[index];
	}
	else
	{
		return (m_non_ratiometric_count<=index) ? NULL : m_functions[m_ratiometric_count+index];
	}
}
