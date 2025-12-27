#ifndef BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
#define BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
#pragma once



#include "../../normalApplicationMenu.h"

class BuilderApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	BuilderApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
