#ifndef VAREDITORITEMWIDGET_H_H_HEAD__FILE__
#define VAREDITORITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../../../alias/type_alias.h"

#define def_vareditor_item_first() \
	Def_Last_StaticMetaInfo( ); \
	static const type_info & getStaticVarTypeInfo( );\
	virtual const type_info & getVarTypeInfo( ) const = 0

#define def_vareditor_item_last() \
	Def_Last_StaticMetaInfo( ); \
	public:\
	static const type_info & getStaticVarTypeInfo( );\
	const type_info & getVarTypeInfo( ) const override

#define imp_vareditor_item_first( class_type_ , target_name_,dir_name_, typeid_type_) \
	Imp_StaticMetaInfo( class_type_, dir_name_, target_name_ );\
	const type_info & class_type_::getVarTypeInfo( ) const{ return  typeid(typeid_type_);}\
	const type_info & class_type_::getStaticVarTypeInfo( ) { return  typeid(typeid_type_);}

class VarGenerate;
class Application;
class I_Var;
class QHBoxLayout;
class VarGenerateWidget;
class VarEditorItemWidget : public QWidget, public Type_Alias {
	Q_OBJECT;
	def_vareditor_item_first( );
protected:
	std_vector< std_shared_ptr< I_Var > > vars;
	Application *application;
	VarGenerate *varGenerate;
	VarGenerateWidget *varGenerateWidget;
public:
	VarEditorItemWidget( QWidget *parent );
	virtual void init( VarGenerateWidget *var_generate_widget );
	virtual const std_vector< std_shared_ptr< I_Var > > & getVar( ) const {
		return vars;
	}
protected:
	void resizeEvent( QResizeEvent *event ) override;
public:
Q_SIGNALS:
	/// @brief 删除编辑
	/// @param remove_widget_item 删除的指向指针
	void delEditorEvent( VarEditorItemWidget *remove_widget_item );
	/// @brief 窗口大小被重置了
	/// @param remove_widget_item 重置的窗口
	/// @param old_size 旧的大小
	/// @param new_size 新的大小
	void resetEditorSizeEvent( VarEditorItemWidget *remove_widget_item, const QSize &old_size, const QSize &new_size );
};

#endif // VAREDITORITEMWIDGET_H_H_HEAD__FILE__
