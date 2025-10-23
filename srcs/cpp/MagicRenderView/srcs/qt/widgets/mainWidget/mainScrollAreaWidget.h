#ifndef MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
#define MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class MainWidget;
class MainWindow;
class MainScrollAreaWidget : public QScrollArea {
	Q_OBJECT;
protected:
	/// @brief 是否鼠标中键
	int isMidMouse;
	/// @brief 按下时全局位置
	QPoint globalPressPos;
	/// @brief 按下时当前窗口位置
	QPoint fromGlobalPressPoint;
	MainWindow *mainWindow;
	MainWidget *mainWidget;
public:
	MainScrollAreaWidget( MainWindow *main_window );
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void setMainWidget( MainWidget *main_widget ) { mainWidget = main_widget; }
	/// @brief 赋值当前选中
	/// @return 成功返回 true
	virtual bool copyNodeItemActionInfo( );
	/// @brief 粘贴选中
	/// @return 成功返回 true
	virtual bool pasteNodeItemActionInfo( );
protected:
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // MAINSCROLLAREAWIDGET_H_H_HEAD__FILE__
