#ifndef GENERATELISTWIDGET_H_H_HEAD__FILE__
#define GENERATELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QScrollBar;
class GenerateListScrollArea;
class GenerateAddInfoWidget;
class I_Var;
class GenerateListItemWidget;
class GenerateListWidget : public QWidget {
	Q_OBJECT;
protected:
	GenerateAddInfoWidget *generateAddInfoWidget;
	GenerateListScrollArea *generateListScrollArea;
	QScrollBar *horizontalScrollBar;
	QScrollBar *verticalScrollBar;
	std_vector< GenerateListItemWidget * > generateListItemWidgets;
protected:
	virtual bool addItem( GenerateListItemWidget *new_list_item_widget );
	virtual bool removeItem( const GenerateListItemWidget *new_list_item_widget );
	virtual bool inster( GenerateListItemWidget *new_list_item_widget, const size_t &index );
	virtual bool sortItemWidget( );
public:
	GenerateListWidget( GenerateListScrollArea *parent );
	~GenerateListWidget( ) override;
	virtual std_vector< std_shared_ptr< I_Var > > getItemVarVector( ) const;
	virtual std_shared_ptr< I_Var > getItemIndexVar( const size_t &index ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // GENERATELISTWIDGET_H_H_HEAD__FILE__
