#ifndef ABOUTAPPLICATIONSCROLLAREA_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class AboutApplicationWindow;
class AboutApplicationWidget;
class AboutApplicationScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	AboutApplicationWidget *aboutApplicationWidgetPtr;
	AboutApplicationWindow *aboutApplicationWindowPtr;
public:
	AboutApplicationScrollArea( AboutApplicationWindow *about_application_window_ptr );
};

#endif // ABOUTAPPLICATIONSCROLLAREA_H_H_HEAD__FILE__
