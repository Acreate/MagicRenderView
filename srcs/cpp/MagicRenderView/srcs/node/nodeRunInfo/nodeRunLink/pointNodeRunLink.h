#ifndef POINTNODERUNLINK_H_H_HEAD__FILE__
#define POINTNODERUNLINK_H_H_HEAD__FILE__
#include "../nodeRunLink.h"
class NodeRunInfo;
class PointNodeRunLink : public NodeRunLink {
	Q_OBJECT;
	friend class NodeRunInfo;
};

#endif // POINTNODERUNLINK_H_H_HEAD__FILE__
