#ifndef UINTDIVNODE_H_H_HEAD__FILE__
#define UINTDIVNODE_H_H_HEAD__FILE__
#pragma once


#include <node/node/processNode.h>
class IntOutputPort;
class IntInputPort;
class UIntDivNode : public ProcessNode {
	Q_OBJECT;
protected:
	IntOutputPort *outputPortType;
	IntInputPort *multipleAddInputPort;
	uint64_t *addResult;
public:
	UIntDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数值运算/无符号整数/除法" ) );
};

#endif // UINTDIVNODE_H_H_HEAD__FILE__
