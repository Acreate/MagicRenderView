#ifndef NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
#define NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
#pragma once
#include <menu/app/action/normalApplicationAction.h>

class NextStepBuilderAction  : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack* application_menu_stack ) override;
	bool run( QWidget *parent ) override;
};

#endif // NEXTSTEPBUILDERACTION_H_H_HEAD__FILE__
