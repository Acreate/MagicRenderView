#ifndef FILEINFONODE_H_H_HEAD__FILE__
#define FILEINFONODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class IntOutputPort;
class UIntOutputPort;
class StringOutputPort;
class DateTimeOutputPort;
class StringInputPort;
class AnyVarInputPort;
class FileInfoNode : public ProcessNode {
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
public:
	FileInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "单元/路径/路径信息" ) );
};
#endif // FILEINFONODE_H_H_HEAD__FILE__
