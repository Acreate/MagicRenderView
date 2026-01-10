#ifndef IMAGEGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define IMAGEGENERATERENDERWIDGET_H_H_HEAD__FILE__



#include <QWidget>
class ImageGenerateRenderScrollArea;
class ImageGenerateItemWidget;

class ImageGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< ImageGenerateItemWidget * > intGenerateItemWidgetVector;
	ImageGenerateRenderScrollArea *generateRenderScrollArea;
	ImageGenerateItemWidget *dragItem;
	size_t generateItemWidgetArratCount;
	size_t generateItemWidgetArratIndex;
	ImageGenerateItemWidget **generateItemWidgetArratPtr;
public:
	ImageGenerateRenderWidget( ImageGenerateRenderScrollArea *generate_render_scroll_area );
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

#endif // IMAGEGENERATERENDERWIDGET_H_H_HEAD__FILE__
