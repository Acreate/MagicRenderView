#ifndef MENUDIRECTOR_H_H_HEAD__FILE__
#define MENUDIRECTOR_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <vector>

class WindowMenu;
class FreeMenu;
class EditorNodeMenu;
class CreateNodeMenu;
class MainWindow;
class MainWidget;
class NodeRunInfo;
class Application;
class NodeDirector;
class QShortcut;
class PrinterDirector;
class QAction;
class SrackInfo;
class MenuDirector : public QObject {
	Q_OBJECT;
protected:
	CreateNodeMenu *createNodeMenu;
	EditorNodeMenu *editorNodeMenu;
	FreeMenu *freeMenu;
	WindowMenu *windowMenu;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	MainWindow *mainWindow;
	MainWidget *mainWidget;
	QString saveFileDirPath;
	QAction *builderNodeVectorBtn;
	QAction *runBuilderAllNodeVectorBtn;
	QAction *runBuilderNextNodeVectorBtn;
	QAction *runBuilderStopNodeVectorBtn;
	QAction *clearBuilderNodeVectorBtn;
	NodeRunInfo *nodeRunBuilderObj;
	std::vector< QAction * > actionVector;
	std::vector< QShortcut * > shortcutVector;
protected Q_SLOTS:
	/// @brief 编译对象清理信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param srack_info 信号堆栈
	/// @param clear_obj 原始信号
	/// @param org_srack_info 原始信号堆栈
	virtual void node_run_info_clear_slot( NodeDirector *signal_obj_ptr, const SrackInfo &srack_info, NodeRunInfo *clear_obj, const SrackInfo &org_srack_info );
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
public:
	MenuDirector( QObject *parent = nullptr );
	~MenuDirector( ) override;
	virtual bool init( );
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_obj_ptr 释放对象指针
	/// @param srack_info 信号行
	void release_signal( MenuDirector *release_obj_ptr, const SrackInfo &srack_info );
};

#endif // MENUDIRECTOR_H_H_HEAD__FILE__
