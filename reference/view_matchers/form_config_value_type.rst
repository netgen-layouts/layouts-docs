``form\config\value_type``
==========================

Matches on the type of value for which the config is edited through the Symfony
form. Used in ``form_view`` view.

.. tip::

    This matcher is usually used with ``form\config\config_key`` matcher because
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
