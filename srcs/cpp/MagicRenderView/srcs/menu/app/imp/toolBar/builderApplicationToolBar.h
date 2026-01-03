#ifndef BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once

#include "../../normalApplicationToolBar.h"

class StopBuilderAction;
class NextStepBuilderAction;
class RunBuilderAction;
class BuilderPorjectAction;
class BuilderApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
	friend class BuilderDirector;
protected:
	struct {
		BuilderPorjectAction *builderPorjectAction;
		RunBuilderAction *runBuilderAction;
		NextStepBuilderAction *nextStepBuilderAction;
		StopBuilderAction *stopBuilderAction;
	} normalToolBarAction;
public:
	BuilderApplicationToolBar( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // BUILDERAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
