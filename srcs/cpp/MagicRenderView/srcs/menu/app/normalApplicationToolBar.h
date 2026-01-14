#ifndef NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
#define NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__

#include <QToolBar>

#include "transpondTriggNormalAction/transpondTriggNormalActionToolsBar.h"

class ApplicationMenuStack;
class NormalApplicationToolBar : public TranspondTriggNormalActionToolsBar {
	Q_OBJECT;
protected:
	void transpondTriggAction( NormalApplicationAction *action ) override;
	virtual void setInitVarNumber( const QString &name ) {
		setObjectName( name );
		setToolTip( name );
		setWindowTitle( name );
	}
public:
	NormalApplicationToolBar( );
	virtual bool init( ApplicationMenuStack *application_menu_stack );
	~NormalApplicationToolBar( ) override;
Q_SIGNALS:
	void release_signal( NormalApplicationToolBar *release_ptr );
	void trigg_action_signal( NormalApplicationToolBar *normal_application_tool_bar, NormalApplicationAction *action );
};

#endif // NORMALAPPLICATIONTOOLBAR_H_H_HEAD__FILE__
