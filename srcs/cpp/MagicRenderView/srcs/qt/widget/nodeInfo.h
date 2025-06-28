#ifndef NODEINFO_H_H_HEAD__FILE__
#define NODEINFO_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
class MainWindow;
class QVBoxLayout;
class QBoxLayout;
class INodeWidget;
class NodeInfo : public QWidget {
	Q_OBJECT;
protected:
	INodeWidget *currentNodeWidget;
	QVBoxLayout *mainLayout;
	MainWindow *mainWindow;
public:
	NodeInfo( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	/// @brief 显示节点信息
	/// @param node_widget 显示的节点信息
	virtual void setNodeWidget( INodeWidget *node_widget );
	/// @brief 获取当前显示的节点
	/// @return 当前节点
	virtual INodeWidget * getNodeWidget( ) const {
		return currentNodeWidget;
	}
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual void setMainWindow( MainWindow *const main_window ) { mainWindow = main_window; }
};
#endif // NODEINFO_H_H_HEAD__FILE__
