#ifndef UINTDIVNODE_H_H_HEAD__FILE__
#define UINTDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntOutputPort;
class UIntInputPort;
class UIntDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint64_t;
protected:
	UIntInputPort *firstInputPort;
	UIntInputPort *secondInputPort;
	UIntOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	UIntDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // UINTDIVNODE_H_H_HEAD__FILE__
