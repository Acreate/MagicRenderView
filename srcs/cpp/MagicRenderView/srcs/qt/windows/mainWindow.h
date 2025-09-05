#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>

class Application;
class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected:
	Application *appInstance;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 窗口的工具栏菜单
	QMenuBar *mainMenuBar;
	/// @brief 主要菜单
	QMenu *mainMenu;
	/// @brief 主要
	MainWidget *mainWidget;
	/// @brief 记录窗口最大化，最小化，全屏之前的坐标位置
	QPoint oldPos, buffPos;
	/// @brief 是否记录坐标
	bool makePos;
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~MainWindow( ) override;
	void setWindowToIndexScreenCentre( size_t index );
protected:
	void resizeEvent( QResizeEvent *resize_event ) override;
	void changeEvent( QEvent * ) override;
	bool event( QEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
