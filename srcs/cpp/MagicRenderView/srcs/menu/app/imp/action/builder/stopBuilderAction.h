#ifndef file_mac_H_HEAD__FILE__
#define file_mac_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class StopBuilderAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // file_mac_H_HEAD__FILE__
