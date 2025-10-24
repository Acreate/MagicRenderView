#ifndef GENERATELISTWIDGET_H_H_HEAD__FILE__
#define GENERATELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QScrollBar;
class QPushButton;
class GenerateListScrollArea;
class I_Var;
class QVBoxLayout;
class GenerateListItemWidget;
class GenerateListWidget : public QWidget {
	Q_OBJECT;
protected:
	QVBoxLayout *mainLayout;
	QPushButton *addItemBtn;
	GenerateListScrollArea *generateListScrollArea;
	QScrollBar *horizontalScrollBar;
	QScrollBar *verticalScrollBar;
	std_vector< GenerateListItemWidget * > generateListItemWidgets;
	GenerateListItemWidget *selectWidget;
	bool isReleaseWidget;
protected:
	virtual bool insterToLayout( GenerateListItemWidget *new_list_item_widget );
	virtual bool addItem( GenerateListItemWidget *new_list_item_widget );
	virtual bool removeItem( GenerateListItemWidget *new_list_item_widget );
	virtual void fromComponentAddItemInfo( );
	virtual GenerateListItemWidget * getPointWidget( const QPoint &pos ) const;
public:
	GenerateListWidget( GenerateListScrollArea *parent );
	~GenerateListWidget( ) override;
	virtual std_vector< std_shared_ptr< I_Var > > getItemVarVector( ) const;
	virtual std_shared_ptr< I_Var > getItemIndexVar( const size_t &index ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // GENERATELISTWIDGET_H_H_HEAD__FILE__
