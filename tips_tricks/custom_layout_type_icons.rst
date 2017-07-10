How to add icons for custom layout types
========================================

Once you :doc:`add a custom layout type </cookbook/custom_layout_types>`, you
will notice that the icon is missing in Block Manager app and admin interface.
This is due to fact that icons are loaded through CSS, rather than through
configuration.

In order to add your own icon to Netgen Layouts, you will need to inject a piece
of CSS into Netgen Layouts configuration for admin interface and Block Manager
app.

.. warning::

    Since CSS classes cannot start with a number, layout type identifiers should
    not start with a number.

.. tip::

    Since layout type icons are used in several places in admin interface and
    Block Manager app in different sizes, it is recommended to create your own
    icons in SVG format, rather than PNG to allow the CSS to resize the icons.

If you wish to add an icon for a layout type with ``my_layout`` identifier in
admin interface, you can use the following CSS:

.. code-block:: css

    .layout-icon.my_layout {
        background-image: url(/path/to/icon/my_layout.svg);
    }

If you wish to add an icon for a layout type with ``my_layout`` identifier in
Block Manager app, you can use the following CSS:

.. code-block:: css

    [value="my_layout"] + label:before {
        background-image: url(/path/to/icon/my_layout.svg);
    }

After that, you need to register your CSS file in configuration:

.. code-block:: yaml

    netgen_block_manager:
        admin:
            stylesheets:
                - '/path/to/bmadmin/style.css'
        app:
            stylesheets:
                - '/path/to/bmapp/style.css'
