#ifndef COLORARRAYSELFMULNODE_H_H_HEAD__FILE__
#define COLORARRAYSELFMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class ColorOutputPort;
class ColorVectorInputPort;
class ColorArraySelfMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	ColorVectorInputPort *firstInputPort;
	ColorOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorArraySelfMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "自运算/颜色/乘法" ) );
};
#endif // COLORARRAYSELFMULNODE_H_H_HEAD__FILE__
