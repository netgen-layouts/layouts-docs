How to inject current eZ location and content in blocks and query types
=======================================================================

.. note::

    This tutorial is eZ Platform/eZ Publish 5 specific.

Often, your custom block definitions and query types need the current
eZ Platform location or content to work. While you can extract the information
about the current location and content from the ``Request`` object, the
differences between different versions of eZ kernel make it impossible to create
generic block definitions and query types that work on any eZ kernel
available.

That's why there is a handy Symfony service called Content Provider in
Netgen Layouts that can be used to retrieve the current location or content in a
generic way. In background, this service uses different implementations of a
service that extracts content and locations from the request for every eZ kernel
version available.

.. note::

    If using eZ Publish 5, you need to specify a Symfony service alias somewhere
    in your configuration which makes sure that an eZ 5 version of the extractor
    is used:

    .. code-block:: yaml

        netgen_block_manager.ezpublish.content_extractor:
            alias: netgen_block_manager.ezpublish.content_extractor.ez5_request

Service identifier of the Content Provider is
``netgen_block_manager.ezpublish.content_provider`` and you can inject it into
your block definitions and query types like any other service.

Content Provider exposes two methods: ``provideLocation`` and ``provideContent``
which return the location and content from the current request and ``null`` if
no location or content exist.

As an example, you can use the Content Provider to inject the location and
content objects into Twig templates for your blocks:

.. code-block:: php

    <?php

    namespace AppBundle\Block\BlockDefinition\Handler;

    use Netgen\BlockManager\API\Values\Block\Block;
    use Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandler;
    use Netgen\BlockManager\Ez\ContentProvider\ContentProviderInterface;

    class MyBlockHandler extends BlockDefinitionHandler
    {
        /**
         * @var \Netgen\BlockManager\Ez\ContentProvider\ContentProviderInterface
         */
        protected $contentProvider;

        /**
         * Constructor.
         *
         * @param \Netgen\BlockManager\Ez\ContentProvider\ContentProviderInterface $contentProvider
         */
        public function __construct(ContentProviderInterface $contentProvider)
        {
            $this->contentProvider = $contentProvider;
        }

        /**
         * Adds the dynamic parameters to the $params object for the provided block.
         *
         * @param \Netgen\BlockManager\Block\DynamicParameters $params
         * @param \Netgen\BlockManager\API\Values\Block\Block $block
         */
        public function getDynamicParameters(DynamicParameters $params, Block $block)
        {
            $params['content'] = $this->contentProvider->provideContent();
            $params['location'] = $this->contentProvider->provideLocation();
        }
    }
