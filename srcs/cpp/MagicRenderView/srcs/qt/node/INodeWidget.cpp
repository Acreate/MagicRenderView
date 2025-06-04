#include "INodeWidget.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
INodeWidget::INodeWidget( QWidget *const parent, const std_shared_ptr< IFunctionDeclaration > &function_declaration_ptr, const Qt::WindowFlags &f ): QWidget( parent, f ),
	functionDeclarationPtr( function_declaration_ptr ) {


	
	
}
void INodeWidget::call( ) const {
	if( functionDeclarationPtr )
		functionDeclarationPtr.get( )->call( );
}
