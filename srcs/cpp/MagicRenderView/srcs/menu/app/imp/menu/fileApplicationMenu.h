#ifndef FILEAPPLICATIONMENU_H_H_HEAD__FILE__
#define FILEAPPLICATIONMENU_H_H_HEAD__FILE__

#include "../../normalApplicationMenu.h"

class ProjectHistoryApplicationMenu;
class FileApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
protected:
	ProjectHistoryApplicationMenu * historyApplicationMenu;
protected:
	void triggMenuActionSlot( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action ) override;
public:
	FileApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // FILEAPPLICATIONMENU_H_H_HEAD__FILE__
