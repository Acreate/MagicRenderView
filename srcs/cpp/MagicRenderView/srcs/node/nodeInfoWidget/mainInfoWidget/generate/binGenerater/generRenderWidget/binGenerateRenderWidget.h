#ifndef BINGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define BINGENERATERENDERWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class BinGenerateRenderScrollArea;
class BinGenerateItemWidget;
class BinGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< BinGenerateItemWidget * > binGenerateItemWidgetVector;
	BinGenerateRenderScrollArea *generateRenderScrollArea;
	BinGenerateItemWidget *dragItem;
	size_t binGenerateItemWidgetArratCount;
	size_t binGenerateItemWidgetArratIndex;
	BinGenerateItemWidget **binGenerateItemWidgetArratPtr;
public:
	BinGenerateRenderWidget( BinGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getIntGenerateItemWidgetArratCount( ) const { return binGenerateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // BINGENERATERENDERWIDGET_H_H_HEAD__FILE__
