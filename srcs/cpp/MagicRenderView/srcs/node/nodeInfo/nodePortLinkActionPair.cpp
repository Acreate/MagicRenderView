#include "nodePortLinkActionPair.h"

#include <QMenu>

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
NodePortLinkActionPair::NodePortLinkActionPair( InputPort *input_port, QAction *input_link_action, OutputPort *output_port, QAction *output_link_action ) : inputPort( input_port ),
	inputLinkAction( input_link_action ),
	outputPort( output_port ),
	outputLinkAction( output_link_action ) {

}
NodePortLinkActionPair::~NodePortLinkActionPair( ) {
	inputPort->disLinkMenu->removeAction( inputLinkAction );
	outputPort->disLinkMenu->removeAction( outputLinkAction );
	inputLinkAction->deleteLater( );
	outputLinkAction->deleteLater( );
}
