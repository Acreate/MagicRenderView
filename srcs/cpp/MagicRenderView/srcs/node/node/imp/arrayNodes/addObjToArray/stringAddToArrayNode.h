#ifndef STRINGADDTOARRAYNODE_H_H_HEAD__FILE__
#define STRINGADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/arrayNode.h>
class StringVectorOutputPort;
class StringInputPort;
class StringAddToArrayNode : public ArrayNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *firstInputPort;
	StringVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	StringAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "组合/序列/字符串" ) );
};
#endif // STRINGADDTOARRAYNODE_H_H_HEAD__FILE__
