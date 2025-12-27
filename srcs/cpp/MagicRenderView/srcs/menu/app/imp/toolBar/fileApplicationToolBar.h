#ifndef FILEAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define FILEAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once
#include "../../normalApplicationToolBar.h"

class ApplicationMenuStack;
class FileApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
public:
	FileApplicationToolBar( const QString &title, QWidget *parent );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};

#endif // FILEAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
