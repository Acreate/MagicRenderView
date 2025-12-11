#ifndef GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class GenerateItemWidget;
class GenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	GenerateItemWidget *viewWidget;
public:
	GenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual GenerateItemWidget * getViewWIidget( ) const { return viewWidget; }
};

#endif // GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
