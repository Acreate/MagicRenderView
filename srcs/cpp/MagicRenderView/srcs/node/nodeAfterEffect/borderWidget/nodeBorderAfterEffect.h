#ifndef NODEBORDERAFTEREFFECT_H_H_HEAD__FILE__
#define NODEBORDERAFTEREFFECT_H_H_HEAD__FILE__
#include "../nodeAfterEffect.h"

class NodeBorderDraw;
class NodeBorderAfterEffect : public NodeAfterEffect {
	Q_OBJECT;
protected:
	NodeBorderDraw* nodeBorderDraw;
public:
	NodeBorderAfterEffect( QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags( ) );
	~NodeBorderAfterEffect( ) override;
	bool updateLayout( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // NODEBORDERAFTEREFFECT_H_H_HEAD__FILE__
