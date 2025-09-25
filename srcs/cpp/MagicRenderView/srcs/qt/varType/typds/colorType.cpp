#include "./colorType.h"

#include <QColor>
#include "../I_Type.h"
ColorType::ColorType( QObject *parent ) : BaseVarType( parent ) {
	initTypeInfo = [this] {
		var = new t_current_type( );
		objTypeInfo.reset( new I_Type( typeid( *this ) ) );
		varTypeInfo.reset( new I_Type( typeid( t_current_type ) ) );
		deleteCall = [this] {
			delete ( t_current_type * ) var;
		};
		return true;
	};
	initTypeInfo( );
}
ColorType::ColorType( ) : ColorType( nullptr ) {
}
ColorType::~ColorType( ) {
}
void ColorType::resetVar( ) {
	*var = t_current_type( );
}
