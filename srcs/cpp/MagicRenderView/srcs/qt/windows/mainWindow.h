#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>
#include <QScrollArea>

#include <alias/type_alias.h>

class NodeItemBuilderObj;
class MainScrollAreaWidget;
class NodeItem;
class ItemWidget;
class Application;
class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected: // action 列表
	/// @brief 保存
	QAction *saveAction;
	/// @brief 另存为
	QAction *saveAsAction;
	/// @brief 加载
	QAction *loadAction;
	/// @brief 重启app
	QAction *resetAppAction;
	/// @brief 退出app
	QAction *quitAppAction;
	/// @brief 编译列表
	QAction *builderNodeItemAction;
	/// @brief 重置运行状态
	QAction *resetRunNodeItemAction;
	/// @brief 一次性运行完毕
	QAction *runDisposableAllNodeItemAction;
	/// @brief 链式运行完毕
	QAction *runListAllNodeItemAction;
	/// @brief 节点式运行
	QAction *runNodeItemNodeItemAction;
	/// @brief 快速保存
	QAction *quickSaveCurrentAction;
	/// @brief 快速加载
	QAction *quickLoadCurrentAction;
protected:
	/// @brief 应用实例
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 窗口的工具栏菜单
	QMenuBar *mainMenuBar;
	/// @brief 主要滚动视窗
	MainScrollAreaWidget *mainScrollArea;
	/// @brief 主要操作视窗
	MainWidget *mainWidget;
	/// @brief 记录窗口最大化，最小化，全屏之前的坐标位置
	QPoint oldPos, buffPos;
	/// @brief 记录窗口大小
	QSize windowSize;
	/// @brief 是否记录坐标
	bool makePos;
	/// @brief 当前使用的路径
	QString currentSaveFilePath;
	/// @brief 文件保存路径 key
	QString savefilePathKey;
	/// @brief 编译对象
	NodeItemBuilderObj *nodeItemBuilderObj;
protected:
	virtual void initMenuActions( );
	virtual void initShortcut( );
	virtual void initMenuBar( );
	virtual void initToolBar( );
	virtual void initIcons( );
	virtual void initMainWindowShowStatus( );
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWindow( ) override;
	void setWindowToIndexScreenCentre( size_t index );
	virtual void overSave( );
	virtual void normalSave( );
	virtual void overLoadFile( );
	virtual void normalLoadFile( );
	virtual void quickSave( );
	virtual void quickLoadFile( );
protected:
	void resizeEvent( QResizeEvent *resize_event ) override;
	void changeEvent( QEvent * ) override;
	bool event( QEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void closeEvent( QCloseEvent *event ) override;
public:
	virtual void createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect );;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
