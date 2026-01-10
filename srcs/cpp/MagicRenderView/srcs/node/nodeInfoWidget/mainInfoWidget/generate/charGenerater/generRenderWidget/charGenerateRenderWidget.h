#ifndef CHARGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define CHARGENERATERENDERWIDGET_H_H_HEAD__FILE__



#include <QWidget>
class CharGenerateRenderScrollArea;
class CharGenerateItemWidget;

class CharGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< CharGenerateItemWidget * > intGenerateItemWidgetVector;
	CharGenerateRenderScrollArea *generateRenderScrollArea;
	CharGenerateItemWidget *dragItem;
	size_t charGenerateItemWidgetArratCount;
	size_t charGenerateItemWidgetArratIndex;
	CharGenerateItemWidget **charGenerateItemWidgetArratPtr;
public:
	CharGenerateRenderWidget( CharGenerateRenderScrollArea *generate_render_scroll_area );
	virtual void updateLayoutSort( );
	virtual void createItem( const size_t &index );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void clear( );
	virtual void updateVectorIndex( );
	virtual void resize( const size_t &new_size );
	virtual std::vector< QString > converTextVector( ) const;
	virtual size_t getIntGenerateItemWidgetArratCount( ) const { return charGenerateItemWidgetArratCount; }
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void requesPopItemMenu_signal( QMenu *pop_menu );
};

#endif // CHARGENERATERENDERWIDGET_H_H_HEAD__FILE__
