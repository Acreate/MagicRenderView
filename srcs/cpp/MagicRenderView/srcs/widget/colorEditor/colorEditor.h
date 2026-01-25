#ifndef COLOREDITOR_H_H_HEAD__FILE__
#define COLOREDITOR_H_H_HEAD__FILE__
#include <QWidget>

class QPushButton;
class QLabel;
class QImage;
class ColorEditor : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 选择坐标显示图标
	QLabel *selectPoint;
	/// @brief 选择颜色
	QImage *selectPointBackground;
	/// @brief 确认按钮
	QLabel *affirmBtn;
	/// @brief 取消按钮
	QLabel *cancelBen;
	/// @brief 透明控制
	QLabel *alphaScrollButton;
	/// @brief 透明控制背景
	QImage *alphaScrollBackground;
	/// @brief 绘制间隔
	int nextInterval;
	/// @brief 按钮绘制笔刷
	QPen *drawPen;
	/// @brief 当前颜色
	QColor currentColor;
	/// @brief 临时颜色
	QColor buffColor;
protected Q_SLOTS:
	virtual void affirmBtenClick( );
	virtual void cancelBtenClick( );
public:
	ColorEditor( QWidget *parent );
	~ColorEditor( ) override;
	virtual const QColor & getCurrentColor( ) const { return currentColor; }
	virtual const QColor & getBuffColor( ) const { return buffColor; }
	virtual void setCurrentColor( const QColor &current_color );
protected:
	bool eventFilter( QObject *watched, QEvent *event ) override;
	bool event( QEvent *event ) override;
Q_SIGNALS:
	void selectorColor( const QColor &color );
};

#endif // COLOREDITOR_H_H_HEAD__FILE__
