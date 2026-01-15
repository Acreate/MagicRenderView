#ifndef STRINGCONVERTOCHARARRAYNODE_H_H_HEAD__FILE__
#define STRINGCONVERTOCHARARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class CharVectorOutputPort;
class StringInputPort;
class StringConverToCharArrayNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *stringInputPortPtr;
	CharVectorOutputPort *charVectorOutputPortPtr;
	std::vector< QChar > *outVarPtr;
public:
	StringConverToCharArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "转换/序列/字符串到字符序列" ) );
};
#endif // STRINGCONVERTOCHARARRAYNODE_H_H_HEAD__FILE__
