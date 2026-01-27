#ifndef FILESIZENODE_H_H_HEAD__FILE__
#define FILESIZENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class UIntOutputPort;
class StringInputPort;
class FileSizeNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	UIntOutputPort *fileSizeOutputPortPtr;

	uint64_t *outFileSizePtr;
public:
	FileSizeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILESIZENODE_H_H_HEAD__FILE__
