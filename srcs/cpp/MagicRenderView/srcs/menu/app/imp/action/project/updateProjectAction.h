#ifndef UPDATEPROJECTACTION_H_H_HEAD__FILE__
#define UPDATEPROJECTACTION_H_H_HEAD__FILE__
#pragma once


#include <menu/app/action/normalApplicationAction.h>

class UpdateProjectAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
};
#endif // UPDATEPROJECTACTION_H_H_HEAD__FILE__
