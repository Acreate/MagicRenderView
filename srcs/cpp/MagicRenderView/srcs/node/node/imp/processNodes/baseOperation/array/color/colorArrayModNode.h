#ifndef COLORARRAYMODNODE_H_H_HEAD__FILE__
#define COLORARRAYMODNODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>
class ColorVectorOutputPort;
class ColorInputPort;
class ColorVectorInputPort;
class ColorArrayModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorArrayModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/运算/颜色/求余" ) );
};

#endif // COLORARRAYMODNODE_H_H_HEAD__FILE__
