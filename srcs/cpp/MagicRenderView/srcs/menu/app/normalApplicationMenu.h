#ifndef NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
#define NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>
#include <QObject>

#include "transpondTriggNormalAction/transpondTriggNormalActionMenu.h"

class NormalApplicationAction;
class ApplicationMenuStack;
class NormalApplicationMenu : public TranspondTriggNormalActionMenu {
	Q_OBJECT;
protected:
	void transpondTriggAction( NormalApplicationAction *action ) override;
	virtual void setInitVarNumber( const QString &name ) {
		setObjectName( name );
		setToolTip( name );
		setWindowTitle( name );
		setTitle( name );
	}
public:
	NormalApplicationMenu( );
	virtual bool init( ApplicationMenuStack *application_menu_stack );
	~NormalApplicationMenu( ) override;
Q_SIGNALS:
	void release_signal( NormalApplicationMenu *release_ptr );
	void trigg_action_signal( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action );
};

#endif // NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
