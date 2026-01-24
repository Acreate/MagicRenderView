#ifndef SHOWCOLORWIDGET_H_H_HEAD__FILE__
#define SHOWCOLORWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class ShowColorWidget : public QWidget {
	Q_OBJECT;
protected:
	QColor currentColor;
	
public:
	ShowColorWidget( QWidget *parent ) : QWidget( parent ) { }
	virtual const QColor & getCurrentColor( ) const { return currentColor; }
	virtual void setCurrentColor( const QColor &current_color ) { currentColor = current_color; }
};

#endif // SHOWCOLORWIDGET_H_H_HEAD__FILE__
