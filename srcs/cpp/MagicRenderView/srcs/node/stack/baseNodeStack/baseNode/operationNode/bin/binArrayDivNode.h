#ifndef BINARRAYDIVNODE_H_H_HEAD__FILE__
#define BINARRAYDIVNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BinVectorOutputPort;
class BinInputPort;
class BinVectorInputPort;
class BinArrayDivNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinVectorInputPort *firstInputPort;
	BinInputPort *secondInputPort;
	BinVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	BinArrayDivNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // BINARRAYDIVNODE_H_H_HEAD__FILE__
