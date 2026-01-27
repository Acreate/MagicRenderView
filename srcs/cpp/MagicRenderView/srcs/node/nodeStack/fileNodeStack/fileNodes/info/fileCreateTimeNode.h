#ifndef FILECREATETIMENODE_H_H_HEAD__FILE__
#define FILECREATETIMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class IntOutputPort;
class UIntOutputPort;
class StringOutputPort;
class DateTimeOutputPort;
class StringInputPort;
class AnyVarInputPort;
class FileCreateTimeNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	DateTimeOutputPort *createTimeOutputPortPtr;



	QDateTime *outCreateTimePtr;

public:
	FileCreateTimeNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILECREATETIMENODE_H_H_HEAD__FILE__
