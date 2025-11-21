PHP attributes for Symfony DI
=============================

The following lists all dependency injection attributes and their usage
available in Netgen Layouts:

``Netgen\Layouts\Attribute\AsBlockDefinitionHandler``
-----------------------------------------------------

**Purpose**: Adds a new block definition handler

When registering a new block definition handler, you need to provide the
``$identifier`` argument in the attribute to specify the unique identifier of
the block definition.

``Netgen\Layouts\Attribute\AsBlockPlugin``
------------------------------------------

**Purpose**: Adds a new block handler plugin

When registering a new block definition handler plugin, you can use the
``$priority`` argument in the attribute to specify the order in which your
handler plugin is executed in regard to other existing plugins.

``Netgen\Layouts\Attribute\AsQueryTypeHandler``
-----------------------------------------------

**Purpose**: Adds a new query type handler

When registering a new query type handler, you need to provide the ``$type``
argument in the attribute to specify the unique identifier of the query type.

``Netgen\Layouts\Attribute\AsParameterType``
--------------------------------------------

**Purpose**: Adds a new parameter type

``Netgen\Layouts\Attribute\AsParameterTypeFormMapper``
------------------------------------------------------

**Purpose**: Adds a new parameter type form mapper

When registering a new parameter type form mapper, you need to provide the
``$parameterType`` argument in the attribute to specify to which parameter type
this mapper applies.

``Netgen\Layouts\Attribute\AsTargetType``
-----------------------------------------

**Purpose**: Adds a new target type

When registering a new target type, you can use the ``$priority`` argument in
the attribute to specify the order in which your target type is considered when
resolving the layout in regard to other existing target types.

``Netgen\Layouts\Attribute\AsTargetTypeFormMapper``
---------------------------------------------------

**Purpose**: Adds a new target type form mapper

When registering a new target type form mapper, you need to provide the
``$targetType`` argument in the attribute to specify to which target type this
mapper applies.

``Netgen\Layouts\Attribute\AsDoctrineTargetTypeHandler``
--------------------------------------------------------

**Purpose**: Adds a new target type Doctrine handler

When registering a new target type Doctrine handler, you need to provide the
``$targetType`` argument in the attribute to specify to which target type this
handler applies.

``Netgen\Layouts\Attribute\AsConditionType``
--------------------------------------------

**Purpose**: Adds a new condition type

``Netgen\Layouts\Attribute\AsConditionTypeFormMapper``
------------------------------------------------------

**Purpose**: Adds a new condition type form mapper

When registering a new condition type form mapper, you need to provide the
``$conditionType`` argument in the attribute to specify to which condition type
this mapper applies.

``Netgen\Layouts\Attribute\AsViewMatcher``
------------------------------------------

**Purpose**: Adds a new view template matcher

When registering a new view template matcher, you need to provide the
``$identifier`` argument in the attribute to specify the unique identifier of
the matcher.

``Netgen\Layouts\Attribute\AsCmsValueConverter``
------------------------------------------------

**Purpose**: Adds a new CMS value converter when defining a custom value type

``Netgen\Layouts\Attribute\AsCmsValueLoader``
---------------------------------------------

**Purpose**: Adds a new CMS value loader when defining a custom value type

When registering a new CMS value loader, you need to provide the ``$valueType``
argument in the attribute to specify the unique identifier of the value.

``Netgen\Layouts\Attribute\AsCmsValueUrlGenerator``
---------------------------------------------------

**Purpose**: Adds a new CMS value URL generator when defining a custom value type

When registering a new CMS value URL generator, you need to provide the
``$valueType`` argument in the attribute to specify the unique identifier of the
value.

``Netgen\Layouts\Enterprise\Attribute\AsLimitationType``
--------------------------------------------------------

**Purpose**: Adds a new limitation type

``Netgen\Layouts\Enterprise\Attribute\AsLimitationTypeFromMapper``
------------------------------------------------------------------

**Purpose**: Adds a new limitation type form mapper

When registering a new limitation type form mapper, you need to provide the
``$limitationType`` argument in the attribute to specify to which limitation
type this mapper applies.
