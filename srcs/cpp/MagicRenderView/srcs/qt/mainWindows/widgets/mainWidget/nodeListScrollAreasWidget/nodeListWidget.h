#ifndef NODELISTWIDGET_H_H_HEAD__FILE__
#define NODELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class NodeTypeTreeListWidget;
class NodeGeneraterItem;
class NodeGeneraterListWidget;
class QScrollArea;
class IFunStack;
class QTreeWidgetItem;
class Application;
class GridWidget;
class QHBoxLayout;
class QListWidget;
class QTreeWidget;
class NodeListWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 节点类型
	NodeTypeTreeListWidget *nodeTypeTreeListWidget;
	/// @brief 节点生成器列表
	NodeGeneraterListWidget *nodeGeneraterListWidget;
	/// @brief 鼠标是否按下
	bool mouseIsPress;
	/// @brief 拖拽的窗口
	QWidget *dragWidgetSize;
	/// @brief 树形结构的顶端选项
	std_vector< QTreeWidgetItem * > topItemS;
	/// @brief 选项绑定指针
	std_vector_pairt< QTreeWidgetItem *, const NodeGeneraterItem * > funStackBind;
public:
	NodeListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeListWidget( ) override;
	virtual QWidget * mouseToPoint( const QPoint &point );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void updateWidgetListLayout( const QSize &old_size, const QSize &current_size );
	void writeHeightIni( ) const;
protected:
	void itemDoubleClicked( QTreeWidgetItem *item, int column );
};

#endif // NODELISTWIDGET_H_H_HEAD__FILE__
