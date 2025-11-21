#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Application;
class NodeDirector;
class DrawLinkWidget;
class DrawNodeWidget;
class MainWidget : public QWidget {
	Q_OBJECT;
	/// @brief 不可获取成员变量
protected:
	Application * appInstancePtr;
	NodeDirector *nodeDirector;
	/// @brief 可获取成员变量
protected:
	DrawNodeWidget *drawNodeWidget;
	DrawLinkWidget *drawLinkWidget;
	/// @brief 构造/析构 
public:
	MainWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	/// @brief 获取成员变量函数调用
public:
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	/// @brief 重载
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
