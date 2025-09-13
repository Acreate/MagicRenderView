#ifndef ITEMWIDGET_H_H_HEAD__FILE__
#define ITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class ItemWidget : public QWidget {
	Q_OBJECT;
public:
	ItemWidget( QWidget *parent );
	~ItemWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void s_signals_deleteItemWidget( ItemWidget *remove_item_widget );
	void s_signals_clickItemWidget( ItemWidget *click_item_widget );
	void s_signals_doubleClickItemWidget( ItemWidget *double_click_item_widget );
};

#endif // ITEMWIDGET_H_H_HEAD__FILE__
