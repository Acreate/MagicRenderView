#ifndef UINTARRAYADDNODE_H_H_HEAD__FILE__
#define UINTARRAYADDNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntVectorInputPort;
class UIntVectorOutputPort;
class UIntOutputPort;
class UIntInputPort;
class UIntArrayAddNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntVectorInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	UIntArrayAddNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // UINTARRAYADDNODE_H_H_HEAD__FILE__
