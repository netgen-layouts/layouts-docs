Creating a custom layout type
=============================

Netgen Layouts ships with some layout types (from simple ones with one zone, to
more complicated ones with 8 zones), which are readily available to be used in
your own projects without any additional configuration.

If none of those layout types satisfy your needs, you can create your own.
Creating your own layout type is split into three parts:

* Basic configuration
* Creating frontend and backend Twig templates for rendering the layout
* Connecting the templates with your layout type

We will demonstrate the process by creating a simple layout type with two zones:
``left`` and ``right``.

Basic configuration
-------------------

To register a new layout type in Netgen Layouts, add the following YAML config:

.. code-block:: yaml

    netgen_layouts:
        layout_types:
            my_layout:
                name: 'My layout'
                icon: '/path/to/icon.svg'
                zones:
                    left:
                        name: 'Left'
                    right:
                        name: 'Right'

This specifies that our new layout type has a ``my_layout`` identifier, that its
human readable name is ``My layout`` and that it has two zones, ``left`` and
``right``. It also specifies the full path to layout type icon.

.. tip::

    Since layout type icons are used in several places in admin interface and
    layout editing app in different sizes, it is recommended to create your own
    icons in SVG format, rather than PNG to allow the CSS to resize the icons.

Creating frontend and backend Twig templates
--------------------------------------------

Netgen Layouts uses two separate templates to render the layout on the frontend
and in the backend. By default, all frontend templates and backend templates for
built-in layout types are based on Bootstrap grid. Backend templates, used by
the layout editing app, will be rendered correctly as long as you provide the
valid Bootstrap markup. On the other hand, to render frontend templates
correctly, you will need to include CSS for Bootstrap Grid component in your
site.

.. note::

    It is possible to switch all frontend templates to use a different grid like
    Flexbox, however at this time, only Bootstrap implementation of templates is
    available.

Creating a backend template
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Backend templates for layout types usually do not have any logic, apart from
HTML markup that specifies where each of the layout type zones goes within
Bootstrap grid. If needed, backend templates can access the currently rendered
layout with a Twig variable named ``layout``.

The following template shows an example of how would the backend template look
for layout type we configured earlier:

.. code-block:: html+jinja

    {# @App/layouts/api/my_layout.html.twig #}

    <div class="row">
        <div class="col-md-8">
            <div data-zone="left"></div>
        </div>

        <div class="col-md-4">
            <div data-zone="right"></div>
        </div>
    </div>

It is important for backend templates to have ``<div data-zone="my_zone"></div>``
element with correct zone identifier (replacing ``my_zone``) for every zone
configured.

Creating a frontend template
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Frontend templates are usually more complicated, since they need to provide the
code to actually render layout zones by themselves.

All markup in frontend templates for your layout types needs to be inside a Twig
block named ``layout`` and they always need to extend a special
``nglayouts.pageLayoutTemplate`` variable available in the template. This variable
will always hold the name of the main pagelayout of your app, which is either
configured manually through Netgen Layouts configuration, or in some cases
picked up automatically from available configuration of your app (if using
eZ Platform for example).

This template has access to currently rendered layout via Twig variable named
``nglayouts.layout`` and each zone is rendered via ``nglayouts_render_zone``
Twig tag. By default, this tag simply renders all blocks one after another.

The complete frontend template for your custom layout type with two zones might
look something like this:

.. code-block:: html+jinja

    {# @App/layouts/my_layout.html.twig #}

    {% extends nglayouts.pageLayoutTemplate %}

    {% block layout %}
        <div class="container">
            <div class="row">
                <div class="col-lg-8">
                    {# You can use the zone object directly #}
                    {% nglayouts_render_zone nglayouts.layout.zone('left') %}
                </div>

                <div class="col-lg-4">
                    {# You can also only provide the zone identifier #}
                    {% nglayouts_render_zone 'right' %}
                </div>
            </div>
        </div>
    {% endblock %}

Connecting the templates with your layout type
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To activate the frontend and backend templates you defined, you will need to
configure them through the view layer configuration. Read up on what a view
layer is and the corresponding terminology in documentation specific to view
layer itself.

Currently, two matchers are implemented in the view layer for layout view:

* ``layout\type`` - Matches on layout type of a layout
* ``layout\shared`` - Matches on "shared" flag of a layout

Most of the time, you will use ``layout\type`` matcher for configuring templates
for your custom layout types. The reason for this is that shared layouts are
never rendered directly on the frontend so there is no really need for using
``layout\shared`` matcher. The reason for its existence is that it is used in
the administration interface of Netgen Layouts.

The following is an example config that enables the two templates we created:

.. code-block:: yaml

    netgen_layouts:
        view:
            layout_view:
                default:
                    my_layout:
                        template: "@App/layouts/my_layout.html.twig"
                        match:
                            layout\type: my_layout
                api:
                    my_layout:
                        template: "@App/layouts/api/my_layout.html.twig"
                        match:
                            layout\type: my_layout

At this point, your new layout type is ready for usage.
