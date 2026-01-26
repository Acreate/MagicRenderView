#ifndef BOTTOMBUTTONWIDGET_H_H_HEAD__FILE__
#define BOTTOMBUTTONWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QLabel;
class BottomButtonWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 确认按钮
	QLabel *affirmBtn;
	/// @brief 取消按钮
	QLabel *cancelBen;
	/// @brief 是否应答
	bool isButtonReponse;
public:
	BottomButtonWidget( QWidget *parent );
protected:
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
public:
Q_SIGNALS:
	void clickAffirmButton_signal( );
	void clickCancelButton_signal( );
};

#endif // BOTTOMBUTTONWIDGET_H_H_HEAD__FILE__
