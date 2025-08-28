#ifndef NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
#define NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QTreeWidget.h>

#include <alias/type_alias.h>

class Application;
class NodeGeneraterListWidget;
class NodeGeneraterItem;
class IFunStack;
class NodeTypeTreeListWidget : public QTreeWidget {
	Q_OBJECT;
protected:
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 树形结构的顶端选项
	QTreeWidgetItem *topItem;;
	/// @brief 选项绑定指针
	std_vector_pairt< QTreeWidgetItem *, const NodeGeneraterItem * > funStackBind;
	/// @brief 绑定的生成列表窗口
	NodeGeneraterListWidget *bindNodeGeneraterListWidget;
protected:
	QTreeWidgetItem * initTopItem( const std_vector< std::shared_ptr< IFunStack > > &fun_stacks );
public:
	NodeTypeTreeListWidget( NodeGeneraterListWidget *node_generater_list_widget, QWidget *parent = nullptr );
	virtual QTreeWidgetItem * appendItem( const std_vector< std::shared_ptr< IFunStack > > &fun_stacks );
Q_SIGNALS:
	void typeItemDoubleClicked( QTreeWidgetItem *item, int column );
};

#endif // NODETYPETREELISTWIDGET_H_H_HEAD__FILE__
