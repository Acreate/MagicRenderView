#ifndef BUILDERPORJECTACTION_H_H_HEAD__FILE__
#define BUILDERPORJECTACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class BuilderDirector;
class BuilderPorjectAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
};

#endif // BUILDERPORJECTACTION_H_H_HEAD__FILE__
