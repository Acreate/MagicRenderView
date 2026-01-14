#ifndef BINCREATEUNITYNODE__H_H_HEAD__FILE__
#define BINCREATEUNITYNODE__H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BinOutputPort;
class BinCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int8_t;
protected:
	BinOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	BinCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/单元/整数" ) );
};
#endif // BINCREATEUNITYNODE__H_H_HEAD__FILE__
