#ifndef STRINGSPLITSTRINGARRAYNODE_H_H_HEAD__FILE__
#define STRINGSPLITSTRINGARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringVectorOutputPort;
class StringInputPort;
class StringSplitStringArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *stringInputPortPtr;
	StringInputPort *splitSubStringInputPortPtr;
	StringVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	StringSplitStringArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // STRINGSPLITSTRINGARRAYNODE_H_H_HEAD__FILE__
