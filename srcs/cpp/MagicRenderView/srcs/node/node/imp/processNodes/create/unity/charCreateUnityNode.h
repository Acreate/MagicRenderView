#ifndef CHARCREATEUNITYNODE_H_H_HEAD__FILE__
#define CHARCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class CharCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QChar;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	CharCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "创建/单元/字符" ) );
};
#endif // CHARCREATEUNITYNODE_H_H_HEAD__FILE__
