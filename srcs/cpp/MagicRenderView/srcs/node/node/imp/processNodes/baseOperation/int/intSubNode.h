#ifndef INTSUBNODE_H_H_HEAD__FILE__
#define INTSUBNODE_H_H_HEAD__FILE__
#pragma once

#include <node/node/processNode.h>
class IntOutputPort;
class IntInputPort;
class IntSubNode : public ProcessNode {
	Q_OBJECT;
protected:
	IntOutputPort *outputPortType;
	IntInputPort *multipleAddInputPort;
	int64_t *addResult;
public:
	IntSubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数值运算/整数/减法" ) );
};

#endif // INTSUBNODE_H_H_HEAD__FILE__
