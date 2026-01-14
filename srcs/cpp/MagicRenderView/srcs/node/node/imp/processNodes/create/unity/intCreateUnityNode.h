#ifndef INTCREATEUNITYNODE_H_H_HEAD__FILE__
#define INTCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class IntCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/单元/整数" ) );
};
#endif // INTCREATEUNITYNODE_H_H_HEAD__FILE__
