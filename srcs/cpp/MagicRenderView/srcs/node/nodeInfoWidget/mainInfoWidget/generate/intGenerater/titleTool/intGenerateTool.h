#ifndef INTGENERATETOOL_H_H_HEAD__FILE__
#define INTGENERATETOOL_H_H_HEAD__FILE__


#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class IntGenerateTool : public QWidget {
	Q_OBJECT;
protected:
	QComboBox *insertIndexComboBox;
	QPushButton *insertBtn;
public:
	IntGenerateTool( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setMaxIndex( const size_t &index );
Q_SIGNALS:
	void addItem_signal( IntGenerateTool *signal_ptr, const size_t &index, const QString &index_text, const QVariant &index_variant );
};
#endif // INTGENERATETOOL_H_H_HEAD__FILE__
