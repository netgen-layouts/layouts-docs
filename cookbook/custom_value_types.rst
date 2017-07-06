Creating custom value types
===========================

In Netgen Layouts, (block) item is a generic concept in a way that blocks do not
(and should not) care what kind of items are put inside the blocks. To achieve
this, a block item is a wrapper around a value object which comes from your CMS.
For example, in eZ Platform integration, Netgen Layouts supports two types of
values: eZ location and eZ content.

To be able to create block items from your own domain objects, you need to
create and register your own custom **value type**. Value type has three
purposes:

* Loading of your domain object from the CMS by its ID by using a value loader
* Handling the domain objects provided by your custom query types by using a
  value converter
* Generating the URL to the domain object by using a value URL builder

Registering a new value type
----------------------------

To be able to use your domain objects inside Netgen Layouts as block items, you
need to register a new value type in the configuration. To do so, you need to
provide a unique identifier for your value type and a human readable name:

.. code-block:: yaml

    netgen_block_manager:
        items:
            value_types:
                my_value_type:
                    name: 'My value type'

This configuration registers a new value type in the system with
``my_value_type`` identifier.

Implementing a value loader
---------------------------

A value loader is an object responsible for loading your domain object by its
ID. It is an implementation of ``Netgen\BlockManager\Item\ValueLoaderInterface``
which provides a single method called ``load``. This method takes the ID of the
domain object and should simply return the object once loaded or throw an
exception if the object could not be loaded.

For example:

.. code-block:: php

    /**
     * Loads the value from provided ID.
     *
     * @param int|string $id
     *
     * @throws \Netgen\BlockManager\Exception\Item\ItemException If value cannot be loaded
     *
     * @return mixed
     */
    public function load($id)
    {
        try {
            return $this->myBackend->loadMyObject($id);
        } catch (Exception $e) {
            throw new ItemException(
                sprintf('Object with ID "%s" could not be loaded.', $id),
                0,
                $e
            );
        }
    }

Implementing Content Browser support
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To be able to actually select the items from the CMS and add them to your
blocks, you also need to
`implement a Netgen Content Browser backend </projects/cb/en/latest/cookbook/custom_backend.html>`_.

To automatically recognize which backend is responsible for which value types,
you need to make sure that the identifier of the item in the
Netgen Content Browser backend you implemented is the same as the identifier of
the value type you configured above.

Implementing a value converter
------------------------------

As you're probably aware, query types need not worry themselves about returning
PHP objects specific to Netgen Layouts to work. Instead, they simply return
domain objects which are then converted by Netgen Layouts into block items.

Converting the domain objects to Netgen Layouts items is done through so called
value converters and every value type needs to have a value converter
implemented. Value converter should implement
``Netgen\BlockManager\Item\ValueConverterInterface``, which provides methods
that return the data used by Netgen Layouts to work with block items, like the
ID of the object, name and if the object is considered visible in your CMS.

Method ``supports`` should return if the value converter supports the given
object. Usually, you will check if the provided object is of correct interface.
This makes it possible to handle different types of value objects in the same
value converter. For example, in eZ Platform, ``Content`` and ``ContentInfo``
are two different objects that represent the same piece of content in the CMS,
but with different usecases in mind.

Method ``getValueType`` should simply return the identifier of the value type
you choose when activating the value type in the configuration.

An example implementation of a value converter might look something like this:

.. code-block:: php

    <?php

    namespace AppBundle\Item\ValueConverter;

    use App\MyValue;
    use Netgen\BlockManager\Item\ValueConverterInterface;

    class MyValueTypeConverter implements ValueConverterInterface
    {
        /**
         * Returns if the converter supports the object.
         *
         * @param mixed $object
         *
         * @return bool
         */
        public function supports($object)
        {
            return $object instanceof MyValue;
        }

        /**
         * Returns the value type for this object.
         *
         * @param mixed $object
         *
         * @return string
         */
        public function getValueType($object)
        {
            return 'my_value_type';
        }

        /**
         * Returns the object ID.
         *
         * @param \App\MyValue $object
         *
         * @return int|string
         */
        public function getId($object)
        {
            return $object->id;
        }

        /**
         * Returns the object name.
         *
         * @param \App\MyValue $object
         *
         * @return string
         */
        public function getName($object)
        {
            return $object->name;
        }

        /**
         * Returns if the object is visible.
         *
         * @param \App\MyValue $object
         *
         * @return bool
         */
        public function getIsVisible($object)
        {
            return $object->isVisible();
        }
    }

Implementing a value URL builder
--------------------------------

To generate the links to your domain objects in your blocks, you can use
``ngbm_item_path`` Twig function in your Twig templates. This function
internally forwards the URL generation to the correct value URL builder based
on the value type of the item. To generate the URL for your value type, simply
implement the ``Netgen\BlockManager\Item\ValueUrlBuilderInterface``, which
provides a single method called ``getUrl`` responsible to generate the URL.

.. note::

    ``getUrl`` method should return the full path to the item, including the
    starting slash, not just a slug.

An example implementation might use the Symfony router and generate the URL
based on the object ID:

.. code-block:: php

    /**
     * Returns the object URL. Take note that this is not a slug,
     * but a full path, i.e. starting with /.
     *
     * @param mixed $object
     *
     * @return string
     */
    public function getUrl($object)
    {
        return $this->router->generate(
            'my_custom_route',
            array(
                'id' => $object->id,
            )
        );
    }
