#ifndef FOREACHNODERUNLINK_H_H_HEAD__FILE__
#define FOREACHNODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLink.h"

class ForeachNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
protected:
	ForeachNodeRunLink( Node * const init_node_ptr )
		: NodeRunLink( init_node_ptr ) { }
};

#endif // FOREACHNODERUNLINK_H_H_HEAD__FILE__
