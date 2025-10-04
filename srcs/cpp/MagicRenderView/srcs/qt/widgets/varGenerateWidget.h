#ifndef VARGENERATEWIDGET_H_H_HEAD__FILE__
#define VARGENERATEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class Application;
class VarGenerate;
class MainWidget;
class I_Var;
class VarGenerateWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 生成的变量列表
	std_vector< I_Var * > mainWidgetGenerateVar;
	MainWidget *mainWidget;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 支持序列化
	VarGenerate *varGenerate;
	/// @brief ini 关键字
	QString keyFirst;
public:
	~VarGenerateWidget( ) override;
	VarGenerateWidget( QWidget *parent_widget );
	VarGenerateWidget( );
	virtual const std_vector< I_Var * > & getMainWidgetGenerateVar( ) const { return mainWidgetGenerateVar; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void setMainWidget( MainWidget * const main_widget );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // VARGENERATEWIDGET_H_H_HEAD__FILE__
