#ifndef _SERVO_H_
#define _SERVO_H_

/*
 *  servo.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include <Wt/WString>
#include "phidget21.h"


class ServoType
{
public:
	ServoType(const Wt::WString& title, CPhidget_ServoType type);

public:
	Wt::WString GetServoTitle() const {return m_title;}
	CPhidget_ServoType GetServoType() const {return m_type;}

private:
	const Wt::WString m_title;
	const CPhidget_ServoType m_type;
};

class ServoUtils
{
public:
  ServoUtils();
  ~ServoUtils();
	
public:
	Wt::WString GetServoTitle(int index) const;
	CPhidget_ServoType GetServoType(int index) const;
	int GetServoTypeIndex(CPhidget_ServoType type) const;

public:
	void PopulateTypeDropdown(Wt::WComboBox* dropdown);

private:
	int m_servo_type_count;
	ServoType** m_servo_types;
};

#endif // _SERVO_H_
