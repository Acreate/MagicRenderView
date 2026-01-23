#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

class BuilderApplicationToolBar;
class FileApplicationMenu;
class ProjectApplicationMenu;
class EditorApplicationMenu;
class HelpApplicationMenu;
class AboutApplicationWindow;
class NormalApplicationToolBar;
class NormalApplicationAction;
class NormalApplicationMenu;
class BuilderApplicationMenu;
class NodeRunInfo;
namespace NodeEnum {
	enum class CreateType;
	enum class AdviseType;
	enum class ErrorType;
}
class OutputPort;
class InputPort;
class SrackInfo;
class Node;
class PrinterDirector;
class NodeDirector;
class MainWidgetScrollArea;
class MainWidget;
class Application;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class Application;
protected:
	MainWidgetScrollArea *mainWidgetScrollArea;
	MainWidget *mainWidget;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	QString saveFileDirPath;
	QMenuBar *appMenuBar;
	ProjectApplicationMenu *projectMenu;
	BuilderApplicationMenu *builderMenu;
	FileApplicationMenu *fileMenu;
	EditorApplicationMenu *editorMenu;
	HelpApplicationMenu *helpMenu;

	BuilderApplicationToolBar *builderToolBar;
	AboutApplicationWindow* aboutApplicationWindowPtr;
protected:
	MainWindow( );
	virtual bool init( );
	
protected Q_SLOTS:
	virtual void selectNode_Slot( MainWidget *sender_signal_ptr, Node *select_node_ptr );
	virtual void triggActionSignal( NormalApplicationAction *action );
	virtual void triggMenuActionSignal( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action );
	virtual void triggToolbarActionSignal( NormalApplicationToolBar *normal_application_tool_bar, NormalApplicationAction *action );
public:
	~MainWindow( ) override;
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual bool popAboutApplicationWindow();
public:
	virtual bool copySelectNodeInfo( );
	virtual bool pastePointNodeInfo( );
	virtual bool cutSelectNodeInfo( );
	virtual bool cancelNodeInfo( );
	virtual bool deleteSelectNodeInfo( );
	virtual bool calculateNodeRenderSize( );
	virtual bool runToNode( Node* target_node );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	bool event( QEvent *event ) override;
	void closeEvent( QCloseEvent *event ) override;
Q_SIGNALS:
	void release_signal( MainWindow *release_ptr );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
