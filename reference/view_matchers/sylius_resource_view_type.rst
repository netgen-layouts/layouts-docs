``sylius_resource\view_type``
=============================

Matches on the view type of the rendered Sylius resource. Used in
``sylius_resource_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            sylius_resource_view:
                default:
                    product\short:
                        template: '@App/layouts/product/short.html.twig'
                        match:
                            sylius_resource\view_type: short
