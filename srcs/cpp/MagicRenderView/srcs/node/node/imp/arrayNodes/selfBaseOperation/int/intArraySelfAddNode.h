#ifndef INTARRAYSELFADDNODE_H_H_HEAD__FILE__
#define INTARRAYSELFADDNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class IntOutputPort;
class IntVectorInputPort;
class UIntInputPort;
class IntArraySelfAddNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/自运算/整数/加法" ) );
};

#endif // INTARRAYSELFADDNODE_H_H_HEAD__FILE__
