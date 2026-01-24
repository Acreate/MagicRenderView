#ifndef COLORSLIDER_H_H_HEAD__FILE__
#define COLORSLIDER_H_H_HEAD__FILE__
#include <QWidget>

class ClickBtn;
class ColorSlider : public QWidget {
	Q_OBJECT;
protected:
	ClickBtn *clickBtn;
protected:
	virtual void resizeWidget( const QSize &old_size, const QSize &new_size );
	virtual void rePainterWidget( );
public:
	ColorSlider( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
protected:
	bool eventFilter( QObject *watched, QEvent *event ) override;
	bool event( QEvent *event ) override;
};

#endif // COLORSLIDER_H_H_HEAD__FILE__
