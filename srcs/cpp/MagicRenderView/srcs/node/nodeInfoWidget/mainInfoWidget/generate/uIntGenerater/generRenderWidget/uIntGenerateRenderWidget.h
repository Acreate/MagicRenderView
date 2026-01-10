#ifndef UINTGENERATERENDERWIDGET_H_H_HEAD__FILE__
#define UINTGENERATERENDERWIDGET_H_H_HEAD__FILE__

class UIntGenerateRenderScrollArea;
class UIntGenerateItemWidget;


#include <QWidget>

class UIntGenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< UIntGenerateItemWidget * > intGenerateItemWidgetVector;
	UIntGenerateRenderScrollArea *generateRenderScrollArea;
	UIntGenerateItemWidget *dragItem;
	size_t intGenerateItemWidgetArratCount;
	size_t intGenerateItemWidgetArratIndex;
	UIntGenerateItemWidget **intGenerateItemWidgetArratPtr;
public:
	UIntGenerateRenderWidget( UIntGenerateRenderScrollArea *generate_render_scroll_area );
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

#endif // UINTGENERATERENDERWIDGET_H_H_HEAD__FILE__
