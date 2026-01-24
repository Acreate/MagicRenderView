#ifndef COLOREDITOR_H_H_HEAD__FILE__
#define COLOREDITOR_H_H_HEAD__FILE__
#include <QWidget>

class QPushButton;
class ColorEditor : public QWidget {
	Q_OBJECT;
protected:
	QPushButton *affirmBtn;
	QPushButton *cancelBen;
	QColor *currentColor;
protected Q_SLOTS:
	virtual void affirmBtenClick( );
	virtual void cancelBtenClick( );
public:
	ColorEditor( QWidget *parent );
	virtual QColor * getCurrentColor( ) const { return currentColor; }
	virtual void setCurrentColor( QColor *current_color ) { currentColor = current_color; }
protected:
	void hideEvent( QHideEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
Q_SIGNALS:
	void selectorColor( const QColor &color );
};

#endif // COLOREDITOR_H_H_HEAD__FILE__
