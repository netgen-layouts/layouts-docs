``sylius_resource\instance``
============================

Matches on the PHP class of the rendered Sylius resource. Used in
``sylius_resource_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            sylius_resource_view:
                default:
                    product:
                        template: '@App/layouts/product.html.twig'
                        match:
                            sylius_resource\instance: Sylius\Component\Product\Model\ProductInterface
