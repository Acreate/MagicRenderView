#ifndef IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
#define IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__

#include <node/nodeInfoWidget/mainInfoWidget/editorNodeInfoScrollArea.h>

class QFileDialog;
class QLabel;
class QPushButton;
class ValidatorWidget;
class QVBoxLayout;
class ImageCreateUnityNodeEditorScrollArea : public EditorNodeInfoScrollArea {
	Q_OBJECT;
	friend class ImageCreateUnityNodeEditorWidget;
protected:
	QFileDialog *fileDialog;
	QString lastLoadFilePath;
	QImage currentVar;
	QWidget *mainWidget;
	QVBoxLayout *mainLayout;
	ValidatorWidget *currentEditorValidator;
	std::vector< ValidatorWidget * > lineFinishedEditorVector;
	QWidget *buttonCompoentWidget;
	QPushButton *pathLoadFileButton;
	QLabel *showImageLabel;
protected:
	ImageCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QImage &current_var );
	void releaseResource( ) override;
	bool eventFilter( QObject *watched, QEvent *event ) override;
	void onLoadPng( );
public:
	bool initNode( Node *init_node ) override;
	~ImageCreateUnityNodeEditorScrollArea( ) override;
	virtual const QImage & getCurrentVar( ) const { return currentVar; }
	virtual void setCurrentVar( const QImage &current_var );
Q_SIGNALS:
	void editingFinished_Signal( const QImage &var );
};

#endif // IMAGECREATEUNITYNODEEDITORSCROLLAREA_H_H_HEAD__FILE__
