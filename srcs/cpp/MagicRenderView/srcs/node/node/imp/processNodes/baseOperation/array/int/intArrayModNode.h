#ifndef INTARRAYMODNODE_H_H_HEAD__FILE__
#define INTARRAYMODNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntVectorInputPort;
class IntVectorOutputPort;
class IntOutputPort;
class IntInputPort;
class IntArrayModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	IntArrayModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/整数/求余" ) );
};

#endif // INTARRAYMODNODE_H_H_HEAD__FILE__
