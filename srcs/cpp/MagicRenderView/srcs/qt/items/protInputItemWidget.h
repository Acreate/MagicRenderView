#ifndef PROTINPUTITEMWIDGET_H_H_HEAD__FILE__
#define PROTINPUTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class ProtInputItemWidget : public QWidget {
	Q_OBJECT;
public:
	ProtInputItemWidget( QWidget *parent = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // PROTINPUTITEMWIDGET_H_H_HEAD__FILE__
