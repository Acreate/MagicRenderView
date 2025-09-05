#ifndef NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#define NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class IFunctionDeclaration;
class NodeControlItemWidge;
class NodeRunFunctionSequenceItemWidget : public QWidget {
	Q_OBJECT;
public:
	friend class NodeRunSequenceWidget;
	/// @brief 双击时钟
	static std::chrono::system_clock::time_point doubleClickClock;
	/// @brief 双击对象
	static NodeRunFunctionSequenceItemWidget *doubleClickObj;
protected:
	/// @brief 是否显示子节点
	bool showChildStatus = false;
	/// @brief 节点是否有效
	bool itemActive = false;
	/// @brief 父节点
	NodeRunSequenceWidget *itemParent;
	/// @brief 子节点
	NodeRunSequenceWidget *itemChild;
protected:
	NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration );
public:
	~NodeRunFunctionSequenceItemWidget( ) override;
public:
	virtual bool isShowChild( ) const {
		if( itemChild == nullptr )
			return false;
		return showChildStatus;
	}
	virtual bool isItemActve( ) const {
		return itemActive;
	}
	virtual NodeRunSequenceWidget * getItemChild( ) const {
		return itemChild;
	}
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
public:
Q_SIGNALS:
	/// @brief 显示子节点
	/// @param flag true 表示展开，false 表示收缩
	void showStatusChange( bool flag );
	/// @brief 展开选项
	void expandItem( );
	/// @brief 收缩项
	void shrinkage( );
	/// @brief 双击
	void doubleClick( );
	/// @brief 子组件配置最小大小要求被改变
	/// @param min_size 最小大小
	void childReMinSize( const QSize &min_size );
};

#endif // NODERUNFUNCTIONSEQUENCEITEMWIDGET_H_H_HEAD__FILE__
