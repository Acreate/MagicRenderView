#ifndef FILELASTREADTIMENODE_H_H_HEAD__FILE__
#define FILELASTREADTIMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class DateTimeOutputPort;
class StringInputPort;

class FileLastReadTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	DateTimeOutputPort *lastReadTimeOutputPortPtr;

	QDateTime *outLastReadTimePtr;
	
public:
	FileLastReadTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILELASTREADTIMENODE_H_H_HEAD__FILE__
