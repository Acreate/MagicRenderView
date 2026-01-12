#ifndef APPAPPLICATIONMENU_H_H_HEAD__FILE__
#define APPAPPLICATIONMENU_H_H_HEAD__FILE__


#include "../../normalApplicationMenu.h"

class AppApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	AppApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // APPAPPLICATIONMENU_H_H_HEAD__FILE__
