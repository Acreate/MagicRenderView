#ifndef GENERATERENDERWIDGET_H_H_HEAD__FILE__
#define GENERATERENDERWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class GenerateRenderScrollArea;
class GenerateItemWidget;
class GenerateRenderWidget : public QWidget {
	Q_OBJECT;
protected:
	std::vector< GenerateItemWidget * > intGenerateItemWidgetVector;
	GenerateRenderScrollArea *generateRenderScrollArea;
public:
	GenerateRenderWidget( GenerateRenderScrollArea *generate_render_scroll_area );
	virtual std::vector< GenerateItemWidget * > * getIntGenerateItemWidgetVector( ) { return &intGenerateItemWidgetVector; }
	virtual void updateLayoutSort( );
};

#endif // GENERATERENDERWIDGET_H_H_HEAD__FILE__
