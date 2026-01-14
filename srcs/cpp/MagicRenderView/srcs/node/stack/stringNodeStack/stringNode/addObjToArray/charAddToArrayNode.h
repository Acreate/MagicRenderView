#ifndef CHARADDTOARRAYNODE_H_H_HEAD__FILE__
#define CHARADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class CharVectorInputPort;
class CharVectorOutputPort;
class CharInputPort;
class CharAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QChar;
protected:
	CharVectorInputPort* firstInputPort;
	CharInputPort *secondInputPort;
	CharVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	CharAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列/追加/字符序列" ) );
};
#endif // CHARADDTOARRAYNODE_H_H_HEAD__FILE__
