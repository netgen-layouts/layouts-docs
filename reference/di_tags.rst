Symfony dependency injection tags
=================================

The following lists all dependency injection tags and their usage available
in Netgen Layouts:

``netgen_layouts.block_definition_handler``
-------------------------------------------

**Purpose**: Adds a new block definition handler

When registering a new block definition handler, you need to use the
``identifier`` attribute in the tag to specify the unique identifier of the
block definition:

.. code-block:: yaml

    app.block.block_definition.handler.my_block:
        class: App\Block\BlockDefinition\Handler\MyBlockHandler
        tags:
            - { name: netgen_layouts.block_definition_handler, identifier: my_block }

``netgen_layouts.block_definition_handler.plugin``
--------------------------------------------------

**Purpose**: Adds a new block handler plugin

When registering a new block definition handler plugin, you can use the
``priority`` attribute in the tag to specify the order in which your handler
plugin is executed in regard to other existing plugins:

.. code-block:: yaml

    app.block.block_definition.handler.plugin.my_plugin:
        class: App\Block\BlockDefinition\Handler\MyPlugin
        tags:
            - { name: netgen_layouts.block_definition_handler.plugin, priority: 10 }

``netgen_layouts.query_type_handler``
-------------------------------------

**Purpose**: Adds a new query type handler

When registering a new query type handler, you need to use the ``type``
attribute in the tag to specify the unique identifier of the query type:

.. code-block:: yaml

    app.collection.query_type.handler.my_handler:
        class: App\Collection\QueryType\Handler\MyHandler
        tags:
            - { name: netgen_layouts.query_type_handler, type: my_handler }

``netgen_layouts.parameter_type``
---------------------------------

**Purpose**: Adds a new parameter type

.. code-block:: yaml

    app.parameters.parameter_type.my_type:
        class: App\Parameters\ParameterType\MyType
        tags:
            - { name: netgen_layouts.parameter_type }

``netgen_layouts.parameter_type.form_mapper``
---------------------------------------------

**Purpose**: Adds a new parameter type form mapper

When registering a new parameter type form mapper, you need to use the ``type``
attribute in the tag to specify to which parameter type this mapper applies:

.. code-block:: yaml

    app.parameters.form.mapper.my_type:
        class: App\Parameters\Form\Mapper\MyTypeMapper
        tags:
            - { name: netgen_layouts.parameter_type.form_mapper, type: my_type }

``netgen_layouts.target_type``
------------------------------

**Purpose**: Adds a new target type

When registering a new target type, you can use the ``priority`` attribute in
the tag to specify the order in which your target type is considered when
resolving the layout in regard to other existing target types:

.. code-block:: yaml

    app.layout.resolver.target_type.my_target:
        class: App\Layout\Resolver\TargetType\MyTarget
        tags:
            - { name: netgen_layouts.target_type, priority: 10 }

``netgen_layouts.target_type.form_mapper``
------------------------------------------

**Purpose**: Adds a new target type form mapper

When registering a new target type form mapper, you need to use the
``target_type`` attribute in the tag to specify to which target type this mapper
applies:

.. code-block:: yaml

    app.layout.resolver.form.target_type.mapper.my_target:
        class: App\Layout\Resolver\Form\TargetType\Mapper\MyTarget
        tags:
            - { name: netgen_layouts.target_type.form_mapper, target_type: my_target }

``netgen_layouts.target_type.doctrine_handler``
-----------------------------------------------

**Purpose**: Adds a new target type Doctrine handler

When registering a new target type Doctrine handler, you need to use the
``target_type`` attribute in the tag to specify to which target type this
handler applies:

.. code-block:: yaml

    app.layout_resolver.target_handler.doctrine.my_target:
        class: App\LayoutResolver\TargetHandler\Doctrine\MyTarget
        tags:
            - { name: netgen_layouts.target_type.doctrine_handler, target_type: my_target }

``netgen_layouts.condition_type``
---------------------------------

**Purpose**: Adds a new condition type

.. code-block:: yaml

    app.layout.resolver.condition_type.my_condition:
        class: App\Layout\Resolver\ConditionType\MyCondition
        tags:
            - { name: netgen_layouts.condition_type }

``netgen_layouts.condition_type.form_mapper``
---------------------------------------------

**Purpose**: Adds a new condition type form mapper

When registering a new condition type form mapper, you need to use the
``condition_type`` attribute in the tag to specify to which condition type this
mapper applies:

.. code-block:: yaml

    app.layout.resolver.form.condition_type.mapper.my_condition:
        class: App\Layout\Resolver\Form\ConditionType\Mapper\MyCondition
        tags:
            - { name: netgen_layouts.condition_type.form_mapper, condition_type: my_condition }

``netgen_layouts.view_matcher``
-------------------------------

**Purpose**: Adds a new view template matcher

When registering a new view template matcher, you need to use the ``identifier``
attribute in the tag to specify the unique identifier of the matcher:

.. code-block:: yaml

    app.view.matcher.block.my_matcher:
        class: App\View\Matcher\Block\MyMatcher
        tags:
            - { name: netgen_layouts.view_matcher, identifier: block\my_matcher }

``netgen_layouts.context_provider``
-----------------------------------

**Purpose**: Adds data to the context which is used to render contextual blocks via AJAX.

.. code-block:: yaml

    app.context.my_context_provider:
        class: App\Context\MyContextProvider
        tags:
            - { name: netgen_layouts.context_provider }
