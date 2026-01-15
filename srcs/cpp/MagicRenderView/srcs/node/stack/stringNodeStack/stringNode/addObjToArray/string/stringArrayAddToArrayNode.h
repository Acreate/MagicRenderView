#ifndef STRINGARRAYADDTOARRAYNODE_H_H_HEAD__FILE__
#define STRINGARRAYADDTOARRAYNODE_H_H_HEAD__FILE__



#include <node/node/processNode.h>
class StringVectorInputPort;
class StringVectorOutputPort;
class StringInputPort;
class StringArrayAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringVectorInputPort *firstInputPort;
	StringInputPort *secondInputPort;
	StringVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	StringArrayAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "序列追加/序列/字符串序列追加到字符串序列" ) );
};
#endif // STRINGARRAYADDTOARRAYNODE_H_H_HEAD__FILE__
