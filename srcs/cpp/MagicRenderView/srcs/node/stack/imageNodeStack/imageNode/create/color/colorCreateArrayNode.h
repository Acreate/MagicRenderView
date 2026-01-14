#ifndef COLORCREATEARRAYNODE_H_H_HEAD__FILE__
#define COLORCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorVectorOutputPort;
class ColorCreateArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/序列/颜色" ) );
};
#endif // COLORCREATEARRAYNODE_H_H_HEAD__FILE__
