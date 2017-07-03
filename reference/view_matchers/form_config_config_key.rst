``form\config\config_key``
==========================

Matches on the config key of a config which is edited through the Symfony form.
Used in ``form_view`` view.

.. tip::

    This matcher is usually used with ``form\config\value_type`` matcher because
    most of the time, forms for rendering different aspects of value
    configuration will be different.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            form_view:
                default:
                    config\block\http_cache\edit:
                        template: '@App/config/block/http_cache/edit.html.twig'
                        match:
                            form\type: Netgen\BlockManager\Config\Form\EditType
                            form\config\value_type: Netgen\BlockManager\API\Values\Block\Block
                            form\config\config_key: http_cache
