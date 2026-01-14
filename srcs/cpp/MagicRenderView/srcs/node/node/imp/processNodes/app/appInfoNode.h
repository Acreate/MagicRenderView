#ifndef APPINFONODE_H_H_HEAD__FILE__
#define APPINFONODE_H_H_HEAD__FILE__

#include <node/node/processNode.h>

class IntOutputPort;
class DateTimeOutputPort;
class StringOutputPort;
class AnyVarInputPort;
class AppInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *appNameOutputPort;
	StringOutputPort *appPathOutputPort;
	DateTimeOutputPort *appStartTimeOutputPort;
	DateTimeOutputPort *builderTimeOutputPort;
	StringOutputPort *builderToolOutputPort;
	StringOutputPort *versionOutputPort;
	IntOutputPort *isSharedOutputPort;
	QString * appNameVarPtr;
	QString * appPathVarPtr;
	QDateTime * builderTimeVarPtr;
	QDateTime * appStartTimeVarPtr;
	QString * builderToolVarPtr;
	QString * versionVarPtr;
	int64_t * isShared;
public:
	AppInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "生成/软件信息" ) );
};
#endif // APPINFONODE_H_H_HEAD__FILE__
