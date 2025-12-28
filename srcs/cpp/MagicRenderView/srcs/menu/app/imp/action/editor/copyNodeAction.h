#ifndef COPYNODEACTION_H_H_HEAD__FILE__
#define COPYNODEACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class CopyNodeAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
	bool run( QWidget *parent ) override;
};

#endif // COPYNODEACTION_H_H_HEAD__FILE__
