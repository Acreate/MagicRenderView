#ifndef EDITORAPPLICATIONMENU_H_H_HEAD__FILE__
#define EDITORAPPLICATIONMENU_H_H_HEAD__FILE__

#include "../../normalApplicationMenu.h"

class EditorApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	EditorApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // EDITORAPPLICATIONMENU_H_H_HEAD__FILE__
