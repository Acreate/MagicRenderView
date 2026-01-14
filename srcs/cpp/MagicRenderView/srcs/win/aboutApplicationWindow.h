#ifndef ABOUTAPPLICATIONWINDOW_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
class AboutApplicationScrollArea;
class AboutApplicationWidget;
class MainWindow;
class AboutApplicationWindow : public QMainWindow {
	Q_OBJECT;
protected:
	MainWindow *parentMainWiindowPtr;
	AboutApplicationScrollArea* aboutApplicationScrollAreaPtr;
	AboutApplicationWidget* aboutApplicationWidgetPtr;
public:
	AboutApplicationWindow( MainWindow *parent_main_wiindow_ptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	void updateWindowGeometry( );
protected:
	void showEvent( QShowEvent *event ) override;
	bool eventFilter( QObject *watched, QEvent *event ) override;
};

#endif // ABOUTAPPLICATIONWINDOW_H_H_HEAD__FILE__
