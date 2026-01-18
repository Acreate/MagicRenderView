#ifndef RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__
#define RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__


#include <menu/app/action/normalApplicationAction.h>

#include "../../../../../srack/srackInfo.h"

class Node;
class BuilderDirector;
class RunToTargetNodeBuilderAction : public NormalApplicationAction {
	Q_OBJECT;
protected:
	Node * targetNode;
protected:
	virtual void releaTarget( Node *release_target, const SrackInfo &srack_info );
public:
	bool init( ApplicationMenuStack *application_menu_stack ) override;
	bool run( MainWindow* parent ) override;
	virtual Node * getTargetNode( ) const { return targetNode; }
	virtual void setTargetNode( Node *target_node );
};
#endif // RUNTOTARGETNODEBUILDERACTION_H_H_HEAD__FILE__
