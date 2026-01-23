#ifndef HELPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define HELPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__

#include "../../normalApplicationToolBar.h"

class HelpApplicationToolBar : public NormalApplicationToolBar {
	Q_OBJECT;
public:
	HelpApplicationToolBar( );
	bool init( ApplicationMenuStack *application_menu_stack ) override;
};
#endif // HELPAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
