#ifndef NODEINFOWIDGET_H_H_HEAD__FILE__
#define NODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include "../../../enums/widgetEnum.h"

class MainWidgetScrollArea;
class VarDirector;
class BottomNodeInfoTool;
class NodeInfoTitle;
class EditorNodeInfoScrollArea;
class QLabel;
class Node;
class MainWindow;
class NodeInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	WidgetEnum::ShowType showPosType;
	MainWindow *parentMainWindow;
	MainWidgetScrollArea *mainWidgetScrollArea;
	Node *node;
	NodeInfoTitle *titile;
	BottomNodeInfoTool *buttonWidget;
	EditorNodeInfoScrollArea *editorNodeInfoScrollArea;
	VarDirector *varDirector;
	QScrollBar *vScrollBar;
	QScrollBar *hScrollBar;
	int offsetY;
	int offsetX;
	int topOffsetY;
	int leftOffsetX;
public:
	NodeInfoWidget( MainWindow *parent );
	~NodeInfoWidget( ) override;
	virtual bool isNodeTypeInfoWidget( Node *check_node_ptr ) const;
	virtual bool initNodeInfo( Node *check_node_ptr );
	/// @brief 释放资源
	/// @return 资源释放数量
	virtual size_t releaseVar( ) { return 0; }
	/// @brief 清理资源指向内容（值配置为 nullptr，不会进行释放，释放请使用 @code NodeInfoWidget::releaseVar() @endcode )
	/// @return 清理数量
	virtual size_t clearVarPtr( ) { return 0; }
	/// @brief 拷贝窗口数据到节点
	/// @param copy_cout 拷贝数量
	/// @return 成功执行返回 true
	virtual bool copyVarToNode( size_t &copy_cout ) { return true; }
	/// @brief 获取节点
	/// @return 节点
	virtual Node * getNode( ) const { return node; }
	/// @brief 获取标题
	/// @return 标题
	virtual QString getTitleText( ) const;
	virtual void showNodeInfoWidget( WidgetEnum::ShowType show_pos_type );
protected:
	virtual void okButtonEvent( ) { }
	virtual void cancelButtonEvent( ) { }
protected:
	bool eventFilter( QObject *event_obj_ptr, QEvent *event_type ) override;
	bool event( QEvent * ) override;
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	void release_signal( NodeInfoWidget *release_ptr );
	void hide_signal( NodeInfoWidget *hide_ptr );
	void show_signal( NodeInfoWidget *show_ptr );
	void ok_signal( NodeInfoWidget *send_signal_ptr, EditorNodeInfoScrollArea *data_change_widget );
	void cancel_signal( NodeInfoWidget *send_signal_ptr, EditorNodeInfoScrollArea *data_change_widget );
};

#endif // NODEINFOWIDGET_H_H_HEAD__FILE__
