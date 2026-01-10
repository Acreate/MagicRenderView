#ifndef INTGENERATEITEMWIDGET_H_H_HEAD__FILE__
#define INTGENERATEITEMWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QLabel;
class IntGenerateItemWidget : public QWidget {
	Q_OBJECT;
public:
	QLabel *showIndexInfo;
	QLabel *dragLabel;
	QLineEdit *editorVarInfo;
	QMenu *managementMenu;
	QString infoFormmattion;
	QHBoxLayout *mainLayout;
	QMenu *popMenu;
public:
	IntGenerateItemWidget( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setInfo( const size_t &index, const QString &var_value );
	virtual void setIndex( const size_t &index );
	virtual bool isDragWidgetPos( const QPoint &pos );
	virtual QMenu * getPopMenu( ) const { return popMenu; }
	virtual QString getVarValue( ) const;
Q_SIGNALS:
	/// @brief 点击删除时发生该信号
	/// @param signal_ptr 信号对象指针
	void removeVar( IntGenerateItemWidget *signal_ptr );
	/// @brief 点击更改变量发生信号
	/// @param signal_ptr 信号对象指针
	void changeVar( IntGenerateItemWidget *signal_ptr );
	/// @brief 点击还原变量发生信号
	/// @param signal_ptr 信号对象指针
	void restoryVar( IntGenerateItemWidget *signal_ptr );
};

#endif // INTGENERATEITEMWIDGET_H_H_HEAD__FILE__
