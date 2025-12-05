#ifndef BOTTOMNODEINFOTOOL_H_H_HEAD__FILE__
#define BOTTOMNODEINFOTOOL_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QPushButton;
class BottomNodeInfoTool : public QWidget {
	Q_OBJECT;
protected:
	QPushButton *okPushButton;
	QPushButton *cancelPushButton;
public:
	BottomNodeInfoTool( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
Q_SIGNALS:
	void ok_signal( );
	void cancel_signal( );
};

#endif // BOTTOMNODEINFOTOOL_H_H_HEAD__FILE__
