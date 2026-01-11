#ifndef FLOATMODNODE_H_H_HEAD__FILE__
#define FLOATMODNODE_H_H_HEAD__FILE__
#pragma once


#include <node/node/processNode.h>
class FloatOutputPort;
class FloatInputPort;
class FloatModNode : public ProcessNode {
	Q_OBJECT;
protected:
	FloatInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatOutputPort *outputPort;
	double *outputVarPtr;
public:
	FloatModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/浮点/求余" ) );
};

#endif // FLOATMODNODE_H_H_HEAD__FILE__
