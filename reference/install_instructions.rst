Install instructions
====================

To install Netgen Layouts, you need to have an existing Symfony full stack
installation. For example, Netgen Layouts can be installed on eZ Platform,
Sylius or Symfony Demo app.

Use Composer
------------

Add the following to your ``composer.json``. During installation, you will be
asked for username and password to ``packagist.netgen.biz``, make sure you have
them ready:

.. code-block:: json

    {
        "repositories": [
            { "type": "composer", "url": "https://packagist.netgen.biz" }
        ]
    }

Execute the following from your installation root:

.. code-block:: shell

    $ composer require netgen/block-manager-standard netgen/block-manager

.. note::

    If you're installing Netgen Layouts on eZ Platform, execute the following
    instead:

    .. code-block:: shell

        $ composer require netgen/block-manager-standard netgen/block-manager-ezpublish netgen/platform-ui-layouts-bundle

.. note::

    If you use Netgen Admin UI, you can also install `netgen/admin-ui-layouts-bundle`
    package and activate `Netgen\Bundle\AdminUILayoutsBundle\NetgenAdminUILayoutsBundle`
    bundle in your `AppKernel` to enable integration of Netgen Layouts into
    Netgen Admin UI.

Activate the bundles
--------------------

Add the following bundles to your kernel:

.. code-block:: php

    new Knp\Bundle\MenuBundle\KnpMenuBundle(),
    new FOS\HttpCacheBundle\FOSHttpCacheBundle(),
    new Sensio\Bundle\FrameworkExtraBundle\SensioFrameworkExtraBundle(),
    new Doctrine\Bundle\MigrationsBundle\DoctrineMigrationsBundle(),
    new WhiteOctober\PagerfantaBundle\WhiteOctoberPagerfantaBundle(),
    new Netgen\Bundle\CoreUIBundle\NetgenCoreUIBundle(),
    new Netgen\Bundle\ContentBrowserBundle\NetgenContentBrowserBundle(),
    new Netgen\Bundle\ContentBrowserUIBundle\NetgenContentBrowserUIBundle(),
    new Netgen\Bundle\BlockManagerBundle\NetgenBlockManagerBundle(),
    new Netgen\Bundle\BlockManagerStandardBundle\NetgenBlockManagerStandardBundle(),
    new Netgen\Bundle\BlockManagerUIBundle\NetgenBlockManagerUIBundle(),
    new Netgen\Bundle\BlockManagerAdminBundle\NetgenBlockManagerAdminBundle(),

.. note::

    If you're installing Netgen Layouts on eZ Platform, activate the following
    bundles too:

    .. code-block:: php

        new Netgen\Bundle\EzPublishBlockManagerBundle\NetgenEzPublishBlockManagerBundle(),
        new Netgen\Bundle\PlatformUILayoutsBundle\NetgenPlatformUILayoutsBundle(),

Add the following bundle to your kernel **only for dev environment**:

.. code-block:: php

    new Netgen\Bundle\BlockManagerDebugBundle\NetgenBlockManagerDebugBundle(),

Import database tables
----------------------

Execute the following from your installation root to import Netgen Layouts database tables:

.. code-block:: shell

    $ php app/console doctrine:migrations:migrate --configuration=vendor/netgen/block-manager/migrations/doctrine.yml

Configuration
-------------

Starting from version 1.12 of eZ Platform, `there is a configuration`__ that
caches 404 pages with a low TTL to increase performance. This cache interferes
with Netgen Layouts REST API endpoints which return 404 responses in their
normal operation workflow.

To disable cache on Netgen Layouts API endpoints, add the following options to
``app/config/config.yml`` under the ``match`` key of ``fos_http_cache``
configuration responsible for caching 404 pages:

.. code-block:: yaml

    attributes:
        _route: "^(?!ngbm_api_|ngcb_api_)"

The whole ``match`` configuration should then look like this:

.. code-block: yaml

    match:
        attributes:
            _route: "^(?!ngbm_api_|ngcb_api_)"
        match_response: '!response.isFresh() && response.isNotFound()'

Routing and assets
------------------

Add the following routes to your main routing config file:

.. code-block:: yaml

    netgen_block_manager:
        resource: "@NetgenBlockManagerBundle/Resources/config/routing.yml"
        prefix: "%netgen_block_manager.route_prefix%"

    netgen_content_browser:
        resource: "@NetgenContentBrowserBundle/Resources/config/routing.yml"
        prefix: "%netgen_content_browser.route_prefix%"

Run the following from your installation root to symlink assets:

.. code-block:: shell

    $ php app/console assets:install --symlink --relative

.. note::

    If you're installing Netgen Layouts on eZ Platform, you also need to dump
    Assetic assets:

    .. code-block:: shell

        $ php app/console assetic:dump

Adjusting your full views
-------------------------

All of your full views need to extend ``ngbm.layoutTemplate`` variable (see
below for example). If layout was resolved, this variable will hold the name of
the template belonging to the resolved layout. In case when layout was not
resolved, it will hold the name of your main pagelayout template (the one your
full views previously extended). This makes it possible for your full view
templates to be fully generic, that is, not depend whether there is a resolved
layout or not:

.. code-block:: jinja

    {% extends ngbm.layoutTemplate %}

    {% block content %}
        {# My full view code #}
    {% endblock %}

Adjusting your base pagelayout template
---------------------------------------

To actually display the resolved layout template in your page, you need to
modify your main pagelayout template to include a Twig block named layout which
wraps everything between your opening and closing ``<body>`` tag:

.. code-block:: html+jinja

    <body>
        {% block layout %}
            {# Other Twig code #}

            {% block content %}{% endblock %}

            {# Other Twig code #}
        {% endblock %}
    </body>

There are two goals to achieve with the above Twig block:

- If no layout could be resolved for current page, your full view templates will
  just keep on working as before

- If layout is resolved, it will use the ``layout`` block, in which case
  ``content`` Twig block and other Twig code will not be used. You will of
  course need to make sure that in this case, all your layouts have a full view
  block in one of the zones which will display your ``content`` Twig block from
  full view templates

Configuring the pagelayout
--------------------------

As written before, Netgen Layouts replaces the pagelayout in your full views
with its dynamic variable called ``ngbm.layoutTemplate``. It basically injects
itself between rendering of your full view and your pagelayout. Since your full
views do not extend from your main pagelayout any more, Netgen Layouts needs to
know what was your original full view to fallback to it. You can configure your
pagelayout in Netgen Layouts config like this:

.. code-block:: yaml

    netgen_block_manager:
        pagelayout: '@App/pagelayout.html.twig'

.. note::

    If you're installing Netgen Layouts on eZ Platform, your main pagelayout is
    taken from existing eZ Platform configuration, so you can skip this step.

Update Varnish VCL configuration
--------------------------------

To enable caching and later cache clearing of block and layout HTTP caches, you
will need to use Varnish. To make the cache clearing work, you need to modify
your Varnish VCL and add the following rules somewhere in your ``vcl_recv``
function.

.. note::

    If you're using eZ Platform and the VCL supplied by it, the best place
    to put this is in ``ez_purge`` function (which is called from ``vcl_recv``),
    right after ``if (req.http.X-Location-Id) { ... }`` block.

For Varnish 3:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban( "obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        error 200 "Banned";
    }

    if (req.http.X-Block-Id) {
        ban( "obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        error 200 "Banned";
    }

For Varnish 4 and later:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban("obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        return (synth(200, "Banned"));
    }

    if (req.http.X-Block-Id) {
        ban("obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        return (synth(200, "Banned"));
    }

.. _`eZ Platform pull request #213`: https://github.com/ezsystems/ezplatform/pull/213/files#diff-bf0e70bcef1a5d5b2f87289220a51108

__ `eZ Platform pull request #213`_
