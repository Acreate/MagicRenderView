#ifndef COLORARRAYSELFADDNODE_H_H_HEAD__FILE__
#define COLORARRAYSELFADDNODE_H_H_HEAD__FILE__


#include <node/node/arrayNode.h>
class ColorVectorInputPort;
class ColorOutputPort;
class ColorArraySelfAddNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/自运算/颜色/加法" ) );
};
#endif // COLORARRAYSELFADDNODE_H_H_HEAD__FILE__
