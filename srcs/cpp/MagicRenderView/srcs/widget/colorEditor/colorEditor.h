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
	/// @brief 旧的大小
	QSize oldSize;
	/// @brief 新的大小
	QSize currentSize;
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
	/// @brief 更新组件布局
	/// @return 成功返回 true
	virtual bool updateLayout( );
	/// @brief 更新颜色信息到组件
	/// @return 成功返回 true
	virtual bool updateColorInfo( );
	/// @brief 清理组件颜色信息
	/// @return 成功返回 true
	virtual bool clearColorInfo( );
	/// @brief 渲染组件
	/// @return 成功返回 true
	virtual bool reDrawWidget( );
	/// @brief 确定按钮点击调用
	/// @return 成功执行返回 true
	virtual bool affirmButtonRelease( );
	/// @brief 取消按钮点击调用
	/// @return 成功返回 true
	virtual bool cancelButtonRelease( );
	/// @brief 滑动按钮被点击
	/// @return 调用成功返回 true
	virtual bool alphaScrollButtonRelease( );
	/// @brief 滑动按钮绘制事件
	/// @return 调用成功返回 true
	virtual bool alphaScrollButtonPaint( );
	/// @brief 隐藏事件被调用
	/// @return 成功调用返回 true
	virtual bool hideEventCall( );
	/// @brief 隐藏事件被调用
	/// @return 成功调用返回 true
	virtual bool showEventCall( );
protected:
	bool eventFilter( QObject *watched, QEvent *event ) override;
	bool event( QEvent *event ) override;
Q_SIGNALS:
	void selectorColor( const QColor &color );
};

#endif // COLOREDITOR_H_H_HEAD__FILE__
