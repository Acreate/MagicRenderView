#ifndef STRINGCREATEARRAYNODE_H_H_HEAD__FILE__
#define STRINGCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringVectorOutputPort;
class StringCreateArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	StringCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/序列/字符串序列" ) );
};
#endif // STRINGCREATEARRAYNODE_H_H_HEAD__FILE__
