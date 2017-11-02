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
types and blocks. Match configurations in a view context are processed
sequentially and template from first configuration that matches the rules will
be used to render the value.

Netgen Layouts uses five view contexts to render its' templates: ``default`` for
rendering the frontend templates, ``ajax`` for rendering collection pages
rendered view AJAX, ``api`` for rendering the Block Manager app templates and
``admin`` and ``value`` view contexts for rendering the administration
interface.

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

.. tip::

    If you use eZ Platform, view configuration is siteaccess aware. This means
    you can have different templates for different siteaccesses or siteaccess
    groups for the same block views or layout types.

    For example, you can use the following config to use two different templates
    for ``my_layout`` layout type for ``eng`` and ``cro`` siteaccesses:

    .. code-block:: yaml

        netgen_block_manager:
            system:
                eng:
                    view:
                        layout_view:
                            default:
                                my_layout:
                                    template: "@App/layouts/my_layout_eng.html.twig"
                                    match:
                                        layout\type: my_layout
                cro:
                    view:
                        layout_view:
                            default:
                                my_layout:
                                    template: "@App/layouts/my_layout_cro.html.twig"
                                    match:
                                        layout\type: my_layout

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

.. include:: /reference/view_types/index.rst.inc

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

.. include:: /reference/view_matchers/index.rst.inc
