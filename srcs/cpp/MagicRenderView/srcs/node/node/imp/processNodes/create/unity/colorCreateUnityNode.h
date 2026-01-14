#ifndef COLORCREATEUNITYNODE_H_H_HEAD__FILE__
#define COLORCREATEUNITYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharOutputPort;
class ColorCreateUnityNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QColor;
protected:
	CharOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	ColorCreateUnityNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/单元/颜色" ) );
};
#endif // COLORCREATEUNITYNODE_H_H_HEAD__FILE__
