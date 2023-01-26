Install Netgen Layouts Enterprise
=================================

To install Netgen Layouts Enterprise, you need to have an existing Symfony full
stack installation (Ibexa CMS, Sylius, clean Symfony install...) with
Netgen Layouts open source edition installed and configured.

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

Add the ``netgen/layouts-enterprise`` package to your ``require`` section. Use
the same version as the Netgen Layouts packages from open source edition. For
example, if you're using ``~1.0.0`` version of Netgen Layouts, use the same
``~1.0.0`` version for Netgen Layouts Enterprise too.

.. note::

    If you're installing Netgen Layouts Enterprise on Ibexa CMS, you need
    the ``netgen/layouts-enterprise-ibexa`` package too, in the same
    version as the other Netgen Layouts packages.

Activate the bundles
--------------------

Add the following bundles to your configuration:

.. code-block:: php

    Netgen\Bundle\LayoutsEnterpriseBundle\NetgenLayoutsEnterpriseBundle::class => ['all' => true],
    Netgen\Bundle\LayoutsEnterpriseAdminBundle\NetgenLayoutsEnterpriseAdminBundle::class => ['all' => true],
    Netgen\Bundle\LayoutsEnterpriseUIBundle\NetgenLayoutsEnterpriseUIBundle::class => ['all' => true],

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, activate the following
    bundle too after all of the bundles listed above:

    .. code-block:: php

        Netgen\Bundle\LayoutsEnterpriseIbexaBundle\NetgenLayoutsEnterpriseIbexaBundle::class => ['all' => true],

Make sure to activate these bundles after all other Netgen Layouts bundles.

Run Composer
------------

.. note::

    Make sure you run Composer only after adding the bundles to your
    configuration. Otherwise, important frontend assets will not be installed.
    In that case, you can install the assets later by running the following
    command:

    .. code-block:: shell

        php bin/console assets:install --symlink --relative

Run the following Composer command to install the packages:

.. code-block:: shell

    composer update --prefer-dist

.. warning::

    ``prefer-dist`` is used because it is not possible to install source
    packages from ``packagist.netgen.biz`` repository. Make sure to remember
    this when upgrading Netgen Layouts Enterprise to future versions.

Routing and assets
------------------

Add the following routes to your main routing config file. Make sure you add
them after all other Netgen Layouts routes:

.. code-block:: yaml

    netgen_layouts_enterprise:
        resource: "@NetgenLayoutsEnterpriseBundle/Resources/config/routing.yaml"
        prefix: "%netgen_layouts.route_prefix%"

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, activate the following
    routes too after the routes listed above:

    .. code-block:: yaml

        netgen_layouts_enterprise_ibexa:
            resource: "@NetgenLayoutsEnterpriseIbexaBundle/Resources/config/routing.yaml"
