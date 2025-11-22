#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>
class MainWidgetScrollArea;
class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
protected:
	MainWidgetScrollArea *mainWidgetScrollArea;
	MainWidget *mainWidget;
public:
	MainWindow( );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
