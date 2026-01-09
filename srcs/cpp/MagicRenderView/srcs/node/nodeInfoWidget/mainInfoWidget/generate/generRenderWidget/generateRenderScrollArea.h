#ifndef GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#define GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class GenerateRenderWidget;
class GenerateItemWidget;
class GenerateRenderScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	GenerateRenderWidget *viewWidget;
public:
	GenerateRenderScrollArea( QWidget *parent = nullptr );
	virtual GenerateRenderWidget * getViewWidget( ) const { return viewWidget; }
};

#endif // GENERATERENDERSCROLLAREA_H_H_HEAD__FILE__
