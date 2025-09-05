#ifndef NODERUNSEQUENCEAREASWIDGET_H_H_HEAD__FILE__
#define NODERUNSEQUENCEAREASWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include <alias/type_alias.h>

class NodeRunFunctionSequenceItemWidget;
class NodeRunSequenceWidget;
class IFunctionDeclaration;
class NodeScriptsWidget;
class NodeRunSequenceAreasWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodeRunSequenceWidget *mainWidget;
public:
	NodeRunSequenceAreasWidget( QWidget *parent );
	/// @brief 在指定位置配置节点窗口
	/// @param generater_scripts_widget 调用窗口
	/// @param function_declaration 绘制目标
	/// @param glob_point 全局位置
	/// @param set_point 绘制位置
	/// @return 绘制生成的节点窗口
	virtual NodeRunFunctionSequenceItemWidget * setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
};

#endif // NODERUNSEQUENCEAREASWIDGET_H_H_HEAD__FILE__
