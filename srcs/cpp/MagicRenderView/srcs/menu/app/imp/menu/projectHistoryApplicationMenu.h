#ifndef PROJECTHISTORYAPPLICATIONMENU_H_H_HEAD__FILE__
#define PROJECTHISTORYAPPLICATIONMENU_H_H_HEAD__FILE__

#include "../../normalApplicationMenu.h"

class ProjectHistoryApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	ProjectHistoryApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // PROJECTHISTORYAPPLICATIONMENU_H_H_HEAD__FILE__
