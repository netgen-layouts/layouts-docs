How to add a new Ibexa CMS / eZ Platform component
==================================================

.. note::

    This tutorial is Ibexa CMS / eZ Platform specific.

To add a new component, no PHP is needed, only a simple configuration block:

.. code-block:: yaml

    netgen_layouts:
        block_types:
            ibexa_component_hero:
                name: 'Hero'
                definition_identifier: ibexa_component
                icon: '/public/images/components/icon-component-hero.svg'
                defaults:
                    view_type: hero_style_1
                    parameters:
                        content_type_identifier: ng_component_hero

With the configuration above, the component is defined and ready to be used.

The following list explains various configuration entries in the config above:

* ``ibexa_component_hero``: Identifier of the component. This value will be used
  when e.g. adding a block plugin specific to this component.
* ``name``: The name of the component, to be displayed in add block sidebar.
  This is a required value.
* ``definition_identifier``: System identifier of the block definition which all
  components use. This is a required value and the only supported value is
  ``ibexa_component`` (or ``ezcomponent`` in case of eZ Platform)
* ``icon``: The public path to the icon of the component. Optional.
* ``defaults.view_type``: The default view type that the component will use
  after it is created. This config is required and must be valid for the content
  type attached to the component.
* ``defaults.content_type_identifier``: The content type of the content that
  this component will use. Only content of the selected content type can be
  added to the component. This is a required value.

Additionally, you can add the configuration as below to define the default
parent location ID when creating a content which will be added to the component:

.. code-block:: yaml

    ibexa: # "ezpublish" in case of eZ Platform
        system:
            default:
                ibexa_component: # "ezcomponent" in case of eZ Platform
                    parent_locations:
                        ng_component_hero: 42

Here, ``ng_component_hero`` is a content type specified in the configuration
which creates the component (``defaults.content_type_identifier``).
