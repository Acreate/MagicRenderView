﻿#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>

class QPushButton;
class ScrollNodeList;
class ScrollNodeInfo;

class ScrollNodeGraph;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected:
	/// @brief 绘制节点
	ScrollNodeGraph *nodeGraph;
	/// @brief 节点信息
	ScrollNodeInfo *nodeInfo;
	/// @brief 节点列表
	ScrollNodeList *nodeList;
	/// @brief 窗口的工具栏菜单
	QMenuBar *mainMenuBar;
	/// @brief 列表显示按钮
	QPushButton* listBtn;
	/// @brief 信息显示按钮
	QPushButton* infoBtn;
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	void setWindowToIndexScreenCentre( size_t index );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
