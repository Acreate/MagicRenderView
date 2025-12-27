#ifndef SAVEPORJECTACTION_H_H_HEAD__FILE__
#define SAVEPORJECTACTION_H_H_HEAD__FILE__
#pragma once
#include "../../action/normalApplicationAction.h"

class SavePorjectAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override {
		if( NormalApplicationAction::init( application_menu_stack ) == false )
			return false;
		return true;
	}
};

#endif // SAVEPORJECTACTION_H_H_HEAD__FILE__
