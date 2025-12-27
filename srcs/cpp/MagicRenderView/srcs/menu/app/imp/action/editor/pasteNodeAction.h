#ifndef PASTENODEACTION_H_H_HEAD__FILE__
#define PASTENODEACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class PasteNodeAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
};

#endif // PASTENODEACTION_H_H_HEAD__FILE__
