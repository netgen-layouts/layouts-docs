Upgrading from 1.4.0 to 2.0.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/layouts-core``
package and all other related packages (like ``netgen/layouts-standard``,
``netgen/layouts-ibexa`` and others) to ``~2.0.0`` and run the
``composer update`` command.

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 2.0 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_140_200.html>`_
too.

Breaking changes
----------------

* Minimum supported version of PHP is now 8.4

* Minimum supported version of Symfony is now 7.3

* Layouts exported with older version of Netgen Layouts cannot be imported into
  version 2.0

* Ramsey UUID has been replaced by Symfony Uid component. Replace your
  typehints to use ``Symfony\Component\Uid\Uuid`` instead of
  ``Ramsey\Uuid\UuidInterface`` and ``Ramsey\Uuid\Uuid``.

* Missing parameter and return types have been added. This is mostly contained
  to missing union types and the ``mixed`` type. Mostly, the types have been
  taken from existing PHPDoc annotations, but in certain cases, where it was
  physically impossible to pass or return some types, those were made more
  strict. This should not have impact on your existing code (apart from adding
  the required types as needed).

* Property hooks and asymmetric visibility have been introduced across the
  board. This means that wherever possible (meaning, in value objects), getters
  have been removed and replaced with properties.

  This will have most impact on your query type handlers, where you directly
  access the ``Query`` object to execute queries:

  Before:

  .. code-block:: php

      $value = $query->getParameter('param')->getValue();
      $isEmpty = $query->getParameter('param')->isEmpty();

  After:

  .. code-block:: php

      $value = $query->getParameter('param')->value;
      $isEmpty = $query->getParameter('param')->isEmpty;

  This change is (mostly) backwards compatible with your existing Twig
  templates.

  Note that in cases of boolean getters (e.g. ``isEmpty()`` method replaced with
  ``isEmpty`` property in ``Netgen\Layouts\Parameters\Parameter`` class), you
  will need to update your Twig templates to use the new name, since Twig does
  not have fallback for ``is*`` methods like it has for getter methods:

  Before:

  .. code-block:: twig

      {% if block.parameter('foo').empty %}

  After:

  .. code-block:: twig

      {% if block.parameter('foo').isEmpty %}

* In API value objects, ``$status`` property is now an enum of type
  ``Netgen\Layouts\API\Values\Status`` instead of an integer. This change is
  also reflected in API services and other classes wherever status is provided
  as one of the arguments/properties/return values.

* ``nglayouts_item_path`` Twig function cannot be used any more to generate
  admin URLs to your items. A new function, ``nglayouts_item_admin_path`` has
  been implemented for that purpose:

  Before:

  .. code-block:: twig

      {{ nglayouts_item_path(item, 'admin') }}

  After:

  .. code-block:: twig

      {{ nglayouts_item_admin_path(item) }}

* ``Netgen\Layouts\API\Values\Layout\Layout`` and
  ``Netgen\Layouts\API\Values\Block\Placeholder`` do not implement
  ``ArrayAccess``, ``Countable`` and ``IteratorAggregate`` any more. Use
  ``Layout::$zones`` or ``Placeholder::$blocks`` properties directly instead.

* ``@NetgenLayoutsAdmin/app/block/block.html.twig`` template has been removed.
  Use ``@nglayouts_admin/app/block/block.html.twig`` instead.

* ``BlockService::loadPlaceholderBlocks`` method has been added to the
  interface.

* ``LayoutResolverService::loadRules`` method has been removed. Use
  ``LayoutResolverService::loadRulesFromGroup`` or
  ``LayoutResolverService::loadRulesForLayout`` instead.

* ``LayoutResolverService::getRuleCount`` method has been removed. Use
  ``LayoutResolverService::getRuleCountFromGroup`` or
  ``LayoutResolverService::getRuleCountForLayout`` instead.

* ``LayoutResolverService::loadCondition`` method has been removed. Use
  ``LayoutResolverService::loadRuleCondition`` instead.

* ``LayoutResolverService::loadConditionDraft`` method has been removed. Use
  ``LayoutResolverService::loadRuleConditionDraft`` instead.

* ``LayoutResolverService::createDraft`` method has been removed. Use
  ``LayoutResolverService::createRuleDraft`` instead.

* ``LayoutResolverService::discardDraft`` method has been removed. Use
  ``LayoutResolverService::discardRuleDraft`` instead.

* ``LayoutResolverService::restoreFromArchive`` method has been removed. Use
  ``LayoutResolverService::restoreRuleFromArchive`` instead.

* ``LayoutResolverService::addCondition`` method has been removed. Use
  ``LayoutResolverService::addRuleCondition`` instead.

* ``LayoutResolverService::updateCondition`` method has been removed. Use
  ``LayoutResolverService::updateRuleCondition`` instead.

* ``LayoutService::hasStatus`` method has been removed. Use
  ``LayoutResolverService::layoutExists`` instead.

* ``BlockCreateStruct::$name`` property does not accept nulls any more.

* ``LayoutCreateStruct::$description`` property does not accept nulls any more.

* ``Rule::getComment`` method has been removed in favor or ``$description``
  property.

* ``RuleCreateStruct::$comment`` has been removed in favor of ``$description``
  property.

* ``RuleUpdateStruct::$comment`` has been removed in favor of ``$description``
  property.

* ``Netgen\Layouts\Block\BlockDefinition\Handler\PluginInterface::getExtendedIdentifiers``
  has been added to the interface. If you extended the abstract
  ``Netgen\Layouts\Block\BlockDefinition\Handler\Plugin`` class in your plugins,
  you don't have to do anything here as the empty method implementation is
  already available there. Otherwise, implement the method in your plugins.

* ``Netgen\Layouts\Item\ExtendedValueUrlGeneratorInterface`` interface has been
  removed and merged into the main
  ``Netgen\Layouts\Item\ValueUrlGeneratorInterface`` interface.

* ``Netgen\Layouts\Item\ValueUrlGeneratorInterface::generate`` method has been
  removed. Implement ``generateDefaultUrl`` and ``generateAdminUrl`` instead.

* ``Netgen\Layouts\Layout\Resolver\ConditionTypeInterface::export`` and
  ``Netgen\Layouts\Layout\Resolver\ConditionTypeInterface::import`` have been
  added to the interface. If you extended the abstract
  ``Netgen\Layouts\Layout\Resolver\ConditionType`` class in your condition
  types, you don't have to do anything here as the empty method implementations
  are already available there. Otherwise, implement the methods in your
  condition types.

* ``Netgen\Layouts\Layout\Resolver\TargetTypeInterface::export`` and
  ``Netgen\Layouts\Layout\Resolver\TargetTypeInterface::import`` have been
  added to the interface. If you extended the abstract
  ``Netgen\Layouts\Layout\Resolver\TargetType`` class in your target types, you
  don't have to do anything here as the empty method implementations are
  already available there. Otherwise, implement the methods in your target
  types.

* ``$request`` argument of ``LayoutResolverInterface::resolveRule`` method does
  not accept nulls any more. Current request should be provided instead of
  passing null.

* ``LayoutResolverInterface::matches`` method has been removed without
  replacement.

* ``nglayouts.admin.match`` event name has been removed in favor of using
  the ``Netgen\Bundle\LayoutsAdminBundle\Event\AdminMatchEvent`` class as the
  event name.

* ``Netgen\Layouts\Event\CollectViewParametersEvent`` event class has been
  split into ``Netgen\Layouts\Event\BuildViewEvent`` and
  ``Netgen\Layouts\Event\RenderViewEvent``. It also removed the possibility to
  add view parameters directly to the event. Access the view inside the event
  and add the parameters to the view itself.

* ``nglayouts.view.build_view`` event name has been removed in favor of using
  ``Netgen\Layouts\Event\BuildViewEvent`` class as the event name.

* ``nglayouts.view.render_view`` event name has been removed in favor of using
  ``Netgen\Layouts\Event\RenderViewEvent`` class as the event name.

* ``type`` attribute in ``netgen_layouts.parameter_type.form_mapper`` DI tag has
  been renamed to ``parameter_type`` for consistency with other form mapper DI
  tags

* Sylius Product and Sylius Taxon parameter type values have been converted to
  integers as opposed to numeric strings as were before. Update your query
  type handlers and templates to work with the new type if needed.

Deprecations
------------

* There are no deprecations in Netgen Layouts 2.0.
