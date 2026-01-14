#ifndef UINTCREATEUNITYNODE_H_H_HEAD__FILE__
#define UINTCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class UIntCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/单元/无符号整数" ) );
};
#endif // UINTCREATEUNITYNODE_H_H_HEAD__FILE__
