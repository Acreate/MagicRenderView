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
	/// @brief 节点被释放信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param release_node 释放指针
	/// @param srack_info 堆栈信息
	virtual void release_node_slot( NodeDirector *signal_obj_ptr, Node *release_node, const SrackInfo &srack_info );
	/// @brief 节点端口发生释放时，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_port 释放的源端口对象指针
	/// @param target_prot 释放的目标端口对象指针
	/// @param srack_info 堆栈信息
	virtual void finish_release_port_link_slot( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
	/// @brief 节点端口发生链接时，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_port 链接的源端口对象指针
	/// @param target_prot 链接的目标端口对象指针
	/// @param srack_info 堆栈信息
	virtual void finish_create_port_link_slot( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info );
	/// @brief 节点依赖发生释放时候，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_node 依赖节点
	/// @param ref_node 被删除的依赖
	/// @param srack_info 堆栈信息
	virtual void finish_release_ref_node_slot( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info );
	/// @brief 节点依赖发生增持时候，产生该信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_node 依赖节点
	/// @param ref_node 被增持的依赖
	/// @param srack_info 堆栈信息
	virtual void finish_create_ref_node_slot( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info );
	/// @brief 节点错误信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param error_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param error_type 错误类型
	/// @param error_msg 错误消息
	virtual void error_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *error_node, const SrackInfo &org_srack_info, NodeEnum::ErrorType error_type, const QString &error_msg );
	/// @brief 建议节点信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param advise_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	/// @param advise_type 建议类型
	/// @param advise_msg 建议消息
	virtual void advise_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *advise_node, const SrackInfo &org_srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg );
	/// @brief 节点完成运行信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param signal_srack_info 当前信号产生堆栈信息
	/// @param finish_node 原始信号对象
	/// @param org_srack_info 原始对象堆栈信号信息
	virtual void finish_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *finish_node, const SrackInfo &org_srack_info );
	/// @brief 成功创建节点信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param create_node 创建对象
	/// @param srack_info 堆栈信息
	virtual void finish_create_node_slot( NodeDirector *signal_obj_ptr, Node *create_node, const SrackInfo &srack_info );
	/// @brief 节点创建失败信号
	/// @param signal_obj_ptr 信号对象指针
	/// @param create_name 节点名称
	/// @param error_type_info 错误类型
	/// @param error_msg 失败信息
	/// @param srack_info 堆栈信息
	virtual void error_create_node_slot( NodeDirector *signal_obj_ptr, const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg, const SrackInfo &srack_info );
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
