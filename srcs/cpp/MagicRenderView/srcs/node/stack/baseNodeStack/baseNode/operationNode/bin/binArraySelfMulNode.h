#ifndef BINARRAYSELFMULNODE_H_H_HEAD__FILE__
#define BINARRAYSELFMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BinVectorInputPort;
class BinOutputPort;
class BinInputPort;
class BinArraySelfMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinVectorInputPort *firstInputPort;
	BinInputPort *secondInputPort;
	BinOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	BinArraySelfMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/浮点/加法" ) );
};
#endif // BINARRAYSELFMULNODE_H_H_HEAD__FILE__
