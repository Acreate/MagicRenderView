#ifndef COLORARRAYADDNODE_H_H_HEAD__FILE__
#define COLORARRAYADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorVectorOutputPort;
class ColorInputPort;
class ColorVectorInputPort;

class ColorArrayAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	ColorArrayAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "颜色/序列/加法" ) );
};

#endif // COLORARRAYADDNODE_H_H_HEAD__FILE__
