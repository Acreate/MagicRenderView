#ifndef COLORDIVNODE_H_H_HEAD__FILE__
#define COLORDIVNODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>
class ColorOutputPort;
class ColorInputPort;

class ColorDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "颜色/单元/除法" ) );
};
#endif // COLORDIVNODE_H_H_HEAD__FILE__
