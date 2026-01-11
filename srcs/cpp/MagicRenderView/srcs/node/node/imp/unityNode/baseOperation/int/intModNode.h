#ifndef INTMODNODE_H_H_HEAD__FILE__
#define INTMODNODE_H_H_HEAD__FILE__

#include <node/node/unityNode.h>

class IntOutputPort;
class IntInputPort;
class IntModNode : public UnityNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/整数/求余" ) );
};

#endif // INTMODNODE_H_H_HEAD__FILE__
