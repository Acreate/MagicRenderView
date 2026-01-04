#ifndef BUILDERDIRECTOR_H_H_HEAD__FILE__
#define BUILDERDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class NormalApplicationToolBar;
class NormalApplicationMenu;
class BuilderApplicationToolBar;
class BuilderApplicationMenu;
class NodeRunInfo;
class NodeDirector;
class Application;
class MainWindow;
class BuilderDirector : public QObject {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	NodeRunInfo *nodeRunInfo;
protected:
	std::vector< BuilderApplicationMenu * > menus;
	std::vector< BuilderApplicationToolBar * > toolBars;
protected:
	virtual void updateBuilderActionObjInfo( );
	virtual void resetBuilderActionObjInfo( );
	virtual void validBuilderActionObjInfo( );
	virtual void removeMenu( NormalApplicationMenu *remove_target );
	virtual void removeToolBar( NormalApplicationToolBar *remove_target );
public:
	~BuilderDirector( ) override;
	virtual bool init( );
	virtual bool addMenu( BuilderApplicationMenu *builder_application_menu );
	virtual bool addToolBar( BuilderApplicationToolBar *builder_application_tool_bar );
	virtual bool builderNodeProject( );
	virtual bool nextStepBuilderNode( );
	virtual bool runBuilderBuilderNode( );
	virtual bool stopBuilderBuilderNode( );
	virtual NodeRunInfo * getNodeRunInfo( ) const { return nodeRunInfo; }
};

#endif // BUILDERDIRECTOR_H_H_HEAD__FILE__
