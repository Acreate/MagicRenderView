#ifndef FLOATCREATEUNITYNODE_H_H_HEAD__FILE__
#define FLOATCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class FloatCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = double;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	FloatCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/单元/浮点" ) );
};
#endif // FLOATCREATEUNITYNODE_H_H_HEAD__FILE__
