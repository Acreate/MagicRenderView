#ifndef EDITORDIRECTOR_H_H_HEAD__FILE__
#define EDITORDIRECTOR_H_H_HEAD__FILE__

#include <QObject>

class Application;
class MainWindow;
class EditorDirector : public QObject {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	Application *instancePtr;
public:
	virtual bool init( );
	virtual bool copySelectNodeInfo( );
	virtual bool pastePointNodeInfo( );
	virtual bool cutSelectNodeInfo( );
	virtual bool cancelNodeInfo( );
	virtual bool deleteSelectNodeInfo( );
	virtual bool calculateNodeRenderSize( );
};

#endif // EDITORDIRECTOR_H_H_HEAD__FILE__
