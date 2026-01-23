#ifndef OUTPORTITEMWIDGET_H_H_HEAD__FILE__
#define OUTPORTITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class QTextEdit;
class QLabel;
class QVBoxLayout;
class OutputPort;
class OutPortItemWidget : public QWidget {
	Q_OBJECT;
protected:
	OutputPort *outputPortPtr;
	QString msg;
	QVBoxLayout *mainLayout;
	QLabel *outputPortPtrName;
	QTextEdit *outputPortMsg;
public:
	OutPortItemWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	virtual void setInfo( OutputPort *output_port_ptr, const QString &msg );
	virtual OutputPort * getOutputPortPtr( ) const { return outputPortPtr; }
	virtual const QString & getMsg( ) const { return msg; }
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // OUTPORTITEMWIDGET_H_H_HEAD__FILE__
