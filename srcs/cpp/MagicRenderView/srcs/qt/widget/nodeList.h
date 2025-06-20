#ifndef NODELIST_H_H_HEAD__FILE__
#define NODELIST_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include <alias/type_alias.h>

class QVBoxLayout;
class INodeWidget;
class MainWindow;
class NodeList : public QWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	std_vector< INodeWidget * > currentNodeWidgets;
	QVBoxLayout *mainLayout;
public:
	NodeList( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) );
	/// @brief 清空面板
	virtual void clearInfoPanel( );
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual void setMainWindow( MainWindow *const main_window ) { mainWindow = main_window; }
	virtual const std_vector<INodeWidget *> & getCurrentNodeWidgets( ) const { return currentNodeWidgets; }
	virtual void setCurrentNodeWidgets( const std_vector<INodeWidget *> &current_node_widgets );
};
#endif // NODELIST_H_H_HEAD__FILE__
