#ifndef READFILEBINDATANODE_H_H_HEAD__FILE__
#define READFILEBINDATANODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class UIntOutputPort;
class BinVectorOutputPort;
class StringInputPort;
class ReadFileBinDataNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePathInputPort;
	BinVectorOutputPort *outBinVectorPort;
	std::vector< uint8_t > *outVectorPtr;
public:
	ReadFileBinDataNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // READFILEBINDATANODE_H_H_HEAD__FILE__
