Creating a custom container block
=================================

Containers are blocks like any other, so everything described in chapter on
creating a custom block applies here.

The difference between regular blocks and containers is that containers can
contain other blocks. This is achieved by using something called a placeholder,
which is nothing more than a label which is applied to every child block in a
container. When rendering the container, you can use this label to specify where
in the template will all blocks with that label be rendered. As with zones, all
blocks with a specified label will be rendered one after another.

Think of a placeholder in the container block as a lightweight variant of a zone
in a layout. When you drag and drop a new block to a placeholder in a container,
placeholder label is automatically assigned to the new block so it can be
rendered when requested.

.. note::

    Currently, it is not possible to add containers within containers.

Container definition handler
----------------------------

When creating a custom block definition handler for a container block, instead
of extending from ``Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandler``
abstract class, you will extend from
``Netgen\BlockManager\Block\BlockDefinition\ContainerDefinitionHandler`` which
is also an abstract class. What is left for you to do is to define which
placeholders your new container block has by implementing
``getPlaceholderIdentifiers`` method. For example, ``Two columns`` container
block provided by Netgen Layouts looks like this:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace Netgen\BlockManager\Block\BlockDefinition\Handler\Container;

    use Netgen\BlockManager\Block\BlockDefinition\ContainerDefinitionHandler;

    final class TwoColumnsHandler extends ContainerDefinitionHandler
    {
        public function getPlaceholderIdentifiers(): array
        {
            return ['left', 'right'];
        }
    }

Twig templates
--------------

Frontend Twig templates for container blocks have all the same features as Twig
templates for regular blocks. The only difference is that in templates for
container blocks, you can use ``ngbm_render_placeholder`` Twig function to
render all blocks which are located in specified placeholder.

For example, frontend Twig template for ``Two columns`` block provided by
Netgen Layouts looks like this:

.. code-block:: html+jinja

    {% extends '@NetgenBlockManager/block/block.html.twig' %}

    {% block content %}
        <div class="row">
            <div class="col-md-6">
                {{ ngbm_render_placeholder(block, 'left') }}
            </div>
            <div class="col-md-6">
                {{ ngbm_render_placeholder(block, 'right') }}
            </div>
        </div>
    {% endblock %}

As for backend Twig templates for container blocks, they are similar to backend
Twig templates for layout types. They do not need custom logic to render the
blocks, except specific HTML elements used as markers for block placeholders:

.. code-block:: html+jinja

    {% extends '@NetgenBlockManager/api/block/block.html.twig' %}

    {% block content %}
        <div class="row">
            <div class="col-md-6">
                <div data-placeholder="left" data-receiver></div>
            </div>
            <div class="col-md-6">
                <div data-placeholder="right" data-receiver></div>
            </div>
        </div>
    {% endblock %}

Basically, for every placeholder in your container block, you need to have a
``<div data-placeholder="my_placeholder" data-receiver></div>`` element with a
placeholder identifier in ``data-placeholder`` attribute.
