#ifndef FILEONLYISREADNODE_H_H_HEAD__FILE__
#define FILEONLYISREADNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class BoolOutputPort;
class StringInputPort;
class FileOnlyIsReadNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	BoolOutputPort *isOnlyReadOutputPortPtr;

	int64_t *outIsOnlyReadPtr;
public:
	FileOnlyIsReadNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILEONLYISREADNODE_H_H_HEAD__FILE__
