#ifndef MAINWIDGET_H_H_HEAD__FILE__
#define MAINWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class PrinterDirector;
class NodeRefLinkInfo;
class OutputPort;
class InputPort;
class NodeClickInfo;
class MainWindow;
class MainWidgetScrollArea;
class Node;
class Application;
class NodeDirector;
class DrawLinkWidget;
class DrawNodeWidget;
class MainWidget : public QWidget {
	Q_OBJECT;
	/// @brief 不可获取成员变量
protected:
	Application *appInstancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	/// @brief 可获取成员变量
protected:
	MainWindow *mainWindow;
	DrawNodeWidget *drawNodeWidget;
	DrawLinkWidget *drawLinkWidget;
	MainWidgetScrollArea *mainWidgetScrollArea;
	NodeClickInfo *clickInfoPtr;
	QMenu *nodeCreateMenu;
	Node *oldSelectNode;
	Node *dragNode;
	InputPort *selectInputPort;
	OutputPort *selectOutputPort;
	QDateTime *oldClickTime;
	QPoint offsetPoint;
	QSize renderMaxSize;
	/// @brief 构造/析构 
public:
	MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~MainWidget( ) override;
	virtual bool addNode( NodeRefLinkInfo *node_ref_link_info );
	virtual bool ensureVisible( Node *target );
	virtual bool init( );
	/// @brief 快捷功能
public:
	virtual void copySelectNodeInfo( );
	virtual void pastePointNodeInfo( );
	virtual void cutSelectNodeInfo( );
	virtual void cancelNodeInfo( );
	virtual void deleteSelectNodeInfo( );
	void subWidgetReSize( );
	virtual void calculateNodeRenderSize( );
	/// @brief 获取成员变量函数调用
public:
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	/// @brief 重载
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void release_signal( MainWidget *release_ptr );
};

#endif // MAINWIDGET_H_H_HEAD__FILE__
