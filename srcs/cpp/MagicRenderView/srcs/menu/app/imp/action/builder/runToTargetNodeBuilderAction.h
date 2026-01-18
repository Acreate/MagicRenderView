#ifndef RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__
#define RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__

#include <menu/app/action/normalApplicationAction.h>

#include "../../../../../srack/srackInfo.h"

class Node;
class BuilderDirector;
class RunToTargetNodeBuilderAction : public NormalApplicationAction {
	Q_OBJECT;
protected:
	Node *targetNode;
	bool thisEnblen;
protected:
	virtual void releaTarget( Node *release_target, const SrackInfo &srack_info );
	virtual void createNodeRunInfoAction(  );
	virtual void releaseNodeRunInfoAction(  );
protected Q_SLOTS:
	virtual void enabledChanged_Slot( bool change_enbled_flag );
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow *parent ) override;
	virtual Node * getTargetNode( ) const { return targetNode; }
	virtual void setTargetNode( Node *target_node );
};
#endif // RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__
