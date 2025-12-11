#ifndef GENERATERENDERWIDGET_H_H_HEAD__FILE__
#define GENERATERENDERWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class GenerateRenderScrollArea;
class GenerateItemWidget;
class GenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< GenerateItemWidget * > intGenerateItemWidgetVector;
	GenerateRenderScrollArea *generateRenderScrollArea;
	GenerateItemWidget *dragItem;
	size_t intGenerateItemWidgetArratCount;
	size_t intGenerateItemWidgetArratIndex;
	GenerateItemWidget **intGenerateItemWidgetArratPtr;
public:
	GenerateRenderWidget( GenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void resize( const size_t &new_size );
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // GENERATERENDERWIDGET_H_H_HEAD__FILE__
