#ifndef COLORADDTOARRAYNODE_H_H_HEAD__FILE__
#define COLORADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class ColorVectorOutputPort;
class ColorInputPort;
class ColorAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorInputPort *firstInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "组合/序列/颜色" ) );
};
#endif // COLORADDTOARRAYNODE_H_H_HEAD__FILE__
