#ifndef FLOATARRAYMULNODE_H_H_HEAD__FILE__
#define FLOATARRAYMULNODE_H_H_HEAD__FILE__
#pragma once

#include <node/node/processNode.h>
class FloatVectorInputPort;
class FloatVectorOutputPort;
class FloatOutputPort;
class FloatInputPort;
class FloatArrayMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	FloatArrayMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/浮点/乘法" ) );
};

#endif // FLOATARRAYMULNODE_H_H_HEAD__FILE__
