#ifndef CLEARPROJECTACTION_H_H_HEAD__FILE__
#define CLEARPROJECTACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class ClearProjectAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
	bool run( QWidget *parent ) override;
};

#endif // CLEARPROJECTACTION_H_H_HEAD__FILE__
