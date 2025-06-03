#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once

#include <QMainWindow>
class MainWindow : public QMainWindow {
	Q_OBJECT;
public:
	MainWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	void setWindowToIndexScreenCentre( size_t index );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
