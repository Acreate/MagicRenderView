#ifndef STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#define STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QPushButton;
class NodeItemInfo;
class VarGenerate;
class NodeDirector;
class Application;
class NodeItem;
class StartNodeInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
	NodeItemInfo *currentNodeItemInfo;
protected:
	std_vector< std_vector< NodeItemInfo * > > runList;
	const NodeItemInfo *errorNodeItemInfo;
protected:
	Application *application;
	NodeDirector *nodeDirector;
	VarGenerate *varGenerate;
	QWidget *toolBtnVector;
	QPushButton *runBtn;
	QPushButton *builderBtn;
protected:
	virtual void run( );
	virtual void builder( );
	virtual void updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info );
	virtual void toolWidgetMoveToMid( );
	virtual bool fillLinkNodeInfo( const NodeItemInfo *node_item );
	virtual void removeNodeInfo( const NodeItemInfo *node_item );
public:
	StartNodeInfoWidget( NodeItem *node_item );
	/// @brief 检查运行列表当中是否存在指定节点
	/// @param node_item 匹配的节点
	/// @return true 表示存在
	virtual bool hasNodeInfo( const NodeItem *node_item );
	/// @brief 依赖节点是否合法，如在运行链当中存在该输入节点时返回 true
	/// @param input_node_item 该节点作为输入节点
	/// @return 合法返回 true
	virtual bool inputNodeItemLegitimate( const NodeItemInfo *input_node_item );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // STARTNODEINFOWIDGET_H_H_HEAD__FILE__
