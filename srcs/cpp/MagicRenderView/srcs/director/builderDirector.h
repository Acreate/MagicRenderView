#ifndef BUILDERDIRECTOR_H_H_HEAD__FILE__
#define BUILDERDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class Application;
class MainWindow;
class BuilderDirector : public QObject {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	Application *instancePtr;
public:
	virtual bool init( );
	virtual bool builderNodeProject( );
	virtual bool nextStepBuilderNode( );
	virtual bool runBuilderBuilderNode( );
	virtual bool stopBuilderBuilderNode( );
};

#endif // BUILDERDIRECTOR_H_H_HEAD__FILE__
