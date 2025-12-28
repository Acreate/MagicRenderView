#ifndef OPENPROJECTACTION_H_H_HEAD__FILE__
#define OPENPROJECTACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class OpenProjectAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
	bool run( QWidget *parent ) override;
};

#endif // OPENPROJECTACTION_H_H_HEAD__FILE__
