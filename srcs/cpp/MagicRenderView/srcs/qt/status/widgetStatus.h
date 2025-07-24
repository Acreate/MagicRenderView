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
	/// @brief 是否显示
	bool showStatus;
	/// @brief 关键字
	QString key;
public:
	WidgetStatus( const QString &key, QWidget *widget, size_t layout, bool is_show );
	virtual ~WidgetStatus( ) { }
	virtual const QString & getKey( ) const { return key; }
	virtual size_t getLayout( ) const { return layout; }
	virtual void setLayout( const size_t layout ) { this->layout = layout; }
	virtual QWidget * getWidget( ) const { return widget; }
	virtual void setWidget( QWidget *const widget ) { this->widget = widget; }
	virtual bool isShow( ) const { return showStatus; }
	virtual void setIsShow( const bool is_show ) { showStatus = is_show; }
	virtual void getAppIniValue( );
	virtual void setAppIniValue( );
};

#endif // WIDGETSTATUS_H_H_HEAD__FILE__
