#ifndef NODELISTWIDGET_H_H_HEAD__FILE__
#define NODELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Application;
class GridWidget;
class QHBoxLayout;
class QListWidget;
class NodeListWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 主要窗口布局
	QHBoxLayout *mainLayout;
	/// @brief 节点类型
	QListWidget *nodeTypeList;
	/// @brief 节点生成器列表
	GridWidget* nodeGeneraterList;
	/// @brief 应用单例指针
	Application *applicationInstancePtr;
public:
	NodeListWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeListWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODELISTWIDGET_H_H_HEAD__FILE__
