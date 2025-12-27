#ifndef PROJECTAPPLICATIONMENU_H_H_HEAD__FILE__
#define PROJECTAPPLICATIONMENU_H_H_HEAD__FILE__
#pragma once
#include "../../normalApplicationMenu.h"

class ProjectApplicationMenu : public NormalApplicationMenu {
	Q_OBJECT;
public:
	ProjectApplicationMenu( const QString &title, QWidget *parent );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // PROJECTAPPLICATIONMENU_H_H_HEAD__FILE__
