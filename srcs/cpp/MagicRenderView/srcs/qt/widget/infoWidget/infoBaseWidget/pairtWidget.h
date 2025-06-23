#ifndef PAIRTWIDGET_H_H_HEAD__FILE__
#define PAIRTWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class PairtWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	/// @brief 键验证器
	std_function< bool( const ITypeObject * ) > firstVerify;
	/// @brief 值验证器
	std_function< bool( const ITypeObject * ) > scondVerify;
	std_shared_ptr< IInfoWidget * > first;
	std_shared_ptr< IInfoWidget * > scond;
public:
	PairtWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );

	QString getText( ) const override;
	bool setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;

	virtual const std_function< bool( const ITypeObject * ) > & getFirstVerify( ) const { return firstVerify; }
	virtual void setFirstVerify( const std_function< bool( const ITypeObject * ) > &first_verify ) { firstVerify = first_verify; }
	virtual const std_function< bool( const ITypeObject * ) > & getScondVerify( ) const { return scondVerify; }
	virtual void setScondVerify( const std_function< bool( const ITypeObject * ) > &scond_verify ) { scondVerify = scond_verify; }

	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;

	/// @brief 获取键
	/// @return 键
	virtual std_shared_ptr< ITypeObject > getFirst( ) const;
	/// @brief 获取值
	/// @return 值
	virtual std_shared_ptr< ITypeObject > getScond( ) const;
	/// @brief 配置 key
	/// @param key 配置的对象
	/// @return 成功返回 true
	virtual bool setFirst( const std_shared_ptr< ITypeObject > &key ) const;
	/// @brief 配置 value
	/// @param value 配置的对象
	/// @return 成功返回 true
	virtual bool setScond( const std_shared_ptr< ITypeObject > &value ) const;

};

#endif // PAIRTWIDGET_H_H_HEAD__FILE__
