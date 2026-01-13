#ifndef READFILETEXTNODE_H_H_HEAD__FILE__
#define READFILETEXTNODE_H_H_HEAD__FILE__

#include "../../../processNode.h"
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
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "单元/文件/读取/字符串" ) );
};
#endif // READFILETEXTNODE_H_H_HEAD__FILE__
