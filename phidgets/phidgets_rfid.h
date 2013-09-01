#ifndef _PHIDGETS_RFID_H_
#define _PHIDGETS_RFID_H_

/*
 *  phidgets_rfid.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "phidgets_common.h"

#define NOT_A_PROTOCOL (static_cast<CPhidgetRFID_Protocol>(-1))


class PhidgetsRFID : public PhidgetsCommon
{
public:
  PhidgetsRFID(int serial);
  virtual ~PhidgetsRFID();

public: //From PhidgetsCommon
	virtual bool Init();
	virtual CPhidgetHandle GetHandle() {return reinterpret_cast<CPhidgetHandle>(m_rfid_handle);}
	virtual WidgetsCommon* CreateWidget(PhidgetApplication* application);

public:
	virtual CPhidgetRFIDHandle GetNativeHandle() const {return m_rfid_handle;}

public:
  int OnPhidgetAttach(CPhidgetHandle handle);
  int OnPhidgetDetach(CPhidgetHandle handle);
	int OnPhidgetTagHandler(CPhidgetRFIDHandle handle, char* tag, CPhidgetRFID_Protocol protocol);
	int OnPhidgetTagLostHandler(CPhidgetRFIDHandle handle, char* tag, CPhidgetRFID_Protocol protocol);

public:
	bool CanWriteTags() const;

private:
	CPhidgetRFIDHandle m_rfid_handle;
};

#endif // _PHIDGETS_RFID_H_
