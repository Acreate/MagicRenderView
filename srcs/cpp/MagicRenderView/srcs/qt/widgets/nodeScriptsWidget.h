#ifndef NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#define NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class NodeRunSequenceAreasWidget;
class IFunctionDeclaration;
class NodeFuncPreviewImageWidget;
class NodeRunSequenceWidget;
class NodeDefineVarWidget;
class Application;
class NodeScriptsWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief ini 关键字
	QString keyFirst;
	Application *applicationInstancePtr;
	/// @brief 鼠标是否按下
	bool mouseIsPress;
	/// @brief 拖拽的窗口
	QWidget *dragWidgetSize;
	/// @brief 变量定义窗口
	NodeDefineVarWidget *nodeDefineVarWidget;
	/// @brief 节点序列窗口
	NodeRunSequenceAreasWidget *nodeRunSequenceAreasWidget;
public:
	NodeScriptsWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeScriptsWidget( ) override;
	void writeHeightIni( ) const;

	QWidget * mouseToPoint( const QPoint &point );
protected:
	void updateWidgetListLayout( const QSize &old_size, const QSize &current_size );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
protected Q_SLOTS :
	void dragEventEnd( Application *event_obj, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glbal_point );
};
#endif // NODESCRIPTSWIDGET_H_H_HEAD__FILE__
