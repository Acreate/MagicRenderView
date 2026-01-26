#ifndef SELECTCOLORWIDGET_H_H_HEAD__FILE__
#define SELECTCOLORWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class SelectColorWidget : public QWidget {
	Q_OBJECT;
protected:
	QColor currentSelectColor;
public:
	SelectColorWidget( QWidget *parnet );
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	/// @brief 选择颜色完毕
	/// @param color 当前颜色
	void changeFinishColor_siganl( const QColor &color );
	/// @brief 当前正在选择颜色
	/// @param color 当前颜色
	void changeCurrenColor_siganl( const QColor &color );
};

#endif // SELECTCOLORWIDGET_H_H_HEAD__FILE__
