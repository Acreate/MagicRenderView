#ifndef COLORARRAYDIVNODE_H_H_HEAD__FILE__
#define COLORARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorVectorOutputPort;
class ColorInputPort;
class ColorVectorInputPort;
class ColorArrayDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/颜色/除法" ) );
};

#endif // COLORARRAYDIVNODE_H_H_HEAD__FILE__
