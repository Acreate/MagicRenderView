#ifndef FLOATGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define FLOATGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class FloatGenerateRenderWidget;
class FloatGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	FloatGenerateRenderWidget *viewWidget;
public:
	FloatGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual FloatGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // FLOATGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
