#ifndef ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#define ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class AboutApplicationWindow;
class AboutApplicationWidget : public QWidget {
	Q_OBJECT;
protected:
	AboutApplicationWindow *parentWindow;
public:
	AboutApplicationWidget( AboutApplicationWindow *parent_window );
	virtual QString getSoftwareProtocolInfo( );
};

#endif // ABOUTAPPLICATIONWIDGET_H_H_HEAD__FILE__
