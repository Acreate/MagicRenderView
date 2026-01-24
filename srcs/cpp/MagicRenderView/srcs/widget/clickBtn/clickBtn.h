#ifndef CLICKBTN_H_H_HEAD__FILE__
#define CLICKBTN_H_H_HEAD__FILE__
#include <QWidget>

class ClickBtn : public QWidget {
	Q_OBJECT;
protected:
	QImage *image;
	QString text;
public:
	ClickBtn( QWidget *parent );
	~ClickBtn( ) override;
	
	virtual QImage & getImage( ) const;
	virtual void setImage( QImage &image );
	virtual const QString & getText( ) const;
	virtual void setText( const QString &text );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // CLICKBTN_H_H_HEAD__FILE__
