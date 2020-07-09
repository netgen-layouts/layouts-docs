Upgrading from 1.1.0 to 1.2.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/layouts-core``
package and all other related packages (like ``netgen/layouts-standard``,
``netgen/layouts-ezplatform`` and others) to ``~1.2.0`` and run the
``composer update`` command.

Database migration
------------------

Run the following command from the root of your installation to execute
migration to version 1.2 of Netgen Layouts (if you're using Doctrine Migrations
v3):

.. code-block:: shell

    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine.yaml

or in case of Doctrine Migrations v2:

.. code-block:: shell

    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine2.yaml

.. note::

    If the above commands fail with errors about unrecognized configuration keys,
    you most probably ran the command for the wrong version of Doctrine
    Migrations. In that case, just try running the other one to migrate correctly.

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 1.2 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_110_120.html>`_
too.

Netgen Layouts Enterprise upgrade notes
---------------------------------------

.. note::

    This section is only relevant if you use Netgen Layouts Enterprise.

Since Netgen Layouts Enterprise 1.2, the code switched from BitBucket to GitHub.
Usually, there will be no issues when upgrading Netgen Layouts Enterprise to 1.2,
but in case any issues arise related to non-existing files/versions when
upgrading, they can be fixed by removing the ``composer.lock`` file and
``vendor/netgen/`` folder and running ``composer update`` again.

Changelog
---------

Major features
~~~~~~~~~~~~~~

* Enabled export of mappings (in open source version) and roles and policies (in
  Enterprise version)
* Enabled import of all supported entities (mappings, layouts, roles, policies)
  through admin interface
* Import procedure can now overwrite or skip existing entities, in addition to
  creating a new copy of the entity. Entities are considered same if they have
  the same UUID.

Other changes
~~~~~~~~~~~~~

* Minimum supported PHP version is now 7.3

Deprecations
------------

* ``LayoutsService::hasStatus`` method has been deprecated and will be removed
  in 2.0. Use ``LayoutsService::layoutExists`` method instead.

* Block plugin interface method
  ``Netgen\Layouts\Block\BlockDefinition\Handler\PluginInterface::getExtendedHandlers``
  changed the return type hint from ``array`` to a backwards compatible
  ``iterable`` type (``array`` type is a subtype of ``iterable``) in order to
  allow usage of ``yield`` keyword in the method implementations. E.g. you can
  now write the method like this:

  .. code-block:: php

      public static function getExtendedHandlers(): iterable
      {
          yield MyBlockHandler::class;
          yield MyOtherBlockHandler::class;
      }

  If you don't need ``yield``, there's nothing for you to do, however, if you
  wish to use ``yield`` in the method, or just for consistency sake, you can
  update your block plugins to use the ``iterable`` return typehint.

* Not implementing ``TargetTypeInterface::export`` and
  ``TargetTypeInterface::import`` methods is deprecated and they will be added
  to ``TargetTypeInterface`` in 2.0. Implement these methods in your target
  types or make them extend ``Netgen\Layouts\Layout\Resolver\TargetType``
  abstract class to remove the deprecation.

  The purpose of these methods is to provide an alternate value for your targets
  when exporting/importing them. E.g. you can provide some form of a remote ID
  instead of an autoincremented database ID usually stored in a target.

* Not implementing ``ConditionTypeInterface::export`` and
  ``ConditionTypeInterface::import`` methods is deprecated and they will be added
  to ``ConditionTypeInterface`` in 2.0. Implement these methods in your condition
  types or make them extend ``Netgen\Layouts\Layout\Resolver\ConditionType``
  abstract class to remove the deprecation.

  The purpose of these methods is to provide an alternate value for your
  conditions when exporting/importing them. E.g. you can provide some form of a
  remote ID instead of an autoincremented database ID usually stored in a
  condition.

* From eZ Platform kernel 7.5.7 onwards, you can use ``ContentTypeIdentifier``
  criterion without making sure that the content type identifiers exist, while
  previously in order to avoid exceptions, you would have to use ``ContentTypeId``
  criterion.

  Consequently, if you created custom eZ Platform query types and used
  ``ContentTypeFilterTrait`` helper trait available in Netgen Layouts, there is
  no more need to provide content type handler to the trait. The corresponding
  method (``setContentTypeHandler``) and property (``$this->contentTypeHandler``)
  will be removed in 2.0. Related method
  ``ContentTypeFilterTrait::getContentTypeIds`` will also be removed. Migrate
  your query types to use ``ContentTypeIdentifier`` criterion instead of using
  ``ContentTypeId`` criterion.

Breaking changes
----------------

There were no breaking changes in 1.2 version of Netgen Layouts.
