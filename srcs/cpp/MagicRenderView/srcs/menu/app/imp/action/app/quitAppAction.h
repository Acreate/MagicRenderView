#ifndef QUITAPPACTION_H_H_HEAD__FILE__
#define QUITAPPACTION_H_H_HEAD__FILE__


#include <menu/app/action/normalApplicationAction.h>

class QuitAppAction : public NormalApplicationAction {
	Q_OBJECT;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
};
#endif // QUITAPPACTION_H_H_HEAD__FILE__
