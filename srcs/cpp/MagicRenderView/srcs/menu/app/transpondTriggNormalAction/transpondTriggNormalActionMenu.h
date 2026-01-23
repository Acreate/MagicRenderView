#ifndef TRANSPONDTRIGGNORMALACTIONMENU_H_H_HEAD__FILE__
#define TRANSPONDTRIGGNORMALACTIONMENU_H_H_HEAD__FILE__

#include <QMenu>

class NormalApplicationMenu;
class NormalApplicationAction;
class TranspondTriggNormalActionMenu : public QMenu {
	Q_OBJECT;
protected:
	std::vector< NormalApplicationAction * > allAction;
	NormalApplicationAction **actionArrayPtr;
	size_t actionArrayCount;
private:
protected:
	virtual void clearResource( );
	virtual void triggAction( QAction *transpond_action_ptr );
	virtual bool appendAction( NormalApplicationAction *append_action );
	virtual bool isThisNodemalAction( QAction *check_action );
	virtual void transpondTriggAction( NormalApplicationAction *action ) = 0;
	virtual bool init( );
public:
	TranspondTriggNormalActionMenu( );
	~TranspondTriggNormalActionMenu( ) override;
};

#endif // TRANSPONDTRIGGNORMALACTIONMENU_H_H_HEAD__FILE__
