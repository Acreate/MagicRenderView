#ifndef FILELASTCHANGETIMENODE_H_H_HEAD__FILE__
#define FILELASTCHANGETIMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class DateTimeOutputPort;
class StringInputPort;

class FileLastChangeTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	DateTimeOutputPort *lastChangeTimeOutputPortPtr;

	QDateTime *outLastChangeTimePtr;
public:
	FileLastChangeTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILELASTCHANGETIMENODE_H_H_HEAD__FILE__
