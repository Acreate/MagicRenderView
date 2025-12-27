#ifndef PROJECTAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define PROJECTAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once
#include "../../normalApplicationToolBar.h"

class ProjectApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
public:
	ProjectApplicationToolBar( const QString &title, QWidget *parent );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // PROJECTAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
