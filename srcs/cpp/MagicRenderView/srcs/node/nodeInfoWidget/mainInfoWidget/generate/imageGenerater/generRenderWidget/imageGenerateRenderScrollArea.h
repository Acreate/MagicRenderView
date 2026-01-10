#ifndef IMAGEGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define IMAGEGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class ImageGenerateRenderWidget;
class ImageGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	ImageGenerateRenderWidget *viewWidget;
public:
	ImageGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual ImageGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // IMAGEGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
