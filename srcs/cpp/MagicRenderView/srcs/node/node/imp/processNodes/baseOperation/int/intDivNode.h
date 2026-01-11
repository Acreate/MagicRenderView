#ifndef INTDIVNODE_H_H_HEAD__FILE__
#define INTDIVNODE_H_H_HEAD__FILE__
#pragma once


#include <node/node/processNode.h>
class IntOutputPort;
class IntInputPort;
class IntDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数值运算/整数/除法" ) );
};

#endif // INTDIVNODE_H_H_HEAD__FILE__
