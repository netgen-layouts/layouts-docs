Using themes
============

Themes in Netgen Layouts provide a way to quickly override any frontend layout,
block and block item templates provided by Netgen Layouts.

Once configured, the override process works based on convention. That is, you
only need to place templates at certain paths, and they will automatically be
picked up and used instead of the built in templates.

.. warning::

    Currently, only frontend templates use themes. Overriding backend templates
    still works in very much the same way as always.

Netgen Layouts theme support defines two concepts: a design, and a theme, design
being a collection of themes and theme being a collection of paths where
templates are being loaded from.

When searching for a template, the system looks at the currently configured
design and starts looking for the template in all themes within the design, one
by one. First path from the first theme which exists for the specified template
is used. This makes it possible to override any built in theme by creating a
design that contains the original theme and your new theme that only has the
overridden templates.

The system also comes with one built in theme called ``standard``, which is
always used as a fallback when no templates are found in your custom
design/themes. All frontend templates for layouts, blocks and block items are
part of this built in theme.

Getting started with themes
---------------------------

To specify which design your frontend will use, you need to add it to
configuration and specify the currently used design:

.. code-block:: yaml

    netgen_layouts:
        design_list:
            my_design: [my_theme, my_other_theme]
            my_second_design: [my_theme, my_third_theme]
        design: my_design

With above configuration, we defined two designs, called ``my_design`` and
``my_second_design``, with their themes, and we specified that currently used
design is ``my_design``.

.. tip::

    If you're using Ibexa CMS, currently used design can be siteaccess aware,
    meaning, you can use configuration similar to this to specify different
    designs for different siteaccesses or siteaccess groups:

    .. code-block:: yaml

        netgen_layouts:
            system:
                frontend_group:
                    design: my_design
                other_group:
                    design: my_second_design

.. tip::

    If you only ever intend to use one theme and knowing that ``standard`` theme
    is always available and ready to be used, you don't need to configure
    **anything**, no design, no themes, and you can simply use ``standard``
    theme for your own templates.

Theme folders
-------------

For every theme you defined, system reserves some special folders where you need
to place the templates for them to be recognized. The folders are, in descending
order of priority:

* ``app/Resources/views/nglayouts/themes/<THEME NAME>``
* ``%twig.default_path%/nglayouts/themes/<THEME NAME>`` (for Symfony 3.4+, usually
  ``templates/nglayouts/themes/<THEME NAME>``)
* ``<PATH TO BUNDLE>/Resources/views/nglayouts/themes/<THEME_NAME>``

For folders inside the bundles, the bundles activated later have higher
priority.

As an example, if you have a design with two themes, ``theme1`` and ``theme2``,
and two bundles active, ``App\FirstBundle`` and ``App\SecondBundle`` (this one
being activated later), the system will look in the following folders for
templates, in descending order of priority (this includes the fallback to
``standard`` theme too and Symfony 3.4+ specific path):

* ``app/Resources/views/nglayouts/themes/theme1``
* ``templates/nglayouts/themes/theme1``
* ``src/SecondBundle/Resources/views/nglayouts/themes/theme1``
* ``src/FirstBundle/Resources/views/nglayouts/themes/theme1``
* ``app/Resources/views/nglayouts/themes/theme2``
* ``templates/nglayouts/themes/theme2``
* ``src/SecondBundle/Resources/views/nglayouts/themes/theme2``
* ``src/FirstBundle/Resources/views/nglayouts/themes/theme2``
* ``app/Resources/views/nglayouts/themes/standard``
* ``templates/nglayouts/themes/standard``
* ``src/SecondBundle/Resources/views/nglayouts/themes/standard``
* ``src/FirstBundle/Resources/views/nglayouts/themes/standard``

Using the theme templates
-------------------------

There are two usecases for using themes:

* Overriding the templates for existing layouts or blocks
* Creating templates for custom layouts or blocks

In both cases, using the theme templates is exactly the same. Once you define
a design and themes, you can reference the templates with a special Twig
namespace called ``@nglayouts``, followed by the template path, where template
path is anything **AFTER** the theme name in the template path on filesystem.
For example, ``@nglayouts/block/my_block.html.twig`` will look for the template
in the following paths:

* ``app/Resources/views/nglayouts/themes/theme1/block/my_block.html.twig``
* ``templates/nglayouts/themes/theme1/block/my_block.html.twig``
* ``src/SecondBundle/Resources/views/nglayouts/themes/theme1/block/my_block.html.twig``
* ...

Overriding the templates for existing layouts or blocks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Overriding the templates for existing layouts and blocks is made really simple
by using themes, since you don't need any configuration to override one of the
existing templates (apart from configuring the design and themes, obviously).

Lets take an example of a built in layout with the identifier ``layout_1``.
This template is located on disk at
``vendor/netgen/layouts-standard/bundle/Resources/views/nglayouts/themes/standard/layout/layout_1.html.twig``
path. As you can see, it's part of the ``standard`` theme, meaning, it can be
overridden by your themes, just by placing the new template at the correct path.
Any of the following paths would be valid (in no specific order of priority):

* ``templates/nglayouts/themes/standard/layout/layout_1.html.twig`` (for Symfony 3.4+)
* ``app/Resources/views/nglayouts/themes/theme1/layout/layout_1.html.twig``
* ``src/FirstBundle/Resources/views/nglayouts/themes/theme1/layout/layout_1.html.twig``
* ``app/Resources/views/nglayouts/themes/standard/layout/layout_1.html.twig``
* ``src/SecondBundle/Resources/views/nglayouts/themes/standard/layout/layout_1.html.twig``
* ...

Creating templates for custom layouts or blocks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Apart from referencing the templates with a new syntax, creating and using
templates for custom blocks and layouts does not differ. You still need to
create ``block_view`` or ``layout_view`` configuration to specify which template
your block will use. For example, to specify the template for a block with
identifier ``my_block``, you would use the following ``block_view``
configuration. Notice how we're referencing the template with our special
``@nglayouts`` Twig namespace:

.. code-block:: yaml

    netgen_layouts:
        view:
            block_view:
                default:
                    my_block\my_view_type:
                        template: "@nglayouts/block/my_block.html.twig"
                        match:
                            block\definition: my_block
                            block\view_type: my_view_type

The template itself would look like this:

.. code-block:: twig

    {% extends '@nglayouts/block/block.html.twig' %}

    {% block content %}
        ...
    {% endblock %}

As you can see, you can even reference the built in templates with
``@nglayouts`` Twig namespace in your templates, for extending them, including
them and so on.

.. warning::

    Not all built in templates can be referenced with ``@nglayouts`` namespace.
    Only layout, block (including the base block template) and item templates
    can be used with ``@nglayouts`` namespace. Referencing all other templates
    still works by using ``@NetgenLayouts`` namespace.

After you place your template in one of the paths discussed earlier, your
template will automatically be picked up and used for rendering your block.
