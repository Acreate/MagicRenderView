#ifndef UINTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define UINTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

class UIntGenerateRenderWidget;
class UIntGenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	UIntGenerateRenderWidget *viewWidget;
public:
	UIntGenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual UIntGenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};
#endif // UINTGENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
