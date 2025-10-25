#ifndef GENERATELISTWIDGET_H_H_HEAD__FILE__
#define GENERATELISTWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QScrollArea;
class VarEditorWidget;
class QScrollBar;
class QPushButton;
class I_Var;
class QVBoxLayout;
class GenerateListItemWidget;
class GenerateListWidget : public QWidget {
	Q_OBJECT;
protected:
	QVBoxLayout *mainLayout;
	QPushButton *addItemBtn;
	QScrollArea *generateListScrollArea;
	QScrollBar *horizontalScrollBar;
	QScrollBar *verticalScrollBar;
	std_vector< GenerateListItemWidget * > generateListItemWidgets;
	GenerateListItemWidget *selectWidget;
	bool isReleaseWidget;
	std_function< std_shared_ptr< I_Var > ( ) > varGenerateFunction;
	std_function< bool( VarEditorWidget *, const QString & ) > nameCheckFunction;
	std_function< bool( VarEditorWidget *, const QString & ) > varCheckFunction;
	std_function< bool( VarEditorWidget *, const QString &, QString & ) > normalVarFunction;
protected:
	virtual bool insterToLayout( GenerateListItemWidget *new_list_item_widget );
	virtual bool addItem( GenerateListItemWidget *new_list_item_widget );
	virtual bool removeItem( GenerateListItemWidget *new_list_item_widget );
	virtual void fromComponentAddItemInfo( );
	virtual GenerateListItemWidget * getPointWidget( const QPoint &pos ) const;
public:
	GenerateListWidget( QScrollArea *parent );
	~GenerateListWidget( ) override;
	virtual std_vector< std_shared_ptr< I_Var > > getItemVarVector( ) const;
	virtual std_shared_ptr< I_Var > getItemIndexVar( const size_t &index ) const;
	virtual const std_function< std_shared_ptr< I_Var >( ) > & getVarGenerateFunction( ) const { return varGenerateFunction; }
	virtual void setVarGenerateFunction( const std_function< std_shared_ptr< I_Var >( ) > &var_generate_function ) { varGenerateFunction = var_generate_function; }
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getNameCheckFunction( ) const { return nameCheckFunction; }
	virtual void setNameCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &name_check_function ) { nameCheckFunction = name_check_function; }
	virtual const std_function< bool( VarEditorWidget *, const QString & ) > & getVarCheckFunction( ) const { return varCheckFunction; }
	virtual void setVarCheckFunction( const std_function< bool( VarEditorWidget *, const QString & ) > &var_check_function ) { varCheckFunction = var_check_function; }
	virtual const std_function< bool( VarEditorWidget *, const QString &, QString & ) > & getNormalVarFunction( ) const { return normalVarFunction; }
	virtual void setNormalVarFunction( const std_function< bool( VarEditorWidget *, const QString &, QString & ) > &normal_var_function ) { normalVarFunction = normal_var_function; }
protected:
	void paintEvent( QPaintEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void changeVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
	void delVarOverSignal( GenerateListWidget *signal_obj_ptr, GenerateListItemWidget *change_item_var_obj_ptr, VarEditorWidget *change_var_obj_ptr );
};

#endif // GENERATELISTWIDGET_H_H_HEAD__FILE__
