#ifndef FLOATARRAYDIVNODE_H_H_HEAD__FILE__
#define FLOATARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class FloatVectorOutputPort;
class FloatVectorInputPort;
class FloatOutputPort;
class FloatInputPort;
class FloatArrayDivNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	FloatArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/浮点/除法" ) );
};

#endif // FLOATARRAYDIVNODE_H_H_HEAD__FILE__
