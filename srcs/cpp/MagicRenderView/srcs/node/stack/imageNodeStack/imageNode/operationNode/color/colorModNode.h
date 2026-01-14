#ifndef COLORMODNODE_H_H_HEAD__FILE__
#define COLORMODNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorOutputPort;
class ColorInputPort;

class ColorModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorInputPort *firstInputPort;
	ColorInputPort *secondInputPort;
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "颜色/单元/求余" ) );
};
#endif // COLORMODNODE_H_H_HEAD__FILE__
