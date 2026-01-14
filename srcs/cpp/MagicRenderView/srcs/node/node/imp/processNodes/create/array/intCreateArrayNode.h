#ifndef INTCREATEARRAYNODE_H_H_HEAD__FILE__
#define INTCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntVectorOutputPort;
class IntCreateArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	IntCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/序列/整数序列" ) );
};
#endif // INTCREATEARRAYNODE_H_H_HEAD__FILE__
