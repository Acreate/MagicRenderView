#ifndef BINCREATEARRAYNODE_H_H_HEAD__FILE__
#define BINCREATEARRAYNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

#include "../../../../../node/createNode.h"

class BinVectorOutputPort;
class BinCreateArrayNode : public CreateNode {
	Q_OBJECT;
private:
	using NodeType = uint8_t;
protected:
	BinVectorOutputPort *outputPort;
	std::vector< NodeType > *outputVarPtr;
public:
	BinCreateArrayNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // BINCREATEARRAYNODE_H_H_HEAD__FILE__
