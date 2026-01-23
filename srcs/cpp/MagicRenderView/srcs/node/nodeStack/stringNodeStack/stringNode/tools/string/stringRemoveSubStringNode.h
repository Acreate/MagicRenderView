#ifndef STRINGREMOVESUBSTRINGNODE_H_H_HEAD__FILE__
#define STRINGREMOVESUBSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntInputPort;
class StringInputPort;
class StringOutputPort;
class StringRemoveSubStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *removeSubStringInputPortPtr;
	StringInputPort *orgStringInputPortPtr;
	UIntInputPort *removeCountInputPortPtr;
	StringOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringRemoveSubStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // STRINGREMOVESUBSTRINGNODE_H_H_HEAD__FILE__
