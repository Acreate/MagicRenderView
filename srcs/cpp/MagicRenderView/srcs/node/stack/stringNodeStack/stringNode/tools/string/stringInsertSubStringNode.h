#ifndef STRINGINSERTSUBSTRINGNODE_H_H_HEAD__FILE__
#define STRINGINSERTSUBSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntInputPort;
class StringInputPort;
class StringOutputPort;
class StringInsertSubStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringInputPort *stringInputPortPtr;
	StringInputPort *insertStringInputPortPtr;
	UIntInputPort *insertIndexInputPortPtr;
	StringOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	StringInsertSubStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // STRINGINSERTSUBSTRINGNODE_H_H_HEAD__FILE__
