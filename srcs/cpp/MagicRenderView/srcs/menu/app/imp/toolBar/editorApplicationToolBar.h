#ifndef EDITORAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define EDITORAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#pragma once

#include "../../normalApplicationToolBar.h"

class EditorApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
public:
	EditorApplicationToolBar( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // EDITORAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
