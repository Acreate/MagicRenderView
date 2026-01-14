#ifndef AUTOACTION_H_H_HEAD__FILE__
#define AUTOACTION_H_H_HEAD__FILE__

#include <QAction>

class AutoAction : public QAction {
	Q_OBJECT;
public:
	AutoAction( const QString &titile = "" ) : QAction( titile ) { }
	~AutoAction( ) override { }
};

#endif // AUTOACTION_H_H_HEAD__FILE__
