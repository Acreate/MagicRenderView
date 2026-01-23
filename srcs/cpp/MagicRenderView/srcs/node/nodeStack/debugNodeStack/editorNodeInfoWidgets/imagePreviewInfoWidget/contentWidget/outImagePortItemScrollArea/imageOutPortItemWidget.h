#ifndef IMAGEOUTPORTITEMWIDGET_H_H_HEAD__FILE__
#define IMAGEOUTPORTITEMWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class QTextEdit;
class QLabel;
class QVBoxLayout;
class OutputPort;
class ImageOutPortItemWidget : public QWidget {
	Q_OBJECT;
protected:
	OutputPort *outputPortPtr;
	QString msg;
	QVBoxLayout *mainLayout;
	QLabel *outputPortPtrName;
	QLabel *outputPreviewImage;
public:
	ImageOutPortItemWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	virtual void setInfo( OutputPort *output_port_ptr, const QImage &image_ref_obj );
	virtual OutputPort * getOutputPortPtr( ) const { return outputPortPtr; }
	virtual const QString & getMsg( ) const { return msg; }
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // IMAGEOUTPORTITEMWIDGET_H_H_HEAD__FILE__
