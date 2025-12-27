#ifndef FILEAPPLICATIONMENU_H_H_HEAD__FILE__
#define FILEAPPLICATIONMENU_H_H_HEAD__FILE__
#pragma once
#include "../../normalApplicationMenu.h"

class FileApplicationMenu : public NormalApplicationMenu{
	Q_OBJECT;
public:
	FileApplicationMenu( const QString &title, QWidget *parent );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // FILEAPPLICATIONMENU_H_H_HEAD__FILE__
