#ifndef BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
#define BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__


#include "../../normalApplicationMenu.h"

class ResetBuilderStartNodeProjectAction;
class StopBuilderAction;
class NextStepBuilderAction;
class RunBuilderAction;
class BuilderPorjectAction;
class BuilderApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
	friend class BuilderDirector;
protected:
	struct {
		BuilderPorjectAction *builderPorjectAction;
		ResetBuilderStartNodeProjectAction *resetBuilderStartNode;
		RunBuilderAction *runBuilderAction;
		NextStepBuilderAction *nextStepBuilderAction;
		StopBuilderAction *stopBuilderAction;
	} normalMenuAction;
public:
	BuilderApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
