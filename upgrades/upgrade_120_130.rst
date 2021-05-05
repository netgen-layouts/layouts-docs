Upgrading from 1.2.0 to 1.3.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/layouts-core``
package and all other related packages (like ``netgen/layouts-standard``,
``netgen/layouts-ezplatform`` and others) to ``~1.3.0`` and run the
``composer update`` command.

Database migration
------------------

Run the following command from the root of your installation to execute
migration to version 1.3 of Netgen Layouts (if you're using Doctrine Migrations
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

Netgen Content Browser version 1.3 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_120_130.html>`_
too.

Changelog
---------

Major features
~~~~~~~~~~~~~~

* Added support for mapping groups (available only in Enterprise version)
* Redesigned mapping admin interface in open source version to match the design
  of Enterprise version

Other changes
~~~~~~~~~~~~~

* Minimum supported PHP version is now 7.4
* Property typehints were added to all properties (private, protected, and
  public) in Netgen Layouts. Extreme care has been taken to make the property
  hints compatible with previously existing PHPDoc annotations. This makes sure
  that any properly used code from Netgen Layouts (e.g. public properties in
  create/update structs) will not result in breaking changes.
* Added support for PHP 8. Note that parameter names are not part of the
  backwards compatibility rules. Using PHP 8's named arguments feature might
  break your code when upgrading to newer Netgen Layouts versions.

Deprecations
------------

* Deprecated ``LayoutResolverService::loadRules`` method. Use
  ``LayoutResolverService::loadRulesForLayout`` or
  ``LayoutResolverService::loadRulesFromGroup`` with root group (the one having
  a NIL UUID), depending on whether you used the ``$layout`` argument or not,
  respectively.

* Deprecated ``LayoutResolverService::getRuleCount`` method. Use
  ``LayoutResolverService::getRuleCountForLayout`` or
  ``LayoutResolverService::getRuleCountFromGroup`` with root group (the one
  having a NIL UUID), depending on whether you used the ``$layout`` argument or
  not, respectively.

* Deprecated ``LayoutResolverService::loadCondition`` method. Use
  ``LayoutResolverService::loadRuleCondition`` method instead.

* Deprecated ``LayoutResolverService::loadConditionDraft`` method. Use
  ``LayoutResolverService::loadRuleConditionDraft`` method instead.

* Deprecated ``LayoutResolverService::createDraft`` method. Use
  ``LayoutResolverService::createRuleDraft`` method instead.

* Deprecated ``LayoutResolverService::discardDraft`` method. Use
  ``LayoutResolverService::discardRuleDraft`` method instead.

* Deprecated ``LayoutResolverService::restoreFromArchive`` method. Use
  ``LayoutResolverService::restoreRuleFromArchive`` method instead.

* Deprecated ``LayoutResolverService::addCondition`` method. Use
  ``LayoutResolverService::addRuleCondition`` method instead.

* Deprecated ``LayoutResolverService::updateCondition`` method. Use
  ``LayoutResolverService::updatedRuleCondition`` method instead.

* Deprecated ``Rule::getComment`` method. Use ``Rule::getDescription`` instead.
  This deprecation also applies to using the ``Rule``object in Twig templates:
  use ``rule.description`` instead of ``rule.comment``.

* Deprecated ``RuleCreateStruct::$comment`` property. Use
  ``RuleCreateStruct::$description`` instead. Note that the ``$description``
  property does not accept ``null`` as ``$comment`` did. Use an empty string
  instead.

* Deprecated ``RuleUpdateStruct::$comment`` property. Use
  ``RuleUpdateStruct::$description`` instead.

* Deprecated setting the value of ``BlockCreateStruct::$name`` property to
  ``null``. Use an empty string instead.

* Deprecated setting the value of ``LayoutCreateStruct::$description`` property
  to ``null``. Use an empty string instead.

Breaking changes
----------------

There were no breaking changes in 1.3 version of Netgen Layouts.
