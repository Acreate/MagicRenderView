#ifndef STRINGARRAYJOINTOSTRINGNODE_H_H_HEAD__FILE__
#define STRINGARRAYJOINTOSTRINGNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringVectorInputPort;
class UIntInputPort;
class IntOutputPort;
class StringInputPort;
class StringOutputPort;
class StringArrayJoinToStringNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = QString;
protected:
	StringVectorInputPort *stringVectorInputPortPtr;
	StringInputPort *jionSubStringInputPortPtr;
	StringOutputPort *outputPortPtr;
	NodeType *outputVarPtr;
public:
	StringArrayJoinToStringNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // STRINGARRAYJOINTOSTRINGNODE_H_H_HEAD__FILE__
