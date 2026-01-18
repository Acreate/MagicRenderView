#ifndef BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__

#include "../../normalApplicationToolBar.h"

class RunToTargetNodeBuilderAction;
class RunToNextFrmeBuilderAction;
class ResetBuilderStartNodeProjectAction;
class StopBuilderAction;
class NextStepBuilderAction;
class RunBuilderAction;
class BuilderPorjectAction;
class BuilderApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
	friend class BuilderDirector;
protected:
	struct BuilderApplicationToolBarActionList {
		BuilderPorjectAction *builderPorjectAction;
		ResetBuilderStartNodeProjectAction *resetBuilderStartNode;
		RunBuilderAction *runBuilderAction;
		NextStepBuilderAction *nextStepBuilderAction;
		StopBuilderAction *stopBuilderAction;
		RunToNextFrmeBuilderAction *runToNextFrmeBuilderAction;
		RunToTargetNodeBuilderAction *runToTargetNodeBuilderAction;
	};
	BuilderApplicationToolBarActionList normalToolBarAction;
public:
	BuilderApplicationToolBar( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	virtual const BuilderApplicationToolBarActionList & getNormalToolBarAction( ) const { return normalToolBarAction; }
};

#endif // BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
