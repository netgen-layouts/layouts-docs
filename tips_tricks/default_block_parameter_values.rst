How to specify default value for block parameters
=================================================

As you probably know, you can create a new block in a layout by drag and
dropping it from the left sidebar to the layout. This means that there is no way
to specify the starting values for the parameters in the block. Instead, the
default values provided in the block definition are used.

This is not a problem per se, but it does mean that in cases when you do need
different starting values than those provided by the block definition, you need
to add a block and immediately edit it in the right sidebar to change the
parameter values to more suitable ones. This only slows down layout creation
process.

To overcome this, you can specify default values for any block parameter in
the configuration. For example, if you want to change the default number of
columns of a Grid block, you would use a configuration like this one:

.. code-block:: yaml

    block_types:
        grid:
            defaults:
                parameters:
                    number_of_columns: 6

From now on, every time you add a Grid block to your layout, it will be created
with 6 columns.
