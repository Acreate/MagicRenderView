#ifndef FILEEXISDISKNODE_H_H_HEAD__FILE__
#define FILEEXISDISKNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BoolOutputPort;
class StringInputPort;
class FileExisDiskNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	BoolOutputPort *isExisOutputPortPtr;

	bool *outIsExisPtr;
public:
	FileExisDiskNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILEEXISDISKNODE_H_H_HEAD__FILE__
