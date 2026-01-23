#ifndef RESETBUILDERSTARTNODEPROJECTACTION_H_H_HEAD__FILE__
#define RESETBUILDERSTARTNODEPROJECTACTION_H_H_HEAD__FILE__


#include <menu/app/action/normalApplicationAction.h>

class ResetBuilderStartNodeProjectAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow *parent ) override;
};

#endif // RESETBUILDERSTARTNODEPROJECTACTION_H_H_HEAD__FILE__
