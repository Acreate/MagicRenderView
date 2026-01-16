#ifndef NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
#define NORMALAPPLICATIONMENU_H_H_HEAD__FILE__

#include <QMenu>
#include <QObject>

#include "transpondTriggNormalAction/transpondTriggNormalActionMenu.h"

class NormalApplicationAction;
class ApplicationMenuStack;
class NormalApplicationMenu : public TranspondTriggNormalActionMenu {
	Q_OBJECT;
protected:
	std::vector< NormalApplicationMenu * > allMenu;
	NormalApplicationMenu **menuArrayPtr;
	size_t menuArrayCount;
protected:
	void transpondTriggAction( NormalApplicationAction *action ) override;
	virtual void setInitVarNumber( const QString &name ) {
		setObjectName( name );
		setToolTip( name );
		setWindowTitle( name );
		setTitle( name );
	}
	void clearResource( ) override;
	virtual void triggMenuActionSlot( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action );
public:
	NormalApplicationMenu( );
	virtual bool init( ApplicationMenuStack *application_menu_stack );
	virtual bool appendMenu( NormalApplicationMenu *append_menu );
	~NormalApplicationMenu( ) override;
Q_SIGNALS:
	void release_signal( NormalApplicationMenu *release_ptr );
	void trigg_action_signal( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action );
};

#endif // NORMALAPPLICATIONMENU_H_H_HEAD__FILE__
