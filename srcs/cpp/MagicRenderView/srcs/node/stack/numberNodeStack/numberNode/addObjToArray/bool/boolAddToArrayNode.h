#ifndef BOOLADDTOARRAYNODE_H_H_HEAD__FILE__
#define BOOLADDTOARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BoolVectorOutputPort;
class BoolVectorInputPort;
class BoolInputPort;
class BinVectorOutputPort;
class BinInputPort;
class BinVectorInputPort;
class BoolAddToArrayNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = bool;
protected:
	BoolVectorInputPort *firstInputPort;
	BoolInputPort *secondInputPort;
	BoolVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	BoolAddToArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // BOOLADDTOARRAYNODE_H_H_HEAD__FILE__
