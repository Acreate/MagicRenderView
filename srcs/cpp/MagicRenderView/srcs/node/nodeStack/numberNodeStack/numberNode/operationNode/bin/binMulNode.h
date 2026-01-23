#ifndef BINMULNODE_H_H_HEAD__FILE__
#define BINMULNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class BinOutputPort;
class BinInputPort;
class BinMulNode : public ProcessNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinInputPort *firstInputPort;
	BinInputPort *secondInputPort;
	BinOutputPort *outputPort;
	NodeType *outputVarPtr;
public:
	BinMulNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};

#endif // BINMULNODE_H_H_HEAD__FILE__
