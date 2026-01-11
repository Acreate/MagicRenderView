#ifndef COLORDIVNODE_H_H_HEAD__FILE__
#define COLORDIVNODE_H_H_HEAD__FILE__


#include <node/node/unityNode.h>
class ColorOutputPort;
class ColorInputPort;

class ColorDivNode : public UnityNode {
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
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/无符号整数/加法" ) );
};
#endif // COLORDIVNODE_H_H_HEAD__FILE__
