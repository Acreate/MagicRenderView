#ifndef RESETAPPACTION_H_H_HEAD__FILE__
#define RESETAPPACTION_H_H_HEAD__FILE__
#pragma once


#include <menu/app/action/normalApplicationAction.h>

class ResetAppAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
};
#endif // RESETAPPACTION_H_H_HEAD__FILE__
