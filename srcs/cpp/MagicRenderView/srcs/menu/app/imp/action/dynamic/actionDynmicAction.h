#ifndef ACTIONDYNMICACTION_H_H_HEAD__FILE__
#define ACTIONDYNMICACTION_H_H_HEAD__FILE__

#include <menu/app/action/normalApplicationAction.h>

class ActionDynmicAction : public NormalApplicationAction {
	Q_OBJECT;
protected:
	std::function< bool( MainWindow *parent ) > dynmicActionCall;
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow *parent ) override;
	virtual void setDynmicActionCall( const std::function< bool( MainWindow *parent ) > &dynmic_action_call );
};
#endif // ACTIONDYNMICACTION_H_H_HEAD__FILE__
