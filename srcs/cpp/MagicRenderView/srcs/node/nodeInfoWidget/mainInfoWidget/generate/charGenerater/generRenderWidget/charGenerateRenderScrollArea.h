#ifndef CHARGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define CHARGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class CharGenerateRenderWidget;
class CharGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	CharGenerateRenderWidget *viewWidget;
public:
	CharGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual CharGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // CHARGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
