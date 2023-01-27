Upgrading from 1.3.0 to 1.4.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/layouts-core``
package and all other related packages (like ``netgen/layouts-standard``,
``netgen/layouts-ibexa`` and others) to ``~1.4.0`` and run the
``composer update`` command.

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 1.4 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_130_140.html>`_
too.

Upgrading your templates
------------------------

1.4 version of Netgen Layouts added an advanced layout preview. With it, you
can add (removing is not yet possible) and manipulate blocks directly from the
preview interface.

To support this, some of your Twig templates need to be updated.

Updating your pagelayout
~~~~~~~~~~~~~~~~~~~~~~~~

Somewhere in your main page layout, you will need to add the following to your
``head`` element:

.. code-block:: twig

    <head>
        ...

        {{ nglayouts_template_plugin('preview.javascripts') }}

        ...
    </head>

Before the end of your ``body`` element, add the following:

.. code-block:: twig

        ...

        {{ nglayouts_template_plugin('preview.body') }}
    </body>

Updating your base frontend block template
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have overridden base frontend ``block.html.twig`` template from
Netgen Layouts in your own project, you will also need to add some markup
related to preview to your override. An example diff can be found `on GitHub`_.

Changelog
---------

Major features
~~~~~~~~~~~~~~

* Added block manipulation features to layout preview (available only in
  Enterprise version)
* Added support for components in Ibexa CMS integration. Components are
  special blocks that act as a 1:1 proxy to an Ibexa content. Components use
  view types defined in attached content as opposed to statically defined list
  of view types in Netgen Layouts config.

Other changes
~~~~~~~~~~~~~

* Added full support for PHP 8.1
* Added PHP 8.x attributes for simplified registering of Symfony services for
  various extension points
* Dropped support for PHP 8.0

Deprecations
------------

* Base template for all admin block templates
  ``@NetgenLayoutsAdmin/app/block/block.html.twig`` is deprecated and will be
  removed in 2.0. Use ``@nglayouts_admin/app/block/block.html.twig`` instead.
* ``ValueUrlGeneratorInterface::generate`` method is deprecated and is replaced
  by two new methods in newly added interface ``ExtendedValueUrlGeneratorInterface``:
  ``generateDefaultUrl`` and ``generateAdminUrl``. These two methods generate item
  paths for frontend and backend, respectively. Implement the new interface in your
  value URL generators and call the ``generateDefaultUrl`` in your ``generate``
  method to migrate. Note that the ``ExtendedValueUrlGeneratorInterface`` interface
  is immediately deprecated and will be merged into ``ValueUrlGeneratorInterface``
  interface and removed in 2.0.
* While not strictly a deprecation but related to the point above,
  ``nglayouts_item_path`` Twig function now receives a second argument with two
  possible values: ``default`` (this value being the default one) and ``admin`` in
  order to specify which URL you wish to generate. Update your calls to
  ``nglayouts_item_path`` Twig function as needed to make sure the correct URL is
  generated for your items.

Breaking changes
----------------

There were no breaking changes in 1.4 version of Netgen Layouts.

.. _`on GitHub`: https://bit.ly/3GxaFwj
