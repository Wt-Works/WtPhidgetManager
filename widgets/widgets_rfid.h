#ifndef _WIDGETS_RFID_H_
#define _WIDGETS_RFID_H_

/*
 *  widgets_rfid.h
 *
 *  Created by Frode Roxrud Gill, 2013.
 *  This code is GPLv3.
 */

#include "widgets_common.h"

class PhidgetsRFID;

class WidgetsRFID : public WidgetsCommon
{
public:
  WidgetsRFID(PhidgetsRFID* phidget, PhidgetApplication* application);
  virtual ~WidgetsRFID();

public: //From WidgetsCommon
	virtual int GetSerial();
  virtual void OnDigitalOutputChanged(int index, bool state);
  virtual void OnGotRFIDTag(const char* tag, CPhidgetRFID_Protocol protocol);
  virtual void OnLostRFIDTag();
	virtual void OnOnboardLEDChanged(bool state);
	virtual void OnRFIDAntennaChanged(bool state);
	virtual void OnTagWritten(const char* new_tag, CPhidgetRFID_Protocol protocol);

protected:
	virtual Wt::WContainerWidget* CreateWidget();

private:
	/* In Wt thread */
	void OnWtAntennaStateChanged(Wt::WCheckBox* checkbox);
	void OnWtOutputStateChanged(Wt::WCheckBox* checkbox);
	void OnWtOnboardLEDStateChanged(Wt::WCheckBox* checkbox);
	void OnWtWriteTag();

	void UpdateTagText();
	void UpdateTagText(const Wt::WString& tag, CPhidgetRFID_Protocol protocol);
	bool CanWriteTags() const;

private:
	PhidgetsRFID* m_phidget;
	
	Wt::WCheckBox* m_antenna_checkbox;
  Wt::WLineEdit* m_tag_edit;
	Wt::WComboBox* m_tag_protocol_dropdown;
	Wt::WCheckBox* m_lock_tag_checkbox;
	Wt::WPushButton* m_write_tag_button;
	Wt::WCheckBox** m_output_checkbox_array;
	int m_output_checkbox_array_length;
	Wt::WCheckBox* m_onboard_led_checkbox;
};

#endif // _W	IDGETS_RFID_H_
