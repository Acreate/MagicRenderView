#ifndef READFILETEXTNODE_H_H_HEAD__FILE__
#define READFILETEXTNODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>
class StringOutputPort;
class StringInputPort;
class ReadFileTextNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringInputPort *filePathInputPort;
	StringOutputPort *outTextPort;
	QString *outTextPtr;
public:
	ReadFileTextNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extern_NodeTypeName_Function( );
};
#endif // READFILETEXTNODE_H_H_HEAD__FILE__
