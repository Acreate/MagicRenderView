#ifndef STRINGCREATEUNITYNODE_H_H_HEAD__FILE__
#define STRINGCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class StringCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/单元/字符串" ) );
};

#endif // STRINGCREATEUNITYNODE_H_H_HEAD__FILE__
