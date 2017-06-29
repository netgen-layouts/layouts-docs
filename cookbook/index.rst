Cookbook
========

Netgen Layouts provides around 10 officially supported extension points, ranging
from simpler ones like creating custom layout types to advanced and rarely used
ones like creating custom conditions and targets for layout matching process.
The following chapters will go through each of these extension points and detail
the process of creating your own layout types, blocks, query types and so on.

Netgen Layouts does not force or otherwise define where your configuration code,
or templates live. The following examples will use YAML as a configuration
format, but you can ofcourse use any format available in Symfony and you can
place templates in folder structure that fits your needs best. As for templates,
to be able to actually use the templates you create, you need to tell
Netgen Layouts where they are, through so called view layer configuration of
Netgen Layouts. View layer and its configuration are explained in a dedicated
chapter.

.. toctree::
    :hidden:

    custom_layout_types
    custom_blocks
    custom_container_blocks
    block_collections
    custom_block_view_types
    custom_query_types

.. include:: /cookbook/map.rst.inc
