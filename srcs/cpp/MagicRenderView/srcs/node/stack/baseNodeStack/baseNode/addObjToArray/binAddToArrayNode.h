#ifndef BINADDTOARRAYNODE_H_H_HEAD__FILE__
#define BINADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BinVectorOutputPort;
class BinInputPort;
class BinVectorInputPort;
class BinAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	BinVectorInputPort* firstInputPort;
	BinInputPort *secondInputPort;
	BinVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	BinAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/追加/整数序列" ) );
};
#endif // BINADDTOARRAYNODE_H_H_HEAD__FILE__
