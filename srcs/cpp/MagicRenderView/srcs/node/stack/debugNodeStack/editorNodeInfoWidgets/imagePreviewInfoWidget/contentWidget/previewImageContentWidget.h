#ifndef PREVIEWIMAGECONTENTWIDGET_H_H_HEAD__FILE__
#define PREVIEWIMAGECONTENTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class PreviewImageNode;
class ImageOutPortItemScrollArea;
class ImageOutPortItemScrollWidget;
class ImageOutPortContentToolsWidget;
class OutputPort;

class Node;
class PreviewImageContentWidget : public QWidget {
	Q_OBJECT;
protected:
	ImageOutPortContentToolsWidget *tool;
	ImageOutPortItemScrollArea *imageOutPortItemScrollArea;
	ImageOutPortItemScrollWidget *imageOutPortItemScrollWidget;
public:
	PreviewImageContentWidget( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	virtual bool init( PreviewImageNode *node );
	virtual bool updateLayout( );
	virtual ImageOutPortItemScrollWidget * getImageOutPortItemScrollWidget( ) const { return imageOutPortItemScrollWidget; }
protected:
	void resizeEvent( QResizeEvent *event ) override;
Q_SIGNALS:
	void click_builder_target_signal( Node *target_node );
};
#endif // PREVIEWIMAGECONTENTWIDGET_H_H_HEAD__FILE__
