#ifndef NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunFunctionSequenceItemWidget;
class NodeRunSequenceWidget : public QWidget {
	Q_OBJECT;
public:
	friend class NodeRunFunctionSequenceItemWidget;
protected:
	/// @brief 顶级选项
	std_list< NodeRunFunctionSequenceItemWidget * > topItem;
	/// @brief 当前展开的节点
	NodeRunFunctionSequenceItemWidget *currentEextendItem;
	/// @brief 选项宽度
	int itemWidth;
	/// @brief 选项高度
	int itemHeight;
	/// @brief 选项间隔宽度
	int itemSpaceWidth;
	/// @brief 用于选项行空格
	int itemSpaceHeight;
public:
	NodeRunSequenceWidget( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeRunSequenceWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
public:	/// @brief 在指定位置配置节点窗口
	/// @param generater_scripts_widget 调用窗口
	/// @param function_declaration 绘制目标
	/// @param glob_point 全局位置
	/// @param set_point 绘制位置
	/// @return 绘制生成的节点窗口
	virtual NodeRunFunctionSequenceItemWidget * setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
	/// @brief 重绘子窗口（脚本节点）
	/// @return 重绘列表
	virtual void updateNodeWidget( );
protected:
	/// @brief 展开选项
	/// @param show_item_widget 选项
	virtual bool expandItem( const NodeRunFunctionSequenceItemWidget *show_item_widget );
	/// @brief 收缩项
	/// @param hide_item_widget 收缩的项
	virtual bool shrinkage( const NodeRunFunctionSequenceItemWidget *hide_item_widget );
	/// @brief 删除项
	/// @param remove_item_widget 删除项项
	virtual bool removeItem( const NodeRunFunctionSequenceItemWidget *remove_item_widget );
	/// @brief 更新展开选项的大小
	virtual void updateExpandItem( );
};

#endif // NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
