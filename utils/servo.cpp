/*
 *  servo.cpp
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "servo.h"

#include <Wt/WComboBox>
#include "./string.h"



ServoType::ServoType(const Wt::WString& title, CPhidget_ServoType type)
: m_title(title),
  m_type(type)
{
}



ServoUtils::ServoUtils()
{
	m_servo_type_count = 24;
	m_servo_types = new ServoType*[m_servo_type_count];
	int i=0;
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_DEFAULT"), PHIDGET_SERVO_DEFAULT);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_RAW_us_MODE"), PHIDGET_SERVO_RAW_us_MODE);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS322HD"), PHIDGET_SERVO_HITEC_HS322HD);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS5245MG"), PHIDGET_SERVO_HITEC_HS5245MG);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_805BB"), PHIDGET_SERVO_HITEC_805BB);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS422"), PHIDGET_SERVO_HITEC_HS422);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_TOWERPRO_MG90"), PHIDGET_SERVO_TOWERPRO_MG90);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HSR1425CR"), PHIDGET_SERVO_HITEC_HSR1425CR);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS785HB"), PHIDGET_SERVO_HITEC_HS785HB);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS485HB"), PHIDGET_SERVO_HITEC_HS485HB);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_HS645MG"), PHIDGET_SERVO_HITEC_HS645MG);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_HITEC_815BB"), PHIDGET_SERVO_HITEC_815BB);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_FIRGELLI_L12_30_50_06_R"), PHIDGET_SERVO_FIRGELLI_L12_30_50_06_R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_FIRGELLI_L12_50_100_06_R"), PHIDGET_SERVO_FIRGELLI_L12_50_100_06_R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_FIRGELLI_L12_50_210_06_R"), PHIDGET_SERVO_FIRGELLI_L12_50_210_06_R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_FIRGELLI_L12_100_50_06_R"), PHIDGET_SERVO_FIRGELLI_L12_100_50_06_R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_FIRGELLI_L12_100_100_06_R"), PHIDGET_SERVO_FIRGELLI_L12_100_100_06_R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S2313M"), PHIDGET_SERVO_SPRINGRC_SM_S2313M);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S3317M"), PHIDGET_SERVO_SPRINGRC_SM_S3317M);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S3317SR"), PHIDGET_SERVO_SPRINGRC_SM_S3317SR);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S4303R"), PHIDGET_SERVO_SPRINGRC_SM_S4303R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S4315M"), PHIDGET_SERVO_SPRINGRC_SM_S4315M);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S4315R"), PHIDGET_SERVO_SPRINGRC_SM_S4315R);
	m_servo_types[i++] = new ServoType(Wt::WString::tr("PHIDGET_SERVO_SPRINGRC_SM_S4505B"), PHIDGET_SERVO_SPRINGRC_SM_S4505B);
}

ServoUtils::~ServoUtils()
{
	int i;
	for (i=0; m_servo_type_count>i; i++)
	{
		delete m_servo_types[i];
	}
	delete[] m_servo_types;
}
	
Wt::WString ServoUtils::GetServoTitle(int index) const
{
	if (0>index || m_servo_type_count<=index)
		return Wt::WString::Empty;
	
	return m_servo_types[index]->GetServoTitle();
}

CPhidget_ServoType ServoUtils::GetServoType(int index) const
{
	if (0>index || m_servo_type_count<=index)
		return PHIDGET_SERVO_DEFAULT;
	
	return m_servo_types[index]->GetServoType();
}

int ServoUtils::GetServoTypeIndex(CPhidget_ServoType type) const
{
	int i;
	for (i=0; m_servo_type_count>i; i++)
	{
		if (m_servo_types[i]->GetServoType() == type)
			return i;
	}
	//If not found, use DEFAULT (and if that is not found, return 0...)
	return (PHIDGET_SERVO_DEFAULT!=type ? GetServoTypeIndex(PHIDGET_SERVO_DEFAULT) : 0);
}

void ServoUtils::PopulateTypeDropdown(Wt::WComboBox* dropdown)
{
	dropdown->clear();

	int i;
	for (i=0; m_servo_type_count>i; i++)
	{
		dropdown->addItem(GetServoTitle(i));
	}
}
