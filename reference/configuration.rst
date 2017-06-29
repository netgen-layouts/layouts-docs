Configuration reference
=======================

Layout type configuration
~~~~~~~~~~~~~~~~~~~~~~~~~

The following lists all available layout type configuration options:

.. code-block:: yaml

    netgen_block_manager:
        layout_types:
            # Layout type identifier
            my_layout:
                # The switch to enable or disable showing of the layout type in the interface
                enabled: true
                # Layout type name, required
                name: 'My layout'

                # A collection of zones available in the layout type, required
                zones:
                    # Zone identifier
                    left:
                        # Zone name, required
                        name: 'Left'

                        # List of block definitions which are allowed in the zone
                        allowed_block_definitions: []
                    right:
                        name: 'Right'
                        allowed_block_definitions: [title]

Block definition configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following lists all available block definition configuration options:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            # Block definition identifier
            my_block:
                # The switch to enable or disable showing of all block types
                # related to block definition in the interface
                enabled: true

                # Identifier of a handler which the block definition will use.
                # The value used here needs to be the same as the identifier
                # specified in handler tag in Symfony DIC.
                # If undefined, the handler with the same identifier as the
                # block definition itself will be used.
                handler: ~

                # Block definition name, required
                name: 'My block'

                # The list of collections the block has. Only one collection named
                # "default" is supported for now. Omit the config to disable the collection.

                collections:
                    default:
                        # The list of valid item types for the collection. Use null to
                        # allow all item types, an empty array to disable adding manual
                        # items, and a list of item type identifiers to limit the collection
                        # to those item types.
                        valid_item_types: null

                        # The list of valid query types for the collection. Use null to
                        # allow all query types, an empty array to disable dynamic collections,
                        # and a list of query type identifiers to limit the collection
                        # to those query types.
                        valid_query_types: null

                # This controls which forms will be available to the block.
                # You can either enable the full form, or content and design forms.
                # If full form is enabled, all block options in the right sidebar
                # in the Block Manager app will be shown at once, otherwise,
                # Content and Design tabs will be created in the right sidebar
                forms:
                    full:
                        enabled: true
                        type: Netgen\BlockManager\Block\Form\FullEditType
                    design:
                        enabled: false
                        type: Netgen\BlockManager\Block\Form\DesignEditType
                    content:
                        enabled: false
                        type: Netgen\BlockManager\Block\Form\ContentEditType

                # The list of all view types in a block definition, required
                view_types:

                    # View type identifier
                    my_view_type:
                        # Switch to control if the view type is shown in the interface or not
                        enabled: true

                        # View type name, required
                        name: 'My view type'

                        # The list of allowed item view types for this block view type
                        item_view_types:

                            # Item view type identifier
                            my_item_view_type:
                                # Switch to control if the item view type is shown in the interface or not
                                enabled: true

                                # Item view type name, required
                                name: 'My item view type'

                        # Use this configuration to control which block parameters will be displayed
                        # when editing a block in specified view type. Use null to display all
                        # parameters, an empty array to hide all parameters and a list of parameter
                        # names to list specific parameters to show. You can also prefix the parameter
                        # with exclamation mark to exclude it.
                        valid_parameters: null

Block type and block type group configuration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following lists all available block type and block type group configuration options:

.. code-block:: yaml

    netgen_block_manager:
        block_types:
            # Block type identifier
            my_block_type:
                # The switch to enable or disable showing the block type in the interface
                enabled: true

                # Block type name, if undefined, will use the name of a block definition
                # with the same identifier as the block type itself.
                name: ~

                # Block definition identifier of the block type, if undefined, will use the
                # block definition with the same identifier as the block type itself.
                definition_identifier: ~

                # Default values for the block
                defaults:

                    # Default name (label) of the block
                    name: ''

                    # Default view type of the block. If empty, will use the first available view type.
                    view_type: ''

                    # Default item view type of items inside the block. If empty, will use the first
                    # available item view type in regards to chosen block view type.
                    item_view_type: ''

                    # Default values for block parameters
                    parameters:
                        param1: value1
                        param2: value2

        block_type_groups:

            # Block type group identifier
            my_group:

                # The switch to enable or disable showing the block type group in the interface
                enabled: true

                # Block type group name, required
                name: 'My group'

                # List of block types to show inside the group
                block_types: [my_type_1, my_type_2]
