#ifndef COLORGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define COLORGENERATERENDERWIDGET_H_H_HEAD__FILE__



#include <QWidget>
class ColorGenerateRenderScrollArea;
class ColorGenerateItemWidget;

class ColorGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< ColorGenerateItemWidget * > intGenerateItemWidgetVector;
	ColorGenerateRenderScrollArea *generateRenderScrollArea;
	ColorGenerateItemWidget *dragItem;
	size_t generateItemWidgetArratCount;
	size_t generateItemWidgetArratIndex;
	ColorGenerateItemWidget **generateItemWidgetArratPtr;
public:
	ColorGenerateRenderWidget( ColorGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getIntGenerateItemWidgetArratCount( ) const { return generateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // COLORGENERATERENDERWIDGET_H_H_HEAD__FILE__
