#ifndef INTGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define INTGENERATERENDERWIDGET_H_H_HEAD__FILE__

class IntGenerateRenderScrollArea;
class IntGenerateItemWidget;


#include <QWidget>

class IntGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< IntGenerateItemWidget * > intGenerateItemWidgetVector;
	IntGenerateRenderScrollArea *generateRenderScrollArea;
	IntGenerateItemWidget *dragItem;
	size_t intGenerateItemWidgetArratCount;
	size_t intGenerateItemWidgetArratIndex;
	IntGenerateItemWidget **intGenerateItemWidgetArratPtr;
public:
	IntGenerateRenderWidget( IntGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getIntGenerateItemWidgetArratCount( ) const { return intGenerateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // INTGENERATERENDERWIDGET_H_H_HEAD__FILE__
