Main concepts
=============

Layout related
--------------

* **Layout** - a core object, responsible for rendering the layout of a page
  with all Blocks added to it. It is instantiated from a Layout Type. Editing a
  layout opens the Block Manager drag & drop interface in which the user is able
  to manage Blocks.

* **Layout Type** - a blueprint for creating a Layout. It has an associated Twig
  template and configuration for Zones. There are several prebuilt Layout Types
  for most common layout structures, but it is easy to develop a custom
  Layout Type.

* **Zone** - a placeholder for Blocks that are added to a Layout. There could be
  more Zones in a Layout. More Blocks can be added to one Zone and they are
  rendered sequentially. A Zone has an identifier, such as ``top``, ``right``,
  ``prefooter`` or similar.

* **Shared Layout/Zones** - a special layout that can't be mapped to any page
  directly. Its purpose is to hold blocks that can be reused in other Layouts.
  There is a special mode in Block Manager when editing a Layout, to link a Zone
  with a Zone from a Shared Layout. When rendering the Zone, it will render
  Blocks from the linked Shared Zone instead.

* **Layout mappings** - a priority list of configurations where you map a layout
  to a Target under the certain Condition.

* **Target** - an abstraction which defines one or more URLs where Layout is
  mapped in a generic way or Backend specific (e.g. eZ location or Symfony
  route).

* **Condition** - additional conditions that need to match for Layout to be
  selected for rendering.

* **Layout Resolver** - a module that figures out which Layout to use for each
  URL and page request. It goes through the mappings and finds the first
  configuration that fits the context, then renders the mapped Layout.

Block related
-------------

* **Block** - another core object responsible for handling specific features. It
  gets instantiated from a Block Type. A Block can be added to a Zone, moved,
  removed, duplicated and configured in the Block Manager interface.

* **Block Type** - a configuration used when Block is created. It defines which
  Block Definition is used and with what default parameter values. All
  configured Block Types are available in the left panel of the Block Manager
  interface.

* **Block Definition** - a class (+ some configuration) in PHP which defines
  Block’s features, which Parameters does it have, which Collections does it
  support. It is possible to add custom Block Definitions.

* **Block Parameter** - every block can have more parameters. They are shown on
  the right panel in the Block Manager interface when the Block is selected.

* **Block Plugins** - special features whose implementation is separated from
  the Block Definition but can be plugged in and reused in more Block Definitions
  at the same time. They offer a simple way to extend the original
  Block Definitions, even reduce them.

* **Block View** - a special parameter for Blocks to offer different templates
  for rendering the Block. In a nutshell, it is a Twig template related to a
  Block Definition and it's very simple to add custom ones.

* **Container** - a special kind of Block whose purpose is to hold other Blocks
  and render them. A Container can have one or more Block placeholders. There
  are several prebuilt Containers (1 column, 2 columns, 3 columns, 4 columns).

Block item related
------------------

* **Block Item** - an abstracted item coming from a backend system. It is
  usually rendered with the Block Item View Twig template.

* **Block Item View** - a special parameter for Blocks to offer different
  templates for rendering the Block Item.

* **Collection** - an object holding Block Items, can be either manual or
  dynamic. For a manual collection, the items are picked from a backend system
  with the Content Browser. In the case of dynamic collection, a Query fetches
  the data but it is still possible to add manual items and mix them with the
  fetched items.

* **Query Type** - a class that implements fetching data from a local or remote
  backend system. It is possible to add custom Query Types.

Other
-----

* **Backend** - a system that is responsible for managing content like CMS or
  eCommerce, integrated with Netgen Layouts. Backend Integration could consist
  of a set of custom extensions: query types, block views, block item views and
  Content Browser customisations.

* **Block Manager** - an interface for managing Blocks in a Layout. Besides
  providing basic Block actions, it also provides Shared Zone linking, Block
  Parameter translation, changing the Layout Type, etc.

* **Layout Manager** - an interface for managing Layouts, Shared Layouts, Layout
  mappings and User Roles and Policies. It also provides cache clearing for
  Layouts and Blocks and exporting Layouts to JSON format.

* **Roles and Policies Manager** - an interface for configuring user roles and
  policies.

* **Content Browser** - a standalone interface for browsing content from a
  backend system and selecting one or more items. It is decoupled from Layouts
  and has its own documentation.
