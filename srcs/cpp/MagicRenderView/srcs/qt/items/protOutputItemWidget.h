#ifndef PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#define PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class ProtOutputItemWidget : public QWidget {
	Q_OBJECT;
public:
	ProtOutputItemWidget( QWidget *parent = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // PROTOUTPUTITEMWIDGET_H_H_HEAD__FILE__
