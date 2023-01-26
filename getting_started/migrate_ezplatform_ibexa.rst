Migrate Netgen Layouts from eZ Platform to Ibexa CMS
====================================================

Migrating Netgen Layouts from eZ Platform to Ibexa boils down to renaming
various namespaces, classes, templates, configuration, identifiers etc.
Basically, any nomenclature that previously included ``ez`` or ``ezplatform``
strings has been renamed to ``ibexa``.

Renamed Composer packages
-------------------------

Replace the following packages in your ``composer.json`` with the new names.
All versions of the packages listed below remain the same. If you don't have
some of the packages listed below, simply skip them, i.e. there is no need to
add them to your ``composer.json``:

.. rst-class:: responsive

+---------------------------------------------------+----------------------------------------------+
| Old package name                                  | New package name                             |
+===================================================+==============================================+
| ``netgen/layouts-ezplatform``                     | ``netgen/layouts-ibexa``                     |
+---------------------------------------------------+----------------------------------------------+
| ``netgen/layouts-ezplatform-site-api``            | ``netgen/layouts-ibexa-site-api``            |
+---------------------------------------------------+----------------------------------------------+
| ``netgen/layouts-enterprise-ezplatform``          | ``netgen/layouts-enterprise-ibexa``          |
+---------------------------------------------------+----------------------------------------------+
| ``netgen/layouts-ezplatform-relation-list-query`` | ``netgen/layouts-ibexa-relation-list-query`` |
+---------------------------------------------------+----------------------------------------------+
| ``netgen/layouts-ezplatform-tags-query``          | ``netgen/layouts-ibexa-tags-query``          |
+---------------------------------------------------+----------------------------------------------+
| ``netgen/content-browser-ezplatform``             | ``netgen/content-browser-ibexa``             |
+---------------------------------------------------+----------------------------------------------+

Renamed namespaces
------------------

All namespaces (and classes) have been renamed to include Ibexa in its name
instead of ``EzPlatform`` or ``Ez``. Refer to the table below to see which
namespaces have been renamed:

.. rst-class:: responsive

+------------------------------------------------------------+-------------------------------------------------------+
| Old namespace name                                         | New namespace name                                    |
+============================================================+=======================================================+
| ``Netgen\Layouts\Ez``                                      | ``Netgen\Layouts\Ibexa``                              |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\LayoutsEzPlatformBundle``                  | ``Netgen\Bundle\LayoutsIbexaBundle``                  |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Layouts\Ez\SiteApi``                              | ``Netgen\Layouts\Ibexa\SiteApi``                      |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\LayoutsEzPlatformSiteApiBundle``           | ``Netgen\Bundle\LayoutsIbexaSiteApiBundle``           |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Layouts\Enterprise\Ez``                           | ``Netgen\Layouts\Enterprise\Ibexa``                   |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\LayoutsEnterpriseEzPlatformBundle``        | ``Netgen\Bundle\LayoutsEnterpriseIbexaBundle``        |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Layouts\Ez\RelationListQuery``                    | ``Netgen\Layouts\Ibexa\RelationListQuery``            |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\LayoutsEzPlatformRelationListQueryBundle`` | ``Netgen\Bundle\LayoutsIbexaRelationListQueryBundle`` |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Layouts\Ez\TagsQuery``                            | ``Netgen\Layouts\Ibexa\TagsQuery``                    |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\LayoutsEzPlatformTagsQueryBundle``         | ``Netgen\Bundle\LayoutsIbexaTagsQueryBundle``         |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\ContentBrowser\Ez``                               | ``Netgen\ContentBrowser\Ibexa``                       |
+------------------------------------------------------------+-------------------------------------------------------+
| ``Netgen\Bundle\ContentBrowserEzPlatformBundle``           | ``Netgen\Bundle\ContentBrowserIbexaBundle``           |
+------------------------------------------------------------+-------------------------------------------------------+

Renamed bundles
---------------

The following bundle names have also been renamed. This impacts not only
changing the bundle name in your ``bundles.php``, but also importing routes,
referencing to templates and so on.

.. rst-class:: responsive

+----------------------------------------------------+-----------------------------------------------+
| Old bundle name                                    | New bundle name                               |
+====================================================+===============================================+
| ``NetgenLayoutsEzPlatformBundle``                  | ``NetgenLayoutsIbexaBundle``                  |
+----------------------------------------------------+-----------------------------------------------+
| ``NetgenLayoutsEzPlatformSiteApiBundle``           | ``NetgenLayoutsIbexaSiteApiBundle``           |
+----------------------------------------------------+-----------------------------------------------+
| ``NetgenLayoutsEnterpriseEzPlatformBundle``        | ``NetgenLayoutsEnterpriseIbexaBundle``        |
+----------------------------------------------------+-----------------------------------------------+
| ``NetgenLayoutsEzPlatformRelationListQueryBundle`` | ``NetgenLayoutsIbexaRelationListQueryBundle`` |
+----------------------------------------------------+-----------------------------------------------+
| ``NetgenLayoutsEzPlatformTagsQueryBundle``         | ``NetgenLayoutsIbexaTagsQueryBundle``         |
+----------------------------------------------------+-----------------------------------------------+
| ``NetgenContentBrowserEzPlatformBundle``           | ``NetgenContentBrowserIbexaBundle``           |
+----------------------------------------------------+-----------------------------------------------+

Renamed entity identifiers in the database
------------------------------------------

All identifiers of entities in Netgen Layouts database have also been renamed.
To migrate your database, execute the following SQL commands:

.. code-block:: sql

    UPDATE nglayouts_block
    SET definition_identifier = 'ibexa_content_field'
    WHERE definition_identifier = 'ezcontent_field';

    UPDATE nglayouts_block
    SET view_type = 'ibexa_content_field'
    WHERE definition_identifier = 'ibexa_content_field' AND view_type = 'ezcontent_field';

    UPDATE nglayouts_collection_item
    SET value_type = 'ibexa_location'
    WHERE value_type = 'ezlocation';

    UPDATE nglayouts_collection_item
    SET value_type = 'ibexa_content'
    WHERE value_type = 'ezcontent';

    UPDATE nglayouts_collection_query
    SET type = 'ibexa_content_search'
    WHERE type = 'ezcontent_search';

    UPDATE nglayouts_rule_condition
    SET type = 'ibexa_site_access'
    WHERE type = 'ez_site_access';

    UPDATE nglayouts_rule_condition
    SET type = 'ibexa_site_access_group'
    WHERE type = 'ez_site_access_group';

    UPDATE nglayouts_rule_condition
    SET type = 'ibexa_content_type'
    WHERE type = 'ez_content_type';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_location'
    WHERE type = 'ez_location';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_content'
    WHERE type = 'ez_content';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_children'
    WHERE type = 'ez_children';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_subtree'
    WHERE type = 'ez_subtree';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_semantic_path_info'
    WHERE type = 'ez_semantic_path_info';

    UPDATE nglayouts_rule_target
    SET type = 'ibexa_semantic_path_info_prefix'
    WHERE type = 'ez_semantic_path_info_prefix';
