#ifndef _PHIDGETS_COMMON_H_
#define _PHIDGETS_COMMON_H_

/*
 *  phidgets_common.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidget21.h"
#include <Wt/WString>

#include "../widgets/widgets_common.h"


class PhidgetsCommon
{
public:
  PhidgetsCommon(int serial);
  virtual ~PhidgetsCommon();

	virtual bool Init() = 0;

public:
	virtual CPhidgetHandle GetHandle() = 0;
	virtual Wt::WString GetPhidgetName();
	int GetSerial() const {return m_serial;}
	virtual WidgetsCommon* CreateWidget(PhidgetApplication* application) = 0;

private:
	int m_serial;
};

#endif // _PHIDGETS_COMMON_H_
