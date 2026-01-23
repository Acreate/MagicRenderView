#ifndef UINTARRAYSELFADDNODE_H_H_HEAD__FILE__
#define UINTARRAYSELFADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntVectorInputPort;
class UIntOutputPort;
class UIntInputPort;
class UIntArraySelfAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntArraySelfAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // UINTARRAYSELFADDNODE_H_H_HEAD__FILE__
