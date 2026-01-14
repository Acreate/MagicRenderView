#ifndef INTSUBNODE_H_H_HEAD__FILE__
#define INTSUBNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntOutputPort;
class IntInputPort;
class IntSubNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntSubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/整数/减法" ) );
};

#endif // INTSUBNODE_H_H_HEAD__FILE__
