#ifndef COLORGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define COLORGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class ColorGenerateRenderWidget;
class ColorGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	ColorGenerateRenderWidget *viewWidget;
public:
	ColorGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual ColorGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // COLORGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
