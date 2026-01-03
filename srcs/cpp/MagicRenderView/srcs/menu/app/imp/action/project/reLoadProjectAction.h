#ifndef RELOADPROJECTACTION_H_H_HEAD__FILE__
#define RELOADPROJECTACTION_H_H_HEAD__FILE__
#pragma once

#include <menu/app/action/normalApplicationAction.h>

class ReLoadProjectAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
};
#endif // RELOADPROJECTACTION_H_H_HEAD__FILE__
