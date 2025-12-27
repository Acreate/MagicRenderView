#ifndef APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#define APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

class NormalApplicationAction;
class NormalApplicationMenu;
class NormalApplicationToolBar;
class Application;
class MainWindow;
class QAction;
class QMenu;
class QToolBar;
class ApplicationMenuStack : public QObject {
	Q_OBJECT;
protected:
	template< typename TGeneratorType >
	class Generator {
	private:
		std::function< TGeneratorType*( ) > generator;
		QString typeName;
		std::vector< QString > aliasTypeName;
		QString *aliasTypeNameArrayPtr;
		size_t aliasTypeNameArrayCount;
	public:
		virtual ~Generator( ) = default;
		Generator( const std::function< TGeneratorType *( ) > &generator, const QString &type_name, const std::vector< QString > &alias_type_name )
			: generator( generator ),
			typeName( type_name ),
			aliasTypeName( alias_type_name ) {
			aliasTypeNameArrayPtr = aliasTypeName.data( );
			aliasTypeNameArrayCount = aliasTypeName.size( );
		}
		virtual TGeneratorType * create( ) {
			return generator( );
		}
		virtual bool isType( const QString &type_name ) {
			return type_name == typeName;
		}
		virtual bool isAliasType( const QString &alisa_type_name ) {
			for( size_t index = 0; index < aliasTypeNameArrayCount; ++index )
				if( aliasTypeNameArrayPtr[ index ] == alisa_type_name )
					return true;
			return false;
		}
	};

	template< typename TGeneratorType >
	class GeneratorArray {
	private:
		std::vector< Generator< TGeneratorType > > normalrGeneratorVector;
		Generator< TGeneratorType > *normalGeneratorArrayPtr;
		size_t normalGeneratorArrayCount;
	public:
		virtual ~GeneratorArray( ) = default;
		GeneratorArray( ) {
			normalGeneratorArrayPtr = nullptr;
			normalGeneratorArrayCount = 0;
		}
		virtual void appendGenerator( const Generator< TGeneratorType > &append_generator ) {
			normalrGeneratorVector.emplace_back( append_generator );
			normalGeneratorArrayPtr = normalrGeneratorVector.data( );
			normalGeneratorArrayCount = normalrGeneratorVector.size( );
		}
		virtual TGeneratorType * fromTypeCreate( const QString &type_name, size_t index = 0 ) {
			for( ; index < normalGeneratorArrayCount; index )
				if( normalGeneratorArrayPtr[ index ].isType( type_name ) )
					return normalGeneratorArrayPtr[ index ].create( );
			return nullptr;
		}
		virtual TGeneratorType * fromAliasTypeCreate( const QString &type_name, size_t index = 0 ) {
			for( ; index < normalGeneratorArrayCount; index )
				if( normalGeneratorArrayPtr[ index ].isAliasType( type_name ) )
					return normalGeneratorArrayPtr[ index ].create( );
			return nullptr;
		}
	};
protected:
	Application *application;
	GeneratorArray< NormalApplicationToolBar > toolBarGeneratorArray;
	GeneratorArray< NormalApplicationMenu > menuGeneratorArray;
	GeneratorArray< NormalApplicationAction > actionGeneratorArray;
public:
	ApplicationMenuStack( QObject *parent = nullptr );
	virtual bool initStack( );
	virtual NormalApplicationToolBar * getToolBar( const QString &tool_menu_name );
	virtual NormalApplicationMenu * getMenu( const QString &tool_menu_name );
	virtual NormalApplicationAction * getAction( const QString &acton_name );
};
#endif // APPLICATIONMENUSTACK_H_H_HEAD__FILE__
