#ifndef FLOATGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define FLOATGENERATERENDERWIDGET_H_H_HEAD__FILE__

class FloatGenerateRenderScrollArea;
class FloatGenerateItemWidget;


#include <QWidget>

class FloatGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< FloatGenerateItemWidget * > intGenerateItemWidgetVector;
	FloatGenerateRenderScrollArea *generateRenderScrollArea;
	FloatGenerateItemWidget *dragItem;
	size_t floatGenerateItemWidgetArratCount;
	size_t floatGenerateItemWidgetArratIndex;
	FloatGenerateItemWidget **floatGenerateItemWidgetArratPtr;
public:
	FloatGenerateRenderWidget( FloatGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getFloatGenerateItemWidgetArratCount( ) const { return floatGenerateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // FLOATGENERATERENDERWIDGET_H_H_HEAD__FILE__
