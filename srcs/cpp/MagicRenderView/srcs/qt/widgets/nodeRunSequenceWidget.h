#ifndef NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class NodeRunSequenceItemWidget;
class NodeRunSequenceItemFunctionWidget;
class NodeRunFunctionSequenceItem;
class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunSequenceWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 顶级选项
	NodeRunFunctionSequenceItem *rootItem;
public:
	NodeRunSequenceWidget( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeRunSequenceWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
public:
	/// @brief 在指定位置配置节点窗口
	/// @param generater_scripts_widget 调用窗口
	/// @param function_declaration 绘制目标
	/// @param glob_point 全局位置
	/// @param set_point
	/// @return 绘制生成的节点窗口
	virtual NodeRunFunctionSequenceItem * setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
	virtual void itemSubWidgetShowEvent( NodeRunSequenceItemWidget *widget, bool is_show, NodeRunFunctionSequenceItem *item );
	virtual void itemThisWidgetShowEvent( NodeRunSequenceItemFunctionWidget *widget, bool is_show, NodeRunFunctionSequenceItem *item );
	virtual void itemThisWidgetCurrentItemDoubleClick( NodeRunSequenceItemFunctionWidget *widget, NodeRunFunctionSequenceItem *item );
};

#endif // NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
