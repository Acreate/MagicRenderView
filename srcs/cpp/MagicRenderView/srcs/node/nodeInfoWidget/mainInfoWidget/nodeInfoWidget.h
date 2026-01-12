#ifndef NODEINFOWIDGET_H_H_HEAD__FILE__
#define NODEINFOWIDGET_H_H_HEAD__FILE__

#include <QScrollArea>

#include "../../../enums/widgetEnum.h"

class QMenuBar;
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
private:
	friend class NodeDirector;
protected:
	WidgetEnum::ShowType showPosType;
	NodeInfoTitle *titile;
	BottomNodeInfoTool *bottomButtonTool;
	EditorNodeInfoScrollArea *editorNodeInfoScrollArea;
	VarDirector *varDirector;
	QScrollBar *vScrollBar;
	QScrollBar *hScrollBar;
	QMenuBar *mainWindowMenuBar;
public:
	NodeInfoWidget( );
	~NodeInfoWidget( ) override;
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
	virtual bool checkNodeValid(Node* check_node_ptr);
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
	virtual Node * getNode( ) const;
	/// @brief 获取标题
	/// @return 标题
	virtual QString getTitleText( ) const;
protected:
	/// @brief 创建节点时候发生
	/// @param node_ref_link_info 创建的节点的引用
	/// @param target_node_ref 引用目标
	virtual void newNodeRefLinkInfo( Node *node_ref_link_info, Node *target_node_ref ) { }
	/// @brief 移除依赖时候发生该消息
	/// @param node_ref_link_info 移除的节点引用
	/// @param target_node_ref 移除的目标
	virtual void removeRefNodeRefLinkInfo( Node *node_ref_link_info, Node *target_node_ref ) { }
protected:
	virtual void updateLayout( );
protected:
	virtual void okButtonEvent( );
	virtual void cancelButtonEvent( );
protected:
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
