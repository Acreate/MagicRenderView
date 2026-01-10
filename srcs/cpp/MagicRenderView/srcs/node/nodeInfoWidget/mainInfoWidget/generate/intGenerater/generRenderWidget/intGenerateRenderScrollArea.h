#ifndef INTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define INTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class IntGenerateRenderWidget;
class IntGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	IntGenerateRenderWidget *viewWidget;
public:
	IntGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual IntGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // INTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
