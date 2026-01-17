#ifndef BOOLCREATEUNITYNODE_H_H_HEAD__FILE__
#define BOOLCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BoolOutputPort;
class BoolCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = bool;
protected:
	BoolOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	BoolCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr("创建/单元/布尔" ) );
};
#endif // BOOLCREATEUNITYNODE_H_H_HEAD__FILE__
