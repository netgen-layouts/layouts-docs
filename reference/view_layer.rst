View layer
==========

All entities in Netgen Layouts (layouts, blocks, mapping rules, forms) are
rendered through the same API called the view layer. View layer revolves around
three concepts:

* View
* Match configuration
* View context

View
----

All entities in Netgen Layouts specify their own view, which defines what
variables will be available in the Twig templates when the entity is rendered.
For example, layout view (identified by ``layout_view`` identifier), specifies
that all layout templates will have a variable called ``layout``, which will
hold the currently rendered template, while item view (identified by
``item_view`` identifier), specifies that all block item templates will have two
variables: ``item``, which holds the currently rendered block item, and
``view_type``, which will hold the item view type with which the item is
rendered.

There are a handful predefined views available in Netgen Layouts, but most
interesting ones are ofcourse views for rendering layouts, blocks and block
items. The other ones are used by administration interface of Netgen Layouts
(list of mappings, layouts and shared layouts) and are rarely needed, e.g. when
developing custom mapping targets and conditions.

Match configuration
-------------------

Match configuration is a single rule which specifies which template will be
rendered for a specific view when all configured conditions are met. Those
conditions are called matches, and services which perform the matching process
are called matchers.

View context
------------

View context is a set of match configuration rules and each view context is used
in different parts of Netgen Layouts. View contexts are what makes it possible
for example to use different templates for frontend and backend for your layout
types and blocks.

Netgen Layouts uses four view contexts to render its' templates: ``default`` for
rendering the frontend templates, ``api`` for rendering the Block Manager app
templates and ``admin`` and ``value`` view contexts for rendering the
administration interface.

Configuring the view layer
--------------------------

The following configuration shows an example on how to configure ``layout_view``
and ``block_view`` views, specifying some match rules in two different view
contexts (``default`` and ``api``).

.. code-block:: yaml

    netgen_block_manager:
        view:
            # The identifier of the view
            layout_view:
                # The name of the view context
                default:
                    # The identifier of a match configuration (unused, but needs to specified in YAML)
                    # The first match configuration for which all conditions match will be picked up and used to render the view
                    layout_1:
                        # The template that will be used when conditions specified below match
                        template: "@App/layout/layout_1.html.twig"

                        # The list of custom parameters that will be injected in the template if the conditions specified below match
                        parameters:
                            param1: value1
                            param2: value2

                        # The list of conditions that will need to match for this rule to be used
                        match:
                            layout\type: layout_1
                    layout_2:
                        template: "@App/api/layout/layout_2.html.twig"
                        match:
                            layout\type: layout_2
            block_view:
                api:
                    title:
                        template: "@App/block/title.html.twig"
                        match:
                            block\definition: title
                    text:
                        template: "@App/api/block/text.html.twig"
                        match:
                            block\definition: text

Custom view contexts
--------------------

If, for some reason, you would want to render some layouts or blocks by hand in
your PHP code, you can create custom view contexts (and custom templates,
ofcourse) on the fly and use them directly when rendering the layouts or blocks,
without touching and compromising the existing frontend templates.

So for example, to render a block view with your custom view context called
``my_context``, you would define a configuration similar to this:

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                my_context:
                    title:
                        template: "@App/block/my_context/title.html.twig"
                        match:
                            block\definition: title

and then somewhere in your controller:

.. code-block:: php

    $block = $this->get('netgen_block_manager.api.service.block')->loadBlock(42);
    return $this->get('netgen_block_manager.view.builder')->buildView($block, 'my_context');

.. note::

    You don't need to return Symfony ``Response`` object from your controllers,
    because Netgen Layouts will create and render it on the fly with a built in
    event listener.

List of built in views
----------------------

The following lists all built in views with their identifiers, supported
interfaces and the list of variables available in the rendered template.

``layout_view``
~~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\Layout\Layout`` interface.

Available variables:

* ``layout`` - The layout which is being rendered

.. warning::

    Frontend templates for layouts (``default`` context) are an exception and
    are not rendered through the Netgen Layouts view layer. Instead, they are
    rendered by extending from a special ``ngbm.layoutTemplate`` variable,
    available in your full view templates. Because of that, in frontend layout
    templates, ``layout`` variable is not available. Instead, the rendered
    layout is accessed by using ``ngbm.layout`` variable.

``block_view``
~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\Block\Block`` interface.

Available variables:

* ``block`` - The block which is being rendered

``item_view``
~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\Item\ItemInterface`` interface.

Available variables:

* ``item`` - The item which is being rendered
* ``view_type`` - Item view type with which the item is being rendered

``parameter_view``
~~~~~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\Parameters\ParameterValue`` interface.

Available variables:

* ``parameter`` - The parameter which is being rendered

.. note::

    While rendering other views will throw an exception if there is no template
    match in requested view context, this view will fallback to the ``default``
    view context. This is due to the fact that in most of the cases, rendering
    a block parameter will look exactly the same in the backend and in the
    frontend.

    This makes it possible to only specify one match configuration rule (in the
    ``default`` context) and one template to render the parameter in any view
    context.

``placeholder_view``
~~~~~~~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\Block\Placeholder`` interface.

Available variables:

* ``placeholder`` - The placeholder which is being rendered
* ``block`` - The block to which the rendered placeholder belongs

``rule_condition_view``
~~~~~~~~~~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\LayoutResolver\Condition`` interface.

Available variables:

* ``condition`` - The condition which is being rendered

``rule_target_view``
~~~~~~~~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\LayoutResolver\Target`` interface.

Available variables:

* ``target`` - The target which is being rendered

``rule_view``
~~~~~~~~~~~~~

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\LayoutResolver\Rule`` interface.

Available variables:
p
* ``rule`` - The rule which is being rendered

``form_view``
~~~~~~~~~~~~~

This view is used to render entities implementing
``Symfony\Component\Form\FormView`` interface.

Available variables:

* ``form`` - The Symfony form view which is being rendered
* ``formObject`` - The underlying Symfony form from which the view was built

List of built in matchers
-------------------------

The following lists all built in view matchers. As a rule of thumb, all matchers
accept either a scalar or an array of scalars as their value. If an array is
provided, the matcher will match if any of the values in the provided array is
matched.

.. note::

    While you can use all matchers in all views, most of the combinations do not
    make sense and will simply not match. For example, using ``layout\type``
    matcher in ``block_view`` view will never match since ``block_view`` renders
    a block, while ``layout\type`` matches on layout type of a rendered layout.

``block\definition``
~~~~~~~~~~~~~~~~~~~~

Matches on block definition of the rendered block.

* Available in: ``block_view``
* Example:

  .. code-block:: yaml

      match:
          block\definition: title

``block\view_type``
~~~~~~~~~~~~~~~~~~~

Matches on view type of the rendered block.

* Available in: ``block_view``
* Example:

  .. code-block:: yaml

      match:
          block\view_type: title

``layout\type``
~~~~~~~~~~~~~~~

Matches on layout type of the rendered layout.

* Available in: ``layout_view``
* Example:

  .. code-block:: yaml

      match:
          layout\type: layout_3

``layout\shared``
~~~~~~~~~~~~~~~~~

Matches on the shared flag of the rendered layout.

* Available in: ``layout_view``
* Example:

  .. code-block:: yaml

      match:
          layout\shared: true


.. note::

    While this matcher accepts an array as its value as all other matchers do,
    it will discard any other value in the array except the first one. This
    makes sense, since the only valid value for this matcher is a boolean.

``item\value_type``
~~~~~~~~~~~~~~~~~~~

Matches on the type of rendered item.

* Available in: ``item_view``
* Example:

  .. code-block:: yaml

      match:
          item\value_type: ezlocation

``item\view_type``
~~~~~~~~~~~~~~~~~~

Matches on item view type of the rendered item.

* Available in: ``item_view``
* Example:

  .. code-block:: yaml

      match:
          item\view_type: standard_with_intro

``parameter\type``
~~~~~~~~~~~~~~~~~~

Matches on type of the rendered parameter.

* Available in: ``parameter_view``
* Example:

  .. code-block:: yaml

      match:
          parameter\type: link

``rule_condition\type``
~~~~~~~~~~~~~~~~~~~~~~~

Matches on type of the rendered condition.

* Available in: ``rule_condition_view``
* Example:

  .. code-block:: yaml

      match:
          rule_condition\type: query_parameter

``rule_target\type``
~~~~~~~~~~~~~~~~~~~~

Matches on type of the rendered target.

* Available in: ``rule_target_view``
* Example:

  .. code-block:: yaml

      match:
          rule_target\type: query_parameter

``form\type``
~~~~~~~~~~~~~

Matches on type of the Symfony form which is rendered.

.. tip::

    This matcher is usually used with the matchers detailed below, if you wish,
    for example, to separate templates for rendering block create and block edit
    forms.

* Available in: ``form_view``
* Example:

  .. code-block:: yaml

      match:
          form\type: Netgen\BlockManager\Layout\Form\EditType

``form\block\definition``
~~~~~~~~~~~~~~~~~~~~~~~~~

Matches on block definition of a block which is edited through the Symfony form.

* Available in: ``form_view``
* Example:

  .. code-block:: yaml

      match:
          form\block\definition: title

``form\query\type``
~~~~~~~~~~~~~~~~~~~

Matches on query type of a query which is edited through the Symfony form.

* Available in: ``form_view``
* Example:

  .. code-block:: yaml

      match:
          form\query\type: ezcontent_search

``form\config\config_key``
~~~~~~~~~~~~~~~~~~~~~~~~~~

Matches on the config key of a config which is edited through the Symfony form.

* Available in: ``form_view``
* Example:

  .. code-block:: yaml

      match:
          form\config\config_key: http_cache

``form\config\value_type``
~~~~~~~~~~~~~~~~~~~~~~~~~~

Matches on the type of value for which the config is edited through the Symfony
form.

.. tip::

    This matcher is usually used with ``form\config\config_key`` matcher because
    most of the time, forms for rendering different aspects of value
    configuration will be different.

* Available in: ``form_view``
* Example:

  .. code-block:: yaml

      match:
          form\config\config_key: http_cache
          form\config\value_type: Netgen\BlockManager\API\Values\Block\Block
