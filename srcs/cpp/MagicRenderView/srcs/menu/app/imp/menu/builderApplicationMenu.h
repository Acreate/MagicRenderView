#ifndef BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
#define BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__

#include "../../normalApplicationMenu.h"

class RunToTargetNodeBuilderAction;
class RunToNextFrmeBuilderAction;
class ResetBuilderStartNodeProjectAction;
class StopBuilderAction;
class NextStepBuilderAction;
class RunBuilderAction;
class BuilderPorjectAction;
class BuilderApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
	friend class BuilderDirector;
protected:
	struct BuilderApplicationMenuActionList {
		BuilderPorjectAction *builderPorjectAction;
		ResetBuilderStartNodeProjectAction *resetBuilderStartNode;
		RunBuilderAction *runBuilderAction;
		NextStepBuilderAction *nextStepBuilderAction;
		StopBuilderAction *stopBuilderAction;
		RunToNextFrmeBuilderAction *runToNextFrmeBuilderAction;
		RunToTargetNodeBuilderAction *runToTargetNodeBuilderAction;
	};
	BuilderApplicationMenuActionList normalMenuAction;
public:
	BuilderApplicationMenu( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	virtual const BuilderApplicationMenuActionList & getNormalMenuAction( ) const { return normalMenuAction; }
};

#endif // BUILDERAPPLICATIONMENU_H_H_HEAD__FILE__
