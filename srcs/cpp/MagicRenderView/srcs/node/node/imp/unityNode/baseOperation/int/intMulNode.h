#ifndef INTMULNODE_H_H_HEAD__FILE__
#define INTMULNODE_H_H_HEAD__FILE__
#pragma once

#include <node/node/processNode.h>
class IntOutputPort;
class IntInputPort;
class IntMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntInputPort *firstInputPort;
	IntInputPort *secondInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/整数/乘法" ) );
};

#endif // INTMULNODE_H_H_HEAD__FILE__
