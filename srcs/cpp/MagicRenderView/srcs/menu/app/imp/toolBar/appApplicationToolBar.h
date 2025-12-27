#ifndef APPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define APPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once

#include "../../normalApplicationToolBar.h"

class AppApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
public:
	AppApplicationToolBar( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // APPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
