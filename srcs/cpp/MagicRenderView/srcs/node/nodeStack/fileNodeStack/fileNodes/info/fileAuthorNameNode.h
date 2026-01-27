#ifndef FILEAUTHORNAMENODE_H_H_HEAD__FILE__
#define FILEAUTHORNAMENODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class IntOutputPort;
class UIntOutputPort;
class StringOutputPort;
class DateTimeOutputPort;
class StringInputPort;
class AnyVarInputPort;
class FileAuthorNameNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePtahInputPortPtr;

	StringOutputPort *authorNameOutputPortPtr;


	QString *outAuthorNamePtr;

public:
	FileAuthorNameNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // FILEAUTHORNAMENODE_H_H_HEAD__FILE__
