#ifndef APPINFONODE_H_H_HEAD__FILE__
#define APPINFONODE_H_H_HEAD__FILE__

#include "../../../processNode.h"

class StringOutputPort;
class AnyVarInputPort;
class AppInfoNode : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *appNameOutputPort;
	StringOutputPort *appPathOutputPort;
	StringOutputPort *builderTimeOutputPort;
	StringOutputPort *builderToolOutputPort;
	StringOutputPort *versionOutputPort;
	QString * appNameVarPtr;
	QString * appPathVarPtr;
	QString * builderTimeVarPtr;
	QString * builderToolVarPtr;
	QString * versionVarPtr;
public:
	AppInfoNode( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "软件/软件信息" ) );
};
#endif // APPINFONODE_H_H_HEAD__FILE__
