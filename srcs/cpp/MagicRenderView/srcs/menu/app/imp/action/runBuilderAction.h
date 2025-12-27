#ifndef RUNBUILDERACTION_H_H_HEAD__FILE__
#define RUNBUILDERACTION_H_H_HEAD__FILE__
#pragma once
#include "../../action/normalApplicationAction.h"

class RunBuilderAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override {
		if( NormalApplicationAction::init( application_menu_stack ) == false )
			return false;
		return true;
	}
};

#endif // RUNBUILDERACTION_H_H_HEAD__FILE__
