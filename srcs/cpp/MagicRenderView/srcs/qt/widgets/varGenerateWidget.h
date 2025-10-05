#ifndef VARGENERATEWIDGET_H_H_HEAD__FILE__
#define VARGENERATEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class VarEditorItemWidget;
class VarAddPanleItemWidget;
class QVBoxLayout;
class Application;
class VarGenerate;
class MainWidget;
class I_Var;
class VarGenerateWidget : public QWidget {
	Q_OBJECT;
private:
	friend class VarEditorItemWidget;
protected:
	/// @brief 生成的变量列表
	std_vector_pairt< QString, std_vector< I_Var * > > mainWidgetGenerateVar;
	MainWidget *mainWidget;
	/// @brief 应用实例
	Application *appInstance;
	/// @brief 支持序列化
	VarGenerate *varGenerate;
	/// @brief ini 关键字
	QString keyFirst;
	/// @brief 主要布局对象
	QVBoxLayout *mainLayout;
	/// @brief 添加相应功能的项
	VarAddPanleItemWidget *varAddPanleItemWidget;
	/// @brief 保存所有编辑窗口
	std_vector< VarEditorItemWidget * > editorItemWidgets;
public:
	~VarGenerateWidget( ) override;
	VarGenerateWidget( QWidget *parent_widget );
	VarGenerateWidget( );
	virtual const std_vector_pairt< QString, std_vector< I_Var * > > & getMainWidgetGenerateVar( ) const { return mainWidgetGenerateVar; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void setMainWidget( MainWidget *main_widget );
	// 响应信号
protected:
	virtual void addVarEditorPanle( VarEditorItemWidget *add_target_widget_ptr );
	virtual void delVarEditorPanle( VarEditorItemWidget *remove_widget_item );
	virtual void resetSizeVarEditorPanle( VarEditorItemWidget *remove_widget_item, const QSize &old_size, const QSize &new_size );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // VARGENERATEWIDGET_H_H_HEAD__FILE__
