#ifndef MACRO_H_H_HEAD__FILE__
#define MACRO_H_H_HEAD__FILE__
#pragma once

#define AliasTypeNames( _Type , ...) aliasTypeNames =std::vector< QString >( {typeid( _Type ).name(   ), __VA_ARGS__ } )
#define Stack_Type_Name( _Type, ... ) typeName = #_Type; AliasTypeNames(_Type,__VA_ARGS__ )

#endif // MACRO_H_H_HEAD__FILE__
