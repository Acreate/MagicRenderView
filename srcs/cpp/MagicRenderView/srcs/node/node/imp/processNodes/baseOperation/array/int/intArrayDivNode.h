#ifndef INTARRAYDIVNODE_H_H_HEAD__FILE__
#define INTARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntVectorInputPort;
class IntVectorOutputPort;
class IntOutputPort;
class IntInputPort;
class IntArrayDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	IntArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/整数/除法" ) );
};

#endif // INTARRAYDIVNODE_H_H_HEAD__FILE__
