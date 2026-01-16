#ifndef TRANSPONDTRIGGNORMALACTIONTOOLSBAR_H_H_HEAD__FILE__
#define TRANSPONDTRIGGNORMALACTIONTOOLSBAR_H_H_HEAD__FILE__

#include <QToolBar>

class NormalApplicationAction;
class TranspondTriggNormalActionToolsBar : public QToolBar {
	Q_OBJECT;
protected:
	std::vector< NormalApplicationAction * > allAction;
	NormalApplicationAction **actionArrayPtr;
	size_t actionArrayCount;
protected:
	virtual void clearResource( );
	virtual void triggAction( QAction *transpond_action_ptr );
	virtual bool appendAction( NormalApplicationAction *append_action );
	virtual bool isThisNodemalAction( QAction *check_action );
	virtual void transpondTriggAction( NormalApplicationAction *action ) = 0;
	virtual bool init( );
public:
	TranspondTriggNormalActionToolsBar( );
	~TranspondTriggNormalActionToolsBar( ) override;
};
#endif // TRANSPONDTRIGGNORMALACTIONTOOLSBAR_H_H_HEAD__FILE__
