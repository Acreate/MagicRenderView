#ifndef VARGENERATEQSCROLLAREAWIDGET_H_H_HEAD__FILE__
#define VARGENERATEQSCROLLAREAWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class VarGenerateWidget;
class VarGenerateScrollAreaWidget : public QScrollArea {
	Q_OBJECT;
protected:
	VarGenerateWidget *contentWidget;
public:
	VarGenerateScrollAreaWidget( QWidget *parent );
	virtual VarGenerateWidget * getContentWidget( ) const { return contentWidget; }
};

#endif // VARGENERATEQSCROLLAREAWIDGET_H_H_HEAD__FILE__
