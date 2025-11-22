#ifndef MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
#define MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class MainWidget;
class MainWidgetScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	MainWidget *mainWidget;
public:
	MainWidgetScrollArea( QWidget *parent = nullptr );
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
};

#endif // MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
