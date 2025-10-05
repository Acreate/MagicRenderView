#ifndef MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
#define MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

#include "../windows/mainWindow.h"

class MainScrollAreaWidget : public QScrollArea {
	Q_OBJECT;
protected:
	/// @brief 是否鼠标中键
	int isMidMouse;
	/// @brief 按下时全局位置
	QPoint globalPressPos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalPressPoint;
public:
	MainScrollAreaWidget( MainWindow *main_window );
protected:
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
