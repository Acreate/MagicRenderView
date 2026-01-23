#ifndef INTARRAYSELFMULNODE_H_H_HEAD__FILE__
#define INTARRAYSELFMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class IntVectorInputPort;
class IntOutputPort;
class UIntOutputPort;
class UIntInputPort;
class IntArraySelfMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = int64_t;
protected:
	IntVectorInputPort *firstInputPort;
	IntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	IntArraySelfMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // INTARRAYSELFMULNODE_H_H_HEAD__FILE__
