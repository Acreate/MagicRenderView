#ifndef NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
#define NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class NextStepBuilderAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override {
		if( NormalApplicationAction::init( application_menu_stack ) == false )
			return false;
		return true;
	}
};

#endif // NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
