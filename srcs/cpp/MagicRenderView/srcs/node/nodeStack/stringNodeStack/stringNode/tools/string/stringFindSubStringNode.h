#ifndef STRINGFINDSUBSTRINGNODE_H_H_HEAD__FILE__
#define STRINGFINDSUBSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntOutputPort;
class StringInputPort;
class StringOutputPort;
class StringFindSubStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	StringInputPort *stringInputPortPtr;
	StringInputPort *findTargetSubStringInputPortPtr;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringFindSubStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // STRINGFINDSUBSTRINGNODE_H_H_HEAD__FILE__
