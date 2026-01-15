#ifndef CHARARRAYADDTOARRAYNODE_H_H_HEAD__FILE__
#define CHARARRAYADDTOARRAYNODE_H_H_HEAD__FILE__


#include <node/node/processNode.h>
class CharVectorInputPort;
class CharVectorOutputPort;
class CharInputPort;
class CharArrayAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QChar;
protected:
	CharVectorInputPort *firstInputPort;
	CharVectorInputPort *secondInputPort;
	CharVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	CharArrayAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列追加/序列/字符序列追加到字符串序列" ) );
};
#endif // CHARARRAYADDTOARRAYNODE_H_H_HEAD__FILE__
