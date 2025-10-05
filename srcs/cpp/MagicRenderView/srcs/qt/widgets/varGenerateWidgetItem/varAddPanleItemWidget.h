#ifndef VARADDPANLEITEMWIDGET_H_H_HEAD__FILE__
#define VARADDPANLEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
#include <qboxlayout.h>

#include "../../../alias/type_alias.h"

class VarEditorItemWidget;
class QHBoxLayout;
class VarGenerateWidget;
class VarAddPanleItemWidget : public QWidget {
	Q_OBJECT;
protected:
	VarGenerateWidget *varGenerateWidget;
	QHBoxLayout *mainLayout;
	/// @brief 创建菜单
	QMenu *createMenu;
	std_vector_pairt< QString, std_vector_pairt< QString, std_function< VarEditorItemWidget*( QWidget * ) > > > createVector;
public:
	VarAddPanleItemWidget( VarGenerateWidget *parent );
	virtual bool appendType( const QString &dir_name, const QString &class_name, const std_function< VarEditorItemWidget*( QWidget * ) > &create_fucntion );
	virtual bool updateInfo( );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
public:
Q_SIGNALS:
	/// @brief 添加功能被点击
	void addClick( VarEditorItemWidget *add_target_widget_ptr );
};

#endif // VARADDPANLEITEMWIDGET_H_H_HEAD__FILE__
