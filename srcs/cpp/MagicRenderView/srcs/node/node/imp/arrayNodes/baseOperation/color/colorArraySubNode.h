#ifndef COLORARRAYSUBNODE_H_H_HEAD__FILE__
#define COLORARRAYSUBNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class ColorVectorOutputPort;
class ColorInputPort;
class ColorVectorInputPort;
class ColorArraySubNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorArraySubNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/序列/颜色/减法" ) );
};

#endif // COLORARRAYSUBNODE_H_H_HEAD__FILE__
