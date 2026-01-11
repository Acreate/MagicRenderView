#ifndef FLOATADDNODE_H_H_HEAD__FILE__
#define FLOATADDNODE_H_H_HEAD__FILE__
#pragma once

#include <node/node/processNode.h>
class FloatOutputPort;
class FloatInputPort;
class FloatAddNode : public ProcessNode {
	Q_OBJECT;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	double *outputVarPtr;
public:
	FloatAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "数值运算/浮点/加法" ) );
};

#endif // FLOATADDNODE_H_H_HEAD__FILE__
