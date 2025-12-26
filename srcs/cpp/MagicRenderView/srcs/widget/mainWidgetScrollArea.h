#ifndef MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
#define MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
#pragma once

#include <QScrollArea>
class MainWidget;
class MainWidgetScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	MainWidget *mainWidget;
public:
	MainWidgetScrollArea( QWidget *parent = nullptr );
	/// @brief 滑动窗口到指定位置
	/// @param reference_widget 参照窗口
	/// @param left_top_pos 左侧坐标
	/// @param right_bottom_pos 右侧坐标
	virtual void scrollToTargetPos( QWidget *reference_widget, const QPoint &left_top_pos, const QPoint &right_bottom_pos );
	/// @brief 滑动窗口到指定位置
	/// @param reference_widget 参照窗口
	/// @param left_top_pos 左侧坐标
	/// @param right_boom_size 矩形长宽
	virtual void scrollToTargetPos( QWidget *reference_widget, const QPoint &left_top_pos, const QSize &right_boom_size );
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
};

#endif // MAINWIDGETSCROLLAREA_H_H_HEAD__FILE__
