#ifndef STRINGGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define STRINGGENERATERENDERWIDGET_H_H_HEAD__FILE__


#include <QWidget>

class StringGenerateRenderScrollArea;
class StringGenerateItemWidget;

class StringGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< StringGenerateItemWidget * > stringGenerateItemWidgetVector;
	StringGenerateRenderScrollArea *generateRenderScrollArea;
	StringGenerateItemWidget *dragItem;
	size_t stringGenerateItemWidgetArratCount;
	size_t stringGenerateItemWidgetArratIndex;
	StringGenerateItemWidget **stringGenerateItemWidgetArratPtr;
public:
	StringGenerateRenderWidget( StringGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getIntGenerateItemWidgetArratCount( ) const { return stringGenerateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // STRINGGENERATERENDERWIDGET_H_H_HEAD__FILE__
