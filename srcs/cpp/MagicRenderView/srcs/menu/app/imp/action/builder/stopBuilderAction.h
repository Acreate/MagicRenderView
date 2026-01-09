#ifndef STOPBUILDERACTION_H_H_HEAD__FILE__
#define STOPBUILDERACTION_H_H_HEAD__FILE__

#include <menu/app/action/normalApplicationAction.h>

class BuilderDirector;
class StopBuilderAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow *parent ) override;
};

#endif // STOPBUILDERACTION_H_H_HEAD__FILE__
