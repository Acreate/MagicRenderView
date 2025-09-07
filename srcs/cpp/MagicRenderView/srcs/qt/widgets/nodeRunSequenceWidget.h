#ifndef NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class NodeRunFunctionSequenceItem;
class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunSequenceWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 顶级选项
	NodeRunFunctionSequenceItem *rootItem;
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
	void showEvent( QShowEvent *event ) override;
public:
	/// @brief 在指定位置配置节点窗口
	/// @param generater_scripts_widget 调用窗口
	/// @param function_declaration 绘制目标
	/// @param glob_point 全局位置
	/// @param set_point 绘制位置
	/// @return 绘制生成的节点窗口
	virtual NodeRunFunctionSequenceItem * setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
};

#endif // NODERUNSEQUENCEWIDGET_H_H_HEAD__FILE__
