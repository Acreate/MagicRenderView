#ifndef WIDGETSTATUS_H_H_HEAD__FILE__
#define WIDGETSTATUS_H_H_HEAD__FILE__
#pragma once
#include <QString>

#include "../types/ITypeObject.h"

class QWidget;
class Application;
class WidgetStatus : public QObject {
	Q_OBJECT;
protected:
	/// @brief 实例
	Application *application;
	/// @brief 比例
	size_t layout;
	/// @brief 窗口
	QWidget *widget;
	/// @brief 关键字
	QString key;
public:
	WidgetStatus( const QString &key, QWidget *widget, size_t layout );
	virtual const QString & getKey( ) const { return key; }
	virtual size_t getLayout( ) const { return layout; }
	virtual void setLayout( const size_t layout ) { this->layout = layout; }
	virtual QWidget * getWidget( ) const { return widget; }
	virtual bool isShow( ) const;
	virtual void getAppIniValue( );
	virtual void setAppIniValue( );
public:
	/// @brief 标准化关键字
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @return 返回标准化后的关键字
	static QString normalKey( const QString &key, QWidget *widget );
	/// @brief 标准化关键字，并且在标准化关键字后续增加一个自定义字符串
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @param append_str 追加的字符串
	/// @return 返回标准化后的关键字
	static QString normalKeyAppendEnd( const QString &key, QWidget *widget, const QString &append_str ) {
		return normalKey( key, widget ).append( "/" ).append( append_str ).append( "/" );
	}
	/// @brief 标准化关键字，并且在末尾追加窗口名称
	/// @param key 自定义关键字列表
	/// @param widget 关键字关联窗口
	/// @return 返回标准化后的关键字
	static QString normalKeyAppendWidgetName( const QString &key, QWidget *widget );
};

#endif // WIDGETSTATUS_H_H_HEAD__FILE__
