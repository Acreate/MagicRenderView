#ifndef HELPAPPLICATIONMENU_H_H_HEAD__FILE__
#define HELPAPPLICATIONMENU_H_H_HEAD__FILE__

#include "../../normalApplicationMenu.h"

class HelpApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	HelpApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // HELPAPPLICATIONMENU_H_H_HEAD__FILE__
