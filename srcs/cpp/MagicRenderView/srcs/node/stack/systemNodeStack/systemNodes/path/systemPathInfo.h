#ifndef SYSTEMPATHINFO_H_H_HEAD__FILE__
#define SYSTEMPATHINFO_H_H_HEAD__FILE__

#include <node/node/processNode.h>
#include <QStandardPaths>

class StringOutputPort;
class SystemPathInfo : public ProcessNode {
	Q_OBJECT;
protected:
	StringOutputPort *fontsPathOutputPortPtr;
	StringOutputPort *applicationsPathOutputPortPtr;
	StringOutputPort *appLocalDataPathOutputPortPtr;
	StringOutputPort *genericDataPathOutputPortPtr;
	StringOutputPort *runtimePathOutputPortPtr;
	StringOutputPort *configPathOutputPortPtr;
	StringOutputPort *genericCachePathOutputPortPtr;
	StringOutputPort *genericConfigPathOutputPortPtr;
	StringOutputPort *appConfigPathOutputPortPtr;
	StringOutputPort *publicSharePathOutputPortPtr;
	StringOutputPort *templatesPathOutputPortPtr;
	StringOutputPort *statePathOutputPortPtr;
	StringOutputPort *genericStatePathOutputPortPtr;
	StringOutputPort *desktopPathOutputPortPtr;
	StringOutputPort *documentsPathOutputPortPtr;
	StringOutputPort *downloadsPathOutputPortPtr;
	StringOutputPort *picturesPathOutputPortPtr;
	StringOutputPort *musicPathOutputPortPtr;
	StringOutputPort *videosPathOutputPortPtr;
	StringOutputPort *homePathOutputPortPtr;
	StringOutputPort *appDataPathOutputPortPtr;
	StringOutputPort *cachePathOutputPortPtr;
	StringOutputPort *tempPathOutputPortPtr;

	QString *fontsPathPtr;
	QString *applicationsPathPtr;
	QString *appLocalDataPathPtr;
	QString *genericDataPathPtr;
	QString *runtimePathPtr;
	QString *configPathPtr;
	QString *genericCachePathPtr;
	QString *genericConfigPathPtr;
	QString *appConfigPathPtr;
	QString *publicSharePathPtr;
	QString *templatesPathPtr;
	QString *statePathPtr;
	QString *genericStatePathPtr;
	QString *desktopPathPtr;
	QString *documentsPathPtr;
	QString *downloadsPathPtr;
	QString *picturesPathPtr;
	QString *musicPathPtr;
	QString *videosPathPtr;
	QString *homePathPtr;
	QString *appDataPathPtr;
	QString *cachePathPtr;
	QString *tempPathPtr;
protected:
	virtual void writableLocationPath ( QString &result_path, const QStandardPaths::StandardLocation &standard_location_type );
public:
	SystemPathInfo( const QString &node_name );
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	bool readyNodeRunData( ) override;
	bool fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "系统/路径信息" ) );
};
#endif // SYSTEMPATHINFO_H_H_HEAD__FILE__
