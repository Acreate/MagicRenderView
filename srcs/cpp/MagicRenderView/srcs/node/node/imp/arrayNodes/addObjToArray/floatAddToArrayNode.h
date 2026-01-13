#ifndef FLOATADDTOARRAYNODE_H_H_HEAD__FILE__
#define FLOATADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class FloatVectorInputPort;
class FloatVectorOutputPort;
class FloatInputPort;
class FloatAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort* firstInputPort;
	FloatInputPort *secondInputPort;
	FloatVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	FloatAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/追加/浮点序列" ) );
};
#endif // FLOATADDTOARRAYNODE_H_H_HEAD__FILE__
