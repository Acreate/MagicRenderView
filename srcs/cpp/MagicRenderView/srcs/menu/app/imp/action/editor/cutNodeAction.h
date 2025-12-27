#ifndef CUTNODEACTION_H_H_HEAD__FILE__
#define CUTNODEACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class CutNodeAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override {
		if( NormalApplicationAction::init( application_menu_stack ) == false )
			return false;
		return true;
	}
};
#endif // CUTNODEACTION_H_H_HEAD__FILE__
