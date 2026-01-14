#ifndef BINMODNODE_H_H_HEAD__FILE__
#define BINMODNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BinOutputPort;
class BinInputPort;
class BinModNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinInputPort *firstInputPort;
	BinInputPort *secondInputPort;
	BinOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	BinModNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "运算/单元/整数/加法" ) );
};

#endif // BINMODNODE_H_H_HEAD__FILE__
