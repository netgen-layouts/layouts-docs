Creating a custom block
=======================

Similar to layout types, when creating a custom block, you need a bit of
configuration and some templates, but since blocks almost always need some
custom logic, you will also need to create a PHP class that will handle custom
functionalities of a block. In the following examples, we will show creating a
custom block that can render a Markdown document.

When creating a custom block, you will often run into two entities mentioned in
code and configuration: a block definition, and a block type. Before you
actually create a custom block, it is important to understand a difference
between a block definition and a block type.

Difference between block definition & block type
------------------------------------------------

Block definition is the central entity you will be creating when creating a
custom block. As the name implies, block definition **defines** how your custom
block behaves. This includes specifying what parameters will the block have and
what type are they of and if the block has a collection or not. It also gives
you a possibility to write your own custom behaviour for a block, based on block
parameters. In case of container blocks, it specifies which placeholders the
container block has.

Each block definition can have multiple block types. Block type is nothing more
than a starting configuration used when creating a block in a layout. In
layout editing app, block types are what is shown on the left side and what you
drag and drop to a zone in a layout. Creating block types for a certain block
definition requires only a couple of lines of configuration where you would
specify starting values for block label, block view, block item view and block
parameters.

Once you create a block in a layout, it doesn't store the information from which
block type it was created, it only stores the block definition. When you think
about it, this makes sense. Since block type is a starting configuration for a
block you're adding to a layout, and that configuration can change in the
lifecycle of a block, there is no benefit in storing the information which block
type was used to create the block. On the other hand, block definition needs to
be stored because it defines how block parameters will be validated, what custom
behaviour the block has and so on.

Configuring a new block definition
----------------------------------

To register a new block definition in Netgen Layouts, you will need the
following configuration:

.. code-block:: yaml

    netgen_layouts:
        block_definitions:
            my_markdown:
                name: 'My markdown block'
                icon: '/path/to/icon.svg'
                view_types:
                    my_markdown:
                        name: 'My markdown block'

This configuration example adds a new block definition with ``my_markdown``
identifier, which as a human readable name ``My markdown block`` and has one
view type, also called ``my_markdown``. It also specifies the full path to the
icon of the block.

View type is nothing more than an identifier of a template which will be used to
render the block. Every block definition needs at least one view type.

.. note::

    By convention, in built in blocks, if a block definition has only one view
    type, like above, that view type will have the same identifier as the block
    definition itself.

Creating a PHP service for a block definition
---------------------------------------------

Every block definition needs a single PHP class that specifies the entire
behaviour of a block. This class needs to implement
``Netgen\Layouts\Block\BlockDefinition\BlockDefinitionHandlerInterface``
interface which specifies a number of methods for you to implement. To simplify
implementing new block definitions, an abstract class exists
(``Netgen\Layouts\Block\BlockDefinition\BlockDefinitionHandler``) which has all
of those methods implemented with default and empty implementations, reducing
the need for writing boilerplate code.

Let's create a basic block definition handler class:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace AppBundle\Block\BlockDefinition\Handler;

    use Netgen\Layouts\API\Values\Block\Block;
    use Netgen\Layouts\Block\BlockDefinition\BlockDefinitionHandler;
    use Netgen\Layouts\Block\DynamicParameters;
    use Netgen\Layouts\Parameters\ParameterBuilderInterface;

    final class MyMarkdownHandler extends BlockDefinitionHandler
    {
        public function buildParameters(ParameterBuilderInterface $builder): void
        {
        }

        public function getDynamicParameters(DynamicParameters $params, Block $block): void
        {
        }

        public function isContextual(Block $block): bool
        {
        }
    }

Specifying block parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~

First method we will look at is ``buildParameters`` method. By using an object
called parameter builder and adding parameter specifications to it, this method
will specify which parameters your custom block will have. Details on how the
parameter builder works, what parameter types exist and how to implement custom
parameter type are explained in dedicated chapter.

Let's add a custom parameter to our block which will serve as an input for raw
Markdown content:

.. code-block:: php

    use Netgen\Layouts\Parameters\ParameterType;

    public function buildParameters(ParameterBuilderInterface $builder): void
    {
        $builder->add('content', ParameterType\TextType::class);
    }

Notice that we didn't specify the human readable labels for the parameters.
That's because they are generated automatically via translation system. To
create the correct labels for your block parameters, you need to add one string
to ``nglayouts`` translation catalog for every parameter in your block with the
format ``block.<block_definition>.<parameter_name>`` where ``block_definition``
and ``parameter_name`` are placeholders that need to be replaced with correct
values. So, for our custom Markdown block definition, the translation file would
look something like this:

.. code-block:: yaml

    block.my_markdown.content: 'Content'

Custom block behaviour
~~~~~~~~~~~~~~~~~~~~~~

Second method in our handler example above is called ``getDynamicParameters``.
This method is used for your own custom logic. Anything goes in this method. You
can inject dependencies into your block definition handler, use them here, do
some processing based on provided instance of a block or some other parameters
you provide when rendering a block manually and so on.

After all processing is done, this method needs to set the parameters which will
be injected into template when block is rendered. The parameters are set to an
instance of ``Netgen\Layouts\Block\DynamicParameters`` object. This object
implements ``ArrayAccess`` interface, so you can use array notation to add the
parameters. Each of the values can either be a regular scalar, array, object and
so on, or it can be a closure, which will transparently be called to calculate
the value at the moment the parameter is used inside the block template.

In case of our Markdown handler, we will need to inject a Markdown parser into
our handler, and use it in this method to parse the raw Markdown into HTML. We
will be using ``Michelf\MarkdownInterface``, Markdown parser which is already
pre-installed with Netgen Layouts:

.. code-block:: php

    /**
     * @var \Michelf\MarkdownInterface
     */
    private $markdownParser;

    public function __construct(MarkdownInterface $markdownParser)
    {
        $this->markdownParser = $markdownParser;
    }

    public function getDynamicParameters(DynamicParameters $params, Block $block): void
    {
        $rawContent = $block->getParameter('content')->getValue();

        $params['html'] = $this->markdownParser->transform($rawContent);
    }

Contextual blocks
~~~~~~~~~~~~~~~~~

A contextual block is a block which needs the current context (i.e. current
request) to function. For example, a block that needs a currently displayed
location or content from eZ Platform is a contextual block.

In order for the system to work properly with contextual blocks,
``isContextual`` method needs to be implemented, which signals to the system if
the block is contextual or not. You can use any property of the provided block
to decide if it contextual or not, but in our case, we will simply return
``false``:

.. code-block:: php

    public function isContextual(Block $block): bool
    {
        return false;
    }

Defining the Symfony service for our handler
--------------------------------------------

To connect the created handler with block definition configuration, we need to
register the handler in Symfony DIC. We also need to specify a service for
Markdown parser we used in the handler:

.. code-block:: yaml

    services:
        app.markdown:
            class: Michelf\MarkdownExtra

        app.block.block_definition.handler.markdown:
            class: AppBundle\Block\BlockDefinition\Handler\MyMarkdownHandler
            arguments:
                - "@app.markdown"
            tags:
                - { name: netgen_block_manager.block.block_definition_handler, identifier: my_markdown }

This configuration is a fairly regular specification of services in Symfony,
however, to correctly recognize our PHP class as a block definition handler, we
need to tag it with ``netgen_block_manager.block.block_definition_handler`` tag
and attach to it an ``identifier`` key with a value which equals to the
identifier of block definition we configured at the beginning (in this case
``my_markdown``).

Specifying block view templates
-------------------------------

Every view type in your block definition needs to have two templates, one for
frontend and one for backend. If you remember, we specified that our
``my_markdown`` block definition has one view type, also called ``my_markdown``.

Frontend block template
~~~~~~~~~~~~~~~~~~~~~~~

Let's create a template for displaying the block in the frontend with
``my_markdown`` view type. Every frontend template for the block needs to extend
from ``@nglayouts/block/block.html.twig`` and all content of the template needs
to be inside Twig block called ``content``. The currently rendered block is
accessible via ``block`` variable which you can use to access block parameters
specified in the handler as well as any dynamic parameters in the block.

.. tip::

    View type templates for built in block definitions are also a great source
    of inspiration, so make sure to give them a look.

Our frontend template for the Markdown block definition will simply output the
parsed Markdown which is provided by the handler:

.. code-block:: jinja

    {# @App/blocks/my_markdown/my_markdown.html.twig #}

    {% extends '@nglayouts/block/block.html.twig' %}

    {% block content %}
        {{ block.dynamicParameter('html')|raw }}
    {% endblock %}

Backend block template
~~~~~~~~~~~~~~~~~~~~~~

As for backend, in this specific case, the template will look **almost** the
same (since all we want is to render the parsed Markdown), save for the
different template used to extend from.

In general, all backend templates need to extend from
``@NetgenLayouts/api/block/block.html.twig`` and in most cases, backend
template will be simpler than the frontend one, without any design specific
markup and so on. Everything you can use in frontend templates is also available
here, meaning that you can use the ``block`` variable to access the block and
its parameters.

Going back to our example backend template, it will look like this:

.. code-block:: jinja

    {# @App/blocks/api/my_markdown/my_markdown.html.twig #}

    {% extends '@NetgenLayouts/api/block/block.html.twig' %}

    {% block content %}
        {{ block.dynamicParameter('html')|raw }}
    {% endblock %}

Connecting the templates with your block definition
---------------------------------------------------

To activate the frontend and backend templates you defined, you will need to
configure them through the view layer configuration. Read up on what a view
layer is and the corresponding terminology in documentation specific to view
layer itself.

Currently, two matchers are implemented in the view layer for block view:

* ``block\definition`` - Matches on block definition of a block
* ``block\view_type`` - Matches on view type of a block

If you are creating a block which will only have a single view type, you can
omit the ``block\view_type`` matcher and use only ``block\definition`` matcher,
which will make sure that templates you defined will be applied to any future
view types of your block automatically.

The following is an example config that enables the two templates we created:

.. code-block:: yaml

    netgen_layouts:
        view:
            block_view:
                default:
                    my_markdown:
                        template: "@App/blocks/my_markdown/my_markdown.html.twig"
                        match:
                            block\definition: my_markdown
                            # View type matcher is optional
                            block\view_type: my_markdown
                api:
                    my_markdown:
                        template: "@App/blocks/api/my_markdown/my_markdown.html.twig"
                        match:
                            block\definition: my_markdown
                            # View type matcher is optional
                            block\view_type: my_markdown

The following configuration shows how you can specify a fallback template that
will be applied to all block view types that do not specify their own template
rules:

.. code-block:: yaml

    netgen_layouts:
        view:
            block_view:
                default:
                    my_markdown:
                        template: "@App/block/my_markdown.html.twig"
                        match:
                            block\definition: my_block
                api:
                    my_markdown:
                        template: "@App/api/block/my_markdown.html.twig"
                        match:
                            block\definition: my_block

.. note::

    Take care to specify the fallback rule at the bottom of all other rules,
    since the first rule that matches will be used when searching for templates.

After you have defined the configuration for the view layer, your block is ready
for usage.

Defining block types for your block definition
----------------------------------------------

Remember block types and how we said that block types are a starting
configuration for a block definition? Remember how we said that block types are
the thing that is shown on the left hand side in the layout editing app?

When you create a custom block definition, Netgen Layouts internally creates for
you a single block type with the same name as block definition with empty
default configuration, and adds it to a block type group called "Custom blocks".
This is to enable the block definition to be displayed in the interface so you
can actually add it to a layout.

If you want to create another starting configuration for your block definition,
you can do so by configuring an additional block type which will also be
automatically added to a "Custom blocks" group. For example:

.. code-block:: yaml

    netgen_layouts:
        block_types:
            my_markdown_v2:
                name: 'My Markdown block with default title'
                icon: '/path/to/icon.svg'
                definition_identifier: my_markdown
                defaults:
                    parameters:
                        content: '# Some default title'

This configuration defines a block type with ``my_markdown_v2`` identifier,
which sets a default value for ``content`` parameter.

If you want to define some other group where your block type should live, you
can do so. In that case, the block type will not be shown in the ``Custom blocks``
group, but in the group you specified. You can use the configuration similar to
this:

.. code-block:: yaml

    netgen_layouts:
        block_type_groups:
            my_group:
                name: 'My group'
                block_types: [my_markdown_v2, second_block_type, other_block_type]

.. tip::

    Once you start adding more and more block types for your block definition, you
    might decide that you no longer need the automatically created block type with
    empty configuration. In that case, you might want to simply disable it:

    .. code-block:: yaml

        netgen_layouts:
            block_types:
                my_markdown:
                    enabled: false
