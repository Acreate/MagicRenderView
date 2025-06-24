#ifndef DATAWIDGET_H_H_HEAD__FILE__
#define DATAWIDGET_H_H_HEAD__FILE__
#pragma once
#include "../IInfoWidget.h"

class HexEditor;
class DataTypeObject;
class QTextEdit;
class DataWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	HexEditor *edit;
	std_shared_ptr< DataTypeObject > dataTypeObject;
public:
	DataWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg );
	QString getText( ) const override;
	bool setText( const QString &new_text ) const override;
	void setPlaceholderText( const QString &placeholder_text ) const override;
	QString getPlaceholderText( ) const override;
	std_shared_ptr< ITypeObject > getValue( ) const override;
	
	/// @brief 获取数据，对于单独的短位补齐策略，false 表示低位(f 补齐位 0x0f)，true 表示非补齐位( f 为 0xf0)
	/// @param mod_is_suffix_data_var 短位补齐策略
	/// @return 返回数据序列
	virtual std_shared_ptr< DataTypeObject > getValue( bool mod_is_suffix_data_var ) const;
	bool setValue( const std_shared_ptr< ITypeObject > &value ) const override;
	virtual bool setString( const QString &hex_text );
	virtual bool setHex( const QByteArray &hex_text );

	virtual bool setHex( const std_vector< uchar > &data_vector );
	virtual bool setHex( const std_vector< char > &data_vector );
	virtual bool setHex( const int64_t &number_value );
	virtual bool setHex( const double &number_value );
};

#endif // DATAWIDGET_H_H_HEAD__FILE__
