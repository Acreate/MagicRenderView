#ifndef RUNTONEXTFRMEBUILDERACTION_H_H_HEAD__FILE__
#define RUNTONEXTFRMEBUILDERACTION_H_H_HEAD__FILE__

#include <menu/app/action/normalApplicationAction.h>

class BuilderDirector;
class RunToNextFrmeBuilderAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
};
#endif // RUNTONEXTFRMEBUILDERACTION_H_H_HEAD__FILE__
