#ifndef BINGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define BINGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class BinGenerateRenderWidget;
class BinGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	BinGenerateRenderWidget *viewWidget;
public:
	BinGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual BinGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // BINGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
