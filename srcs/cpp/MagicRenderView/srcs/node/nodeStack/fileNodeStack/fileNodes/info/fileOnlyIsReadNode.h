#ifndef FILEONLYISREADNODE_H_H_HEAD__FILE__
#define FILEONLYISREADNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class IntOutputPort;
class UIntOutputPort;
class StringOutputPort;
class DateTimeOutputPort;
class StringInputPort;
class AnyVarInputPort;
class FileOnlyIsReadNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;
	StringOutputPort *filePtahOutputPortPtr;
	StringOutputPort *dirNameOutputPortPtr;
	StringOutputPort *baseNameOutputPortPtr;
	StringOutputPort *authorNameOutputPortPtr;
	DateTimeOutputPort *createTimeOutputPortPtr;
	DateTimeOutputPort *lastChangeTimeOutputPortPtr;
	DateTimeOutputPort *lastReadTimeOutputPortPtr;
	UIntOutputPort *fileSizeOutputPortPtr;
	IntOutputPort *isOnlyReadOutputPortPtr;
	IntOutputPort *isExisOutputPortPtr;
	IntOutputPort *isFileOutputPortPtr;

	QString *outFilePtahPtr;
	QString *outDirNamePtr;
	QString *outBaseNamePtr;
	QString *outAuthorNamePtr;
	QDateTime *outCreateTimePtr;
	QDateTime *outLastChangeTimePtr;
	QDateTime *outLastReadTimePtr;
	uint64_t *outFileSizePtr;
	int64_t *outIsOnlyReadPtr;
	int64_t *outIsExisPtr;
	int64_t *outisFilePtr;
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
