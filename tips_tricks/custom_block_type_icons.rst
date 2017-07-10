How to add icons for custom block types
=======================================

Once you :doc:`add a custom block definition and corresponding block type </cookbook/custom_blocks>`,
you will notice that the icon is missing in Block Manager app. This is due to
fact that icons are loaded through CSS, rather than through configuration.

In order to add your own icon to Netgen Layouts, you will need to inject a piece
of CSS into Netgen Layouts configuration for Block Manager app.

.. warning::

    Since CSS classes cannot start with a number, block definition and block
    type identifiers should not start with a number.

If you wish to add an icon for a block type with ``my_block`` identifier in
Block Manager app, you can use the following CSS:

.. code-block:: css

    .add-block-btn.icn-my_block .icon {
        background-image: url(/path/to/icon/my_layout.svg);
    }

After that, you need to register your CSS file in configuration:

.. code-block:: yaml

    netgen_block_manager:
        app:
            stylesheets:
                - '/path/to/bmapp/style.css'
