#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>

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
class DrawNodeWidget;
class DrawLinkWidget;
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
	DrawNodeWidget *drawNodeWidget;
	DrawLinkWidget *drawLinkWidget;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	QToolBar *fileToolBar;
	QToolBar *projectToolBar;
	QString saveFileDirPath;
	std::vector< QShortcut * > shortcutVector;
	std::vector< QAction * > actionVector;
	QMenuBar *appMenuBar;
	QMenu *fileMenu;
	QMenu *projectMenu;
	QAction *builderNodeVectorBtn;
	QAction *runBuilderAllNodeVectorBtn;
	QAction *runBuilderNextNodeVectorBtn;
	QAction *runBuilderStopNodeVectorBtn;
	QAction *clearBuilderNodeVectorBtn;
	NodeRunInfo *nodeRunBuilderObj;
protected Q_SLOTS:
	/// @brief 编译对象清理信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param srack_info 信号堆栈
	/// @param clear_obj 原始信号
	/// @param org_srack_info 原始信号堆栈
	virtual void node_run_info_clear_slot( NodeDirector *signal_obj_ptr, const SrackInfo &srack_info, NodeRunInfo *clear_obj, const SrackInfo &org_srack_info );
protected:
	MainWindow( );
	virtual bool init( );
public:
	~MainWindow( ) override;
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void savePorjectToFile( );
	virtual void loadPorjectAtFile( );
	virtual void unDownloadPorjectAtFile( );
	virtual void copyNodeInfo( );
	virtual void pasteNodeInfo( );
	virtual void cutNodeInfo( );
	virtual void cancelNodeInfo( );
	virtual void deleteNodeInfo( );
	virtual void builderProject( );
	virtual void runAllProject( );
	virtual void runNextProject( );
	virtual void stopProject( );
	virtual void clearProject( );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	bool event( QEvent *event ) override;
Q_SIGNALS:
	void release_signal( MainWindow *release_ptr );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
