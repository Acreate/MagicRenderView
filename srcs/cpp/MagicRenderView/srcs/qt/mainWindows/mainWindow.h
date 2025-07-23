#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>

class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected:
	/// @brief 窗口的工具栏菜单
	QMenuBar *mainMenuBar;
	/// @brief 主要菜单
	QMenu *mainMenu;
	/// @brief 主要
	MainWidget *mainWidget;
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	void setWindowToIndexScreenCentre( size_t index );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
