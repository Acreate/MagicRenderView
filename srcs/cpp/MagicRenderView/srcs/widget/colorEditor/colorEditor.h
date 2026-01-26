#ifndef COLOREDITOR_H_H_HEAD__FILE__
#define COLOREDITOR_H_H_HEAD__FILE__
#include <QWidget>

class QLabel;
class QImage;
class ColorEditor : public QWidget {
	Q_OBJECT;
	ColorEditor( QWidget *parent ) : QWidget( parent ) { }
};

#endif // COLOREDITOR_H_H_HEAD__FILE__
