#ifndef STRINGGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define STRINGGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class StringGenerateRenderWidget;
class StringGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	StringGenerateRenderWidget *viewWidget;
public:
	StringGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual StringGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // STRINGGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
