#ifndef FLOATARRAYMODNODE_H_H_HEAD__FILE__
#define FLOATARRAYMODNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class FloatVectorOutputPort;
class FloatVectorInputPort;
class FloatOutputPort;
class FloatInputPort;
class FloatArrayModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	FloatVectorInputPort *firstInputPort;
	FloatInputPort *secondInputPort;
	FloatVectorOutputPort *outputPort;
	std::vector< NodeType >  *outputVarPtr;
public:
	FloatArrayModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/浮点/求余" ) );
};

#endif // FLOATARRAYMODNODE_H_H_HEAD__FILE__
