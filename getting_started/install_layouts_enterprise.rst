Install Netgen Layouts Enterprise
=================================

To install Netgen Layouts Enterprise, you need to have an existing Symfony full
stack installation (Ibexa CMS, Sylius, clean Symfony install...) with
Symfony Flex and Netgen Layouts open source edition installed and configured.

Add packages to Composer
------------------------

To install Netgen Layouts Enterprise, you need a valid license. Once purchased,
you need to add the license to Composer with the following command:

.. code-block:: shell

    composer config http-basic.packagist.netgen.biz <username> <token>

Next, add the ``packagist.netgen.biz`` Composer repository to ``repositories``
section of your ``composer.json``:

.. code-block:: json

    "repositories": [
        { "type": "composer", "url": "https://packagist.netgen.biz", "canonical": false }
    ]

Add the Netgen Layouts Flex Recipes repo to your ``composer.json``. If
``extra.symfony.endpoint`` already exists in your ``composer.json`` file, make
sure it is an array with ``flex://defaults`` at the very bottom:

.. code-block:: json

    "extra": {
        "symfony": {
            "allow-contrib": true,
            "endpoint": [
                "https://api.github.com/repos/netgen-layouts/recipes/contents/index.json?ref=flex",
                "flex://defaults"
            ]
        }
    }

Add the ``netgen/layouts-enterprise`` package to your ``require`` section. Use
the same version as the Netgen Layouts packages from open source edition. For
example, if you're using ``~1.0.0`` version of Netgen Layouts, use the same
``~1.0.0`` version for Netgen Layouts Enterprise too.

.. note::

    If you're installing Netgen Layouts Enterprise on Ibexa CMS, you need
    the ``netgen/layouts-enterprise-ibexa`` package too, in the same
    version as the other Netgen Layouts packages.

Run composer
------------

Run the following Composer command to install the packages:

.. code-block:: shell

    composer update --prefer-dist

.. warning::

    ``prefer-dist`` is used because it is not possible to install source
    packages from ``packagist.netgen.biz`` repository. Make sure to remember
    this when upgrading Netgen Layouts Enterprise to future versions.
